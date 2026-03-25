
void ReadAngaccCoef(
	const char* angacc_file,
	vector<int> &vec_a,
	vector<int> &vec_b,
	vector<int> &vec_c,
	vector<int> &vec_d,
	vector<double> &vec_coef,
	vector<double> &vec_coeferr
	)
{
   vec_a.clear(); vec_b.clear();
   vec_c.clear(); vec_d.clear();
   vec_coef.clear(); vec_coeferr.clear();

   ifstream ineff;
   ineff.open( angacc_file );
   if(!ineff){ cout << " Angular efficiency file doesn't exist ! Abort the programme "<<endl; exit(0); }
   while(1){
	int a,b,c,d;
	double coef,coeferr;
	ineff >> a >> b >> c >> d >> coef >> coeferr;
	if(!ineff.good()) break;

	//cout<<" "<<a<<" "<<b<<" "<<c<<" "<<d<<" "<<coef<<" "<<coeferr<<endl;
	vec_a.push_back(a);
	vec_b.push_back(b);
	vec_c.push_back(c);
	vec_d.push_back(d);
	vec_coef.push_back(coef);
	vec_coeferr.push_back(coeferr);
   }
   ineff.close();
}
