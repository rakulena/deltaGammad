#include <iostream>
#include <vector>
#include <fstream>
#include <zconf.h>
#include <string>
#include <sstream>

// Read a general matrix file
vector<vector<double>> readMatrixFile( const char *inpfile ){

   vector<vector<double>> matrixAll{};
   
   string tmp_line;
   string tmp_str;
   ifstream fileStream(inpfile, std::ios::in); // ios::in represents read only

   if(fileStream.fail()){
	throw std::logic_error(" File does not exist !");
   }else{
	// read one line once
	while( getline( fileStream, tmp_line,'\n' ) ){ 
	   
	   //cout<<tmp_line<<endl;
	   vector<double> tmp_val{}; tmp_val.clear(); 
	   istringstream _istring( tmp_line );
	   while( _istring>>tmp_str ){
		tmp_val.push_back( stod(tmp_str) );
	   }
	   matrixAll.push_back( tmp_val );
	}
	fileStream.close();
   }

   return matrixAll;
}

// Get a normal TMatrix, m*n
TMatrixD getTMatrixD( const char *inpfile ){
   
   vector<vector<double>> matrixAll = readMatrixFile( inpfile );
  
   // Count the numbers of row and column
   const int nrow = matrixAll.size();
   const int ncol = matrixAll[0].size();
   TMatrixD tmp_matrix(nrow,ncol);

   for( int i=0; i<nrow; i++ ){
     for( int j=0; j<ncol; j++ ){
         tmp_matrix[i][j] = matrixAll[i][j];
      }
   }
   
   return tmp_matrix;
}

// Get a symmetric TMatrix, n*n
TMatrixDSym getTMatrixDSym( const char *inpfile ){
   
   vector<vector<double>> matrixAll = readMatrixFile( inpfile );
  
   const int nrow = matrixAll.size();
   TMatrixDSym tmp_matrix(nrow);

   for( int i=0; i<nrow; i++ ){
     for( int j=0; j<nrow; j++ ){
         tmp_matrix[i][j] = matrixAll[i][j];
      }
   }
   
   return tmp_matrix;
}


