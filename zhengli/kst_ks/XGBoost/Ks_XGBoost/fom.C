#include <TFile.h>
#include <TTree.h>
#include <TGraph.h>
#include <TCanvas.h>
#include <TString.h>
#include <TLatex.h>
#include <cmath>
#include <ROOT/RDataFrame.hxx>
#include <vector>

void fom() {
    std::vector<TString> years = {"2016", "2017", "2018"};
    //std::vector<TString> years = {"2016"};

    for (const auto& year : years) {
        //gROOT->ProcessLine(".x ../inc/lhcbStyle.C");
        TString inputDataPath = Form("/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKshort_data_%s_BDT.root", year.Data());
        TString inputMCPath = Form("/lzufs/user/zhanghy/Sample/Train/Bd2JpsiKshort_mc_%s_BDT.root", year.Data());

        TFile *file_data = TFile::Open(inputDataPath);
        TFile *file_mc = TFile::Open(inputMCPath);
        if (!file_data || !file_mc) {
            std::cerr << "Error: Could not open file for year " << year << std::endl;
            continue;
        }

        ROOT::RDataFrame df_data("DecayTree", file_data);
        ROOT::RDataFrame df_mc("DecayTree", file_mc);

        TGraph *graph = new TGraph();
        int point = 0;

        auto n1 = df_mc.Filter("Bd_ConstJpsi_M > 5250 && Bd_ConstJpsi_M < 5310").Sum("gbw").GetValue();

        double maxFOM = -1;
        double maxBDTcut = -0.2;

        for (double BDTcut = 0; BDTcut <= 1; BDTcut += 0.01) {
            TString mc_cut = Form("Bd_ConstJpsi_M > 5250 && Bd_ConstJpsi_M < 5310 && BDT > %f", BDTcut);
            auto n2 = df_mc.Filter(mc_cut.Data()).Sum("gbw").GetValue();
            auto N = df_data.Filter(Form("Bd_ConstJpsi_M > 5250 && Bd_ConstJpsi_M < 5310 && BDT > %f", BDTcut)).Count().GetValue();

            double FOM = (n2 / n1) / sqrt(N);

            if (FOM > maxFOM) {
                maxFOM = FOM;
                maxBDTcut = BDTcut;
            }

            graph->SetPoint(point, BDTcut, FOM);
            point++;
        }

        TCanvas *canvas = new TCanvas("canvas", "", 800, 600);
        graph->SetMarkerStyle(20);
        graph->SetMarkerColor(kBlue);
        graph->GetXaxis()->SetTitle("BDT");
        graph->GetYaxis()->SetTitle("F.O.M");
        graph->GetYaxis()->SetTitleOffset(1.4); 
        graph->Draw("ALP");

        TLatex *latex = new TLatex();
        latex->SetTextSize(0.04);
        latex->SetTextAlign(21);
        latex->DrawLatex(maxBDTcut, maxFOM, Form("Max FOM: %.5f\nBDT cut: %.2f", maxFOM, maxBDTcut));

        TString outputPlotPath = Form("/lzufs/user/zhanghy/kst_ks/Ks_XGBoost/fom/fom%s.png", year.Data());
        canvas->SaveAs(outputPlotPath);

        file_data->Close();
        file_mc->Close();
        delete latex;
        delete canvas;
        delete graph;
        
    }
    gROOT->ProcessLine(".q");
}
