TGraph *ShadeTF1( 
	TF1 *f1, 
	TF1 *f2, 
	TF1 *f3
	) 
{
   //shade the area between f1 and f2 and draw f3 on top

   //create a TGraph to store the function values
   //shaded area is the fill/color/style of f1
   TGraph *grshade = new TGraph();
   grshade->SetFillColor(f1->GetFillColor());
   grshade->SetFillStyle(f1->GetFillStyle());

   //get picture range
   Double_t xmin = f3->GetMinimumX();
   Double_t xmax = f3->GetMaximumX();
   //Double_t ymin = f3->GetMinimum();
   //Double_t ymax = f3->GetMaximum();

   //process first function
   Int_t npx = f3->GetNpx();
   Int_t npoints=0;
   Double_t dx = (xmax-xmin)/npx;
   Double_t x = xmin+0.5*dx;
   while (x <= xmax) {
	Double_t y = f1->Eval(x);
	//if (y < ymin) y = ymin;
	//if (y > ymax) y = ymax;
	grshade->SetPoint(npoints,x,y);
	npoints++;
	x += dx;
   }
  
   //process second function
   x = xmax-0.5*dx;
   while (x >= xmin) {
	Double_t y = f2->Eval(x);
	grshade->SetPoint(npoints,x,y);
	npoints++;
	x -= dx;
   }
   
   return grshade;
}

