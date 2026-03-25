
// Input tex for the graph
//-----------------------------------------------------------
void InputGraphTex(
	const char *filepath,
	double x[],
	double x_l[],
	double x_h[],
	double y[],
	double y_l[],
	double y_h[]
	)
{
   vector<double> tmp1,tmp2,tmp3,tmp4,tmp5,tmp6;
   ifstream iffile( filepath );
   tmp1.clear();     tmp2.clear();     tmp3.clear();
   tmp4.clear();     tmp5.clear();     tmp6.clear();

   if( !iffile ){
	cout<<"---------------------------------- "<<endl;
	cout<<"  The file of varlist doesn't exit ! =_= "<<endl;
	cout<<"---------------------------------- "<<endl;
	iffile.close();
	exit(0);
	//return;
   }

   while (!iffile.eof()){
	double tmpx, tmpx_l, tmpx_h;
	double tmpy, tmpy_l, tmpy_h;
	iffile >>tmpx >>tmpx_l >>tmpx_h >>tmpy >>tmpy_l >>tmpy_h;
	tmp1.push_back(tmpx);
	tmp2.push_back(tmpx_l);
	tmp3.push_back(tmpx_h);
	tmp4.push_back(tmpy);
	tmp5.push_back(tmpy_l);
	tmp6.push_back(tmpy_h);
   }
   iffile.close();

   const int num = tmp1.size()-1;
   for(int i=0;i<num;i++){
	x[i]   = tmp1[i];
	x_l[i] = tmp2[i];
	x_h[i] = tmp3[i];
	y[i]   = tmp4[i];
	y_l[i] = tmp5[i];
	y_h[i] = tmp6[i];
   }
}


// Input tex for the graph with unit transformation
//-----------------------------------------------------------
void InputGraphTex(
	const char *filepath,
	double x[],
	double x_l[],
	double x_h[],
	double y[],
	double y_l[],
	double y_h[],
	double xunit,
	double yunit
	)
{
   vector<double> tmp1,tmp2,tmp3,tmp4,tmp5,tmp6;
   ifstream iffile( filepath );
   tmp1.clear();     tmp2.clear();     tmp3.clear();
   tmp4.clear();     tmp5.clear();     tmp6.clear();

   if( !iffile ){
	cout<<"---------------------------------- "<<endl;
	cout<<"  The file of varlist doesn't exit ! =_= "<<endl;
	cout<<"---------------------------------- "<<endl;
	iffile.close();
	exit(0);
	//return;
   }

   while (!iffile.eof()){
	double tmpx, tmpx_l, tmpx_h;
	double tmpy, tmpy_l, tmpy_h;
	iffile >>tmpx >>tmpx_l >>tmpx_h >>tmpy >>tmpy_l >>tmpy_h;
	tmp1.push_back(tmpx);
	tmp2.push_back(tmpx_l);
	tmp3.push_back(tmpx_h);
	tmp4.push_back(tmpy);
	tmp5.push_back(tmpy_l);
	tmp6.push_back(tmpy_h);
   }
   iffile.close();

   const int num = tmp1.size()-1;
   for(int i=0;i<num;i++){
	x[i]   = tmp1[i]*xunit;
	x_l[i] = tmp2[i]*xunit;
	x_h[i] = tmp3[i]*xunit;
	y[i]   = tmp4[i]*yunit;
	y_l[i] = tmp5[i]*yunit;
	y_h[i] = tmp6[i]*yunit;
   }

}

// Input graph
//-----------------------------------------------------------
TGraphAsymmErrors *InputGraph(
	const char* iffile,
	int binnum,
	double xunit,
	double yunit
	)
{
   const int nBin = binnum;
   double x[nBin];
   double x_l[nBin];
   double x_h[nBin];
   double y[nBin];
   double y_l[nBin];
   double y_h[nBin];

   InputGraphTex( iffile, x, x_l, x_h, y, y_l, y_h, xunit, yunit );
   TGraphAsymmErrors *graph = new TGraphAsymmErrors(nBin,x,y,x_l,x_h,y_l,y_h);

   return graph;
}
