#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cstdlib>

#include "TROOT.h"
#include "TChain.h"
#include "TFile.h"
#include "TSelector.h"
#include "TTree.h"
#include "TDirectory.h"
#include "TMath.h"

//-------------------------------------------
// MakeSlector
//----------------------------------------------------------------------
// Make a Class to read the root file
// The ".h" and ".C" file generated from the script are really convenient
//-------------------------------------------------------------------------

using namespace std;
int main(int argc, char** argv) {

  //command line parameter defaults
  string filelist = "";
  string root_tree= ""; 
  string offile = "headfile";
  string tool = "cla";

  //parse command line
  int c;
  while( (c=getopt(argc,argv,"hn:n:f:p:t:")) != -1 ){
    switch(c){
    case 'h':
      std::cout <<"Usage: " << argv[0]<<std::endl
                <<"   [-h] [-n <name_of_outputfile>] " <<std::endl
                <<"   [-f filelist] " << std::endl
                <<"   [-p treepath] " << std::endl
		    <<"   [-t tool] t = cla(default,MakeClass), cla2(3)(second(third) type of Loop() definition), sel(MakeSelector) " << std::endl
                <<"Example:"<<std::endl
                <<"   ./MakeHeadfile -f file.list "<<std::endl
                <<"   ./MakeHeadfile -p xxx.root/Decaytree "<<std::endl<<std::endl;
      exit(0);
      break;
    case 'n':
      offile = optarg;
      break;
    case 'f':
      filelist = optarg;
      break;
    case 'p':
      root_tree = optarg;
      break;	
    case 't':
	tool = optarg;
	break;
    }
  }

  // make sure there is only one available filelist or path 
  if(filelist==""&&root_tree==""){
    cout<<"=================================================="<<endl;
    cout<<"  I need only one available filelist or path "<<endl;
    cout<<"=================================================="<<endl<<endl;
    return 0;
  }
  if(filelist!=""&&root_tree!=""){
    cout<<"=================================================="<<endl;
    cout<<"  I need only one available filelist or path "<<endl;
    cout<<"=================================================="<<endl<<endl;
    return 0;
  }

 // input one root_tree by " -f filelist" or " -p xxx.root/DecayTree " 
  string input_root_tree;
  if(!(filelist=="")){

   fstream fin;
   fin.open(filelist.c_str());
   for(int i=0;i<1;i++) 
    fin>>input_root_tree; 

  }else{
   input_root_tree = root_tree; 
  }
  cout<<"============================================="<<endl;
  cout<<" Root File : "<<input_root_tree<<endl;
  cout<<"=============================================="<<endl;
  cout<<" Generate the files                          " <<endl;
  cout<<"=============================================="<<endl;
  
  // generate "offile.h" and "offile.C"
  // but "offile.C" won't be used
  TChain *chain = new TChain();
  chain->Add(input_root_tree.c_str());
  
  if( !chain ){
    cout<<"=================================================="<<endl;
    cout<<" The file doesn't exist ! "<<endl;
    cout<<"=================================================="<<endl<<endl;
    return 0;
  }
 
  string func;
  if( tool == "cla" )  func = "Loop( Long64_t runevt, Int_t year, const char *inforfile, const char *runmode )";
  if( tool == "cla2" ) func = "Loop( Long64_t runevt, const char *runmode )";
  if( tool == "cla3" ) func = "Loop( Long64_t runevt )";

  if( tool == "cla" || tool == "cla2" || tool == "cla3" ){
     chain->MakeClass(offile.c_str());
     system( Form("sed -i 's/void     Loop()/void     %s/g' %s.h",func.c_str(),offile.c_str()) );
     cout<<"=============================================="<<endl;
     cout<<" Loop function : "<<func<<endl; 
     cout<<"=============================================="<<endl;
  }

  if( tool == "sel" )   
     chain->MakeSelector(offile.c_str());
   
  system( Form("rm %s.C",offile.c_str()) );
  
  cout<<" Total Events : "<<chain->GetEntries()<<endl;
  cout<<"============================================="<<endl;
  cout<<" It's done!                                  "<<endl;
  cout<<"============================================="<<endl;
}
