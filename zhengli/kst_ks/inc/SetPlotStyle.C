
// Set the plot style of histogram, graph, xframe, pullframe
//-----------------------------------------------------------
void SetHistStyle(
	TH1D   *hist,
	Color_t MCol,
	int     MSty,
	double  MSiz,
	Color_t LCol,
	int     LSty,
	double  LWid,
	const char *XTitle,
	double ymin,
	double ymax
	)
{
   hist->SetMarkerColor( MCol );
   hist->SetMarkerStyle( MSty );
   hist->SetMarkerSize(  MSiz );
   hist->SetLineColor( LCol );
   hist->SetLineStyle( LSty );
   hist->SetLineWidth( LWid );
   hist->GetXaxis()->SetTitle( XTitle );
   if(ymin!=ymax){
	hist->SetMinimum(ymin);
	hist->SetMaximum(ymax*1.1);
   }

}

void SetHistStyle(
	TH1D   *hist,
	Color_t MCol,
	int     MSty,
	double  MSiz,
	Color_t LCol,
	int     LSty,
	double  LWid,
	const char *XTitle,
	const char *YTitle,
	double ymin,
	double ymax
	)
{
   hist->SetMarkerColor( MCol );
   hist->SetMarkerStyle( MSty );
   hist->SetMarkerSize(  MSiz );
   hist->SetLineColor( LCol );
   hist->SetLineStyle( LSty );
   hist->SetLineWidth( LWid );

   TAttAxis *xAxis = hist->GetXaxis();
   TAttAxis *yAxis = hist->GetYaxis();
   xAxis->SetTitleFont(132);
   yAxis->SetTitleFont(132);
   xAxis->SetTitleSize(0.06);
   yAxis->SetTitleSize(0.06);
   xAxis->SetTitleOffset(1.15);
   yAxis->SetTitleOffset(1.15);
   xAxis->SetLabelOffset(0.02);
   yAxis->SetLabelOffset(0.01);

   hist->GetXaxis()->SetTitle( XTitle );
   hist->GetYaxis()->SetTitle( YTitle );

   if(ymin!=ymax){
	hist->SetMinimum(ymin);
	hist->SetMaximum(ymax*1.1);
   }
}

void SetGraphStyle(
	TGraph *graph,
	Color_t MCol,
	int     MSty,
	double  MSiz,
	Color_t LCol,
	int     LSty,
	double  LWid,
	const char *XTitle,
	const char *YTitle,
	double  ymin,
	double  ymax
	)
{
   graph->SetMarkerColor( MCol );
   graph->SetMarkerStyle( MSty );
   graph->SetMarkerSize(  MSiz );
   graph->SetLineColor( LCol );
   graph->SetLineStyle( LSty );
   graph->SetLineWidth( LWid );
   
   TAttAxis *xAxis = graph->GetXaxis();
   TAttAxis *yAxis = graph->GetYaxis();
   xAxis->SetTitleFont(132);
   yAxis->SetTitleFont(132);
   xAxis->SetTitleSize(0.06);
   yAxis->SetTitleSize(0.06);
   xAxis->SetTitleOffset(1.15);
   yAxis->SetTitleOffset(1.15);
   xAxis->SetLabelOffset(0.02);
   yAxis->SetLabelOffset(0.01);
   
   graph->GetXaxis()->SetTitle( XTitle );
   graph->GetYaxis()->SetTitle( YTitle );
  
   if(ymin!=ymax){
	graph->SetMinimum(ymin);
	graph->SetMaximum(ymax*1.1);
   }

}

