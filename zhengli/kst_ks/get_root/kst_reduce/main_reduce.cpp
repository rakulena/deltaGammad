///////////////////////////////
// Main Program
///////////////////////////////
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <unistd.h>
#include "reduce.h"

using namespace std;

int main(int argc, char** argv) {

  cout<<"==========================================="<<endl;
  cout<<" STARTING  TIME : "<<endl;
  system("date");
  cout<<"==========================================="<<endl;

  //command line parameter defaults
  int nevt = 0;
  int year = 0;
  string mode = "sig_data";
  string filelist = "file.list";

  //parse command line
  int c;
  while( (c=getopt(argc,argv,"hn:n:f:y:m:")) != -1 ){
    switch(c){
    case 'h':
      cout <<"Usage: " << argv[0]<<endl 
		<<"         [-h] [-n <number_of_events>] " << endl
		<<"         [-f filelist] " << endl
		<<"         [-y year]     " << endl  
		<<"         [-m mode]     " << endl  
		<<"Example:"<<endl
		<<"   ./main_xxx -f file.list "<<endl<<endl;
      exit(0);
      break;
    case 'n':
      nevt = atoi(optarg);
      if (nevt < 0) nevt = 0;
      break;
    case 'f':
      filelist = optarg;
      break;
    case 'y':
	year = atoi(optarg);
	break;
    case 'm':
	mode = optarg;
	break;
    }
  }
  
  // get input and output files from parameters.rc
  TChain *chain = new TChain();

  // input root file
  TString input_roottuple;
  cout<<"==========================================="<<endl;
  cout<<"           Reading  Files            "<<endl;
  cout<<"==========================================="<<endl;

  // read input information
  vector<string> inputinfor;
  inputinfor.clear();

  ifstream fin(filelist.c_str());

  if(!fin){
     cout<<"---------------------------------- "<<endl;
     cout<<"  The filelist doesn't exit ! =_= "<<endl;
     cout<<"---------------------------------- "<<endl;
     exit(0);
  }

  while(!fin.eof()){
     string tmpinfor;
     fin>>tmpinfor;
     inputinfor.push_back( tmpinfor );
  }
  fin.close();

  // merge files
  int num = inputinfor.size();
  int innum;
  string::size_type tmpcutfile = inputinfor[num-2].find("cuteff_");

  if( tmpcutfile!=inputinfor[num-2].npos ){
     innum = num-3;
  }else{
     innum = num-2;
  }

  for( int i=0; i<innum; i++ ){

     TChain *tmp_chain = new TChain();
     tmp_chain->Add(inputinfor[i].c_str()); 

     if(!tmp_chain){
	  cout << "Can not open ROOT file: " << inputinfor[i] << endl;
     } else {
	  cout << "File: " << inputinfor[i] 
	     << ", Entries = " << tmp_chain->GetEntries() << endl;
	  chain->Add(inputinfor[i].c_str());
     }
     delete tmp_chain;

  }

  // write temp information file
  string inforfile = Form("%s_tmpinfor.txt",filelist.c_str());
  ofstream tmpoffile( inforfile );
  for( int i=0; i<num-innum-1; i++ ){
     tmpoffile<<inputinfor[innum+i]<<endl;
  }
  tmpoffile.close();

  cout<<"==========================================="<<endl;
  cout<<"  Save the input info. in temp file, "<<inforfile<<endl;
  cout<<"==========================================="<<endl;

  // print out the number of events 
  cout<<"==========================================="<<endl;
  cout<< " "<< innum<< " file(s) is(are) merged"<<endl;
  cout<<"==========================================="<<endl;
  cout<<"         Analyzing  Files            "<<endl;
  cout<<"==========================================="<<endl;

  // number of events to be skimmed
  int runevt = chain->GetEntries();

  if( runevt==0 ){
     cout<<"==========================================="<<endl;
     cout<<" No input data, please check the pat list ! "<<endl;
     cout<<"==========================================="<<endl;
     exit(0);
  }

  if(nevt<runevt&&nevt!=0){
     runevt = nevt;
  }
  cout << " Total Entries: " << chain->GetEntries() << endl;
  cout << "   Run Entries: " << runevt << endl;
  cout<<"==========================================="<<endl;

  // processor class
  reduce *_reduce = new reduce(chain);
  _reduce->Loop( runevt, year, inforfile.c_str(), mode.c_str() );

  cout<<"==========================================="<<endl;
  cout<<"          Ouputing  Files            "<<endl;
  cout<<"==========================================="<<endl;
  system( Form("cat %s",inforfile.c_str()) );
  system( Form("rm %s",inforfile.c_str()) );

  cout<<"==========================================="<<endl;
  cout<<" ENDING  TIME : "<<endl;
  system("date");
  cout<<"==========================================="<<endl;

}
