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
#include "massfit.h"

using namespace std;

int main(int argc, char** argv) {

  cout<<"==========================================="<<endl;
  cout<<" STARTING  TIME : "<<endl;
  system("date");
  cout<<"==========================================="<<endl;

  //command line parameter defaults
  int nevt = 0;
  string mode = "";
  string filelist = "file.list";

  //parse command line
  int c;
  while( (c=getopt(argc,argv,"hn:n:f:m:")) != -1 ){
    switch(c){
    case 'h':
      cout <<"Usage: " << argv[0]<<endl 
		<<"         [-h] [-n <number_of_events>] " << endl
		<<"         [-f filelist] " << endl
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
  int num = inputinfor.size()-1;

  for( int i=0; i<num; i++ ){

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

  // print out the number of events 
  cout<<"==========================================="<<endl;
  cout<< " "<< num<< " file(s) is(are) merged"<<endl;
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
  massfit *_massfit = new massfit(chain);
  _massfit->Loop(runevt,mode.c_str());

  cout<<"==========================================="<<endl;
  cout<<" ENDING  TIME : "<<endl;
  system("date");
  cout<<"==========================================="<<endl;

}
