// Print picture as *.png, *.pdf, *.eps, *.C 
//-------------------------------------------------------------

void Printpic( TCanvas *pic, string outpic, int formatnum ){

   string format[4] = {".pdf",".png",".eps",".C"};
   char out_name[200];
   for(int i=0;i<formatnum;i++){
	sprintf(out_name,"%s%s",outpic.c_str(),format[i].c_str());
	pic->Print(out_name);
   }

}

void Printpic2( TCanvas *pic, string outpic, int formatnum ){

   string format[4] = {".pdf",".png",".eps",".C"};
   char out_name[200];
   for(int i=0;i<formatnum;i++){
	sprintf(out_name,"./output/%s%s",outpic.c_str(),format[i].c_str());
	pic->Print(out_name);
   }

}
