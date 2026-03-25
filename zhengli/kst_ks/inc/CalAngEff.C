
double LegPol(double x, int i)
{

#if 1
   const int n = i;
   double LP[n+1];
   LP[0] = 1;
   LP[1] = x;

   for( int j=2; j<=n; j++ ){
      LP[j] = (2.*j-1.)/j*x*LP[j-1]-(j-1.)/j*LP[j-2];
   }
   return LP[n];
#endif
#if 0
   if(i==0) return 1;
   if(i==1) return x;
   if(i==2) return 0.5*(3.*x*x-1);
   if(i==3) return 0.5*(5.*pow(x,3)-3.*x);
   if(i==4) return (35.*pow(x,4)-30*x*x+3)/8.;
   if(i==5) return (63.*pow(x,5)-70.*x*x*x+15*x)/8.;
   if(i==6) return (231.*pow(x,6)-315.*pow(x,4)+105*x*x-5)/16.;  
   if(i==7) return (429.*pow(x,7)-693.*pow(x,5)+315.*pow(x,3)-35*x)/16.;
   if(i==8) return (6435.*pow(x,8)-12012.*pow(x,6)+6930.*pow(x,4)-1260*x*x+35.)/128.;
   if(i==10) return (46189.*pow(x,10)-109395.*pow(x,8)+90090.*pow(x,6)-30030.*pow(x,4)+3465*x*x-63)/256.;
   if(i==12) return 1./1024.*(231. - 18018.*pow(x,2) + 225225.*pow(x,4) - 1021020.*pow(x,6) + 2078505.*pow(x,8) - 
         1939938.*pow(x,10) + 676039.*pow(x,12));
   if(i==14) return 1./2048.*(-429. + 45045.*pow(x,2) - 765765.*pow(x,4) + 4849845.*pow(x,6) - 
         14549535.*pow(x,8) + 22309287.*pow(x,10) - 16900975.*pow(x,12) + 
         5014575.*pow(x,14));
   if(i==16) return 1./32768.*(6435. - 875160.*pow(x,2) + 19399380.*pow(x,4) - 162954792.*pow(x,6) + 
         669278610.*pow(x,8) - 1487285800.*pow(x,10) + 1825305300.*pow(x,12) - 
         1163381400.*pow(x,14) + 300540195.*pow(x,16));          
   if(i==18) return 1./65536.*(-12155. + 2078505.*pow(x,2) - 58198140.*pow(x,4) + 624660036.*pow(x,6) - 
         3346393050.*pow(x,8) + 10039179150.*pow(x,10) - 17644617900.*pow(x,12) + 
         18032411700.*pow(x,14) - 9917826435.*pow(x,16) + 2268783825.*pow(x,18));
   if(i==20) return 1./262144.*(46189. - 9699690.*pow(x,2) + 334639305.*pow(x,4) - 4461857400.*pow(x,6) + 
         30117537450.*pow(x,8) - 116454478140.*pow(x,10) + 273491577450.*pow(x,12) - 
         396713057400.*pow(x,14) + 347123925225.*pow(x,16) - 167890003050.*pow(x,18) + 34461632205.*pow(x,20));
   if(i==22) return (-88179. + 22309287*pow(x,2) - 929553625*pow(x,4) + 15058768725*pow(x,6) - 
         124772655150*pow(x,8) + 601681470390*pow(x,10) - 1805044411170*pow(x,12) + 
         3471239252250*pow(x,14) - 4281195077775*pow(x,16) + 3273855059475*pow(x,18) - 
         1412926920405*pow(x,20) + 263012370465*pow(x,22))/524288.;            
   if(i==24) return (676039. - 202811700*pow(x,2) + 10039179150*pow(x,4) - 194090796900*pow(x,6) + 
         1933976154825*pow(x,8) - 11345993441640*pow(x,10) + 
         42117702927300*pow(x,12) - 102748681866600*pow(x,14) + 
         166966608033225*pow(x,16) - 178970743251300*pow(x,18) + 
         121511715154830*pow(x,20) - 47342226683700*pow(x,22) + 8061900920775*pow(x,24)
         )/4.194304e6;
   if(i==26) return (-1300075. + 456326325*pow(x,2) - 26466926850*pow(x,4) + 601681470390*pow(x,6) - 
         7091245901025*pow(x,8) + 49638721307175*pow(x,10) - 
         222622144044300*pow(x,12) + 667866432132900*pow(x,14) - 
         1369126185872445*pow(x,16) + 1923935489951475*pow(x,18) - 
         1822675727322450*pow(x,20) + 1112542327066950*pow(x,22) - 
         395033145117975*pow(x,24) + 61989816618513*pow(x,26))/8.388608e6;
   return 0;
#endif
}

TComplex Y(double x, double phi, int l, int m){

   double pi = TMath::Pi();

#if 0
   TComplex term_phi = TComplex(1.,m*phi,1);
   double term_sin = pow( sqrt(1-x*x), abs(m) );
   double term_cos = 0;

   if(l==0&&m==0)  term_cos =  0.50/sqrt(pi);
   if(l==1&&m==0)  term_cos =  0.50*sqrt(3./pi)*x;
   if(l==1&&m==1)  term_cos = -0.50*sqrt(1.5/pi);
   if(l==1&&m==-1) term_cos =  0.50*sqrt(1.5/pi);

   if(l==2&&m==0)  term_cos =  0.25*sqrt(5./pi)*(3*x*x-1);
   if(l==2&&m==1)  term_cos = -0.50*sqrt(15./2./pi)*x;
   if(l==2&&m==-1) term_cos =  0.50*sqrt(15./2./pi)*x;
   if(l==2&&m==2)  term_cos =  0.25*sqrt(15./2./pi);
   if(l==2&&m==-2) term_cos =  0.25*sqrt(15./2./pi);

   if(l==3&&m==1)  term_cos = -1./8.*sqrt(21./pi)*(5*x*x-1);
   if(l==3&&m==-1) term_cos =  1./8.*sqrt(21./pi)*(5*x*x-1);
   if(l==3&&m==3)  term_cos = -1./8.*sqrt(35./pi);
   if(l==3&&m==-3) term_cos =  1./8.*sqrt(35./pi);

   if(l==4&&m==0)  term_cos = 3./16./sqrt(pi)*(35.*pow(x,4)-30.*x*x+3.);
   if(l==4&&m==2)  term_cos =  3./8.*sqrt(2.5/pi)*(7.*x*x-1.);
   if(l==4&&m==-2) term_cos =  3./8.*sqrt(2.5/pi)*(7.*x*x-1.);

   //if(l==5&&m==0)  term_cos =  1./16.*sqrt(11./pi)*(15*x-70*pow(x,3)+63*pow(x,5));
   if(l==5&&m==1)  term_cos = -1./16.*sqrt(165./2./pi)*(1-14*x*x+21*pow(x,4));
   if(l==5&&m==-1) term_cos =  1./16.*sqrt(165./2./pi)*(1-14*x*x+21*pow(x,4));
   if(l==5&&m==3)  term_cos = -1./32.*sqrt(385./pi)*(9*x*x-1);
   if(l==5&&m==-3) term_cos =  1./32.*sqrt(385./pi)*(9*x*x-1);

   if(l==6&&m==0)  term_cos = 1./32.*sqrt(13./pi)*(-5.+105.*x*x-315*pow(x,4)+231*pow(x,6));
   if(l==6&&m==2)  term_cos = 1./64.*sqrt(1365./pi)*(1-18*x*x+33*pow(x,4));
   if(l==6&&m==-2) term_cos = 1./64.*sqrt(1365./pi)*(1-18*x*x+33*pow(x,4));
   if(l==6&&m==4)  term_cos = 3./32.*sqrt(91./2./pi)*(-1+11*x*x);
   if(l==6&&m==-4) term_cos = 3./32.*sqrt(91./2./pi)*(-1+11*x*x);

   //if(l==7&&m==0) term_cos = 1./32.*sqrt(15./pi)*(-35.*x+315*pow(x,3)-693*pow(x,5)+429*pow(x,7));
   if(l==7&&m==1)  term_cos = -1./64.*sqrt(105./2./pi)*(-5+135*x*x-495*pow(x,4)+429*pow(x,6));
   if(l==7&&m==-1) term_cos =  1./64.*sqrt(105./2./pi)*(-5+135*x*x-495*pow(x,4)+429*pow(x,6));
   if(l==7&&m==3)  term_cos = -3./64.*sqrt(35./2./pi)*(3-66*pow(x,2)+143*pow(x,4));
   if(l==7&&m==-3) term_cos =  3./64.*sqrt(35./2./pi)*(3-66*pow(x,2)+143*pow(x,4));

   if(l==8&&m==0)  term_cos = 1./256.*sqrt(17./pi)*(35-1260*x*x+6930*pow(x,4)-12012*pow(x,6)+6435*pow(x,8));
   if(l==8&&m==2)  term_cos = 3./128.*sqrt(595./pi)*(-1+33*x*x-143*pow(x,4)+143*pow(x,6));
   if(l==8&&m==-2) term_cos = 3./128.*sqrt(595./pi)*(-1+33*x*x-143*pow(x,4)+143*pow(x,6));
  // if(l==8&&m==4)  term_cos = 3./128.*sqrt(1309/2./pi)*(1-26*x*x+65*pow(x,4));
  // if(l==8&&m==-4) term_cos = 3./128.*sqrt(1309/2./pi)*(1-26*x*x+65*pow(x,4));
   return term_cos*term_sin*term_phi;
#endif

#if 1
   if(l==0&&m==0) return 0.5/sqrt(pi);
   if(l==1&&m==-1) return 0.5*sqrt(1.5/pi)*sqrt(1-x*x)*TComplex(1.,-phi,1);
   if(l==1&&m==0) return 0.5*sqrt(3./pi)*x;
   if(l==1&&m==1) return -0.5*sqrt(1.5/pi)*sqrt(1-x*x)*TComplex(1.,phi,1);
   if(l==2&&m==-2) return 0.25*sqrt(15./2./pi)*(1-x*x)*TComplex(1.,-2.*phi,1);
   if(l==2&&m==-1) return 0.5*sqrt(15./2./pi)*sqrt(1-x*x)*x*TComplex(1.,-phi,1);
   if(l==2&&m==0) return 0.25*sqrt(5./pi)*(3*x*x-1);
   if(l==2&&m==1) return -0.5*sqrt(15./2./pi)*sqrt(1-x*x)*x*TComplex(1.,phi,1);
   if(l==2&&m==2) return 0.25*sqrt(15./2./pi)*(1-x*x)*TComplex(1.,2.*phi,1);
   if(l==3&&m==1) return -1./8.*sqrt(21./pi)*sqrt(1-x*x)*(5.*x*x-1.)*TComplex(1.,phi,1);
   if(l==3&&m==-1) return 1./8.*sqrt(21./pi)*sqrt(1-x*x)*(5.*x*x-1.)*TComplex(1.,-phi,1);  
   if(l==3&&m==3) return -1./8.*sqrt(35./pi)*sqrt(1-x*x)*(1.-x*x)*TComplex(1.,3.*phi,1);
   if(l==3&&m==-3) return 1./8.*sqrt(35./pi)*sqrt(1-x*x)*(1.-x*x)*TComplex(1.,-3.*phi,1);  
   if(l==4&&m==0) return 3./16./sqrt(pi)*(35.*pow(x,4)-30.*x*x+3.);
   if(l==4&&m==2) return 3./8.*sqrt(2.5/pi)*(1-x*x)*(7.*x*x-1.)*TComplex(1.,2.*phi,1);    
   if(l==4&&m==-2) return 3./8.*sqrt(2.5/pi)*(1-x*x)*(7.*x*x-1.)*TComplex(1.,-2.*phi,1);    

   if(l==5&&m==0) return 1./16.*sqrt(11./pi)*(15*x-70*pow(x,3)+63*pow(x,5));
   if(l==6&&m==0) return 1./32.*sqrt(13./pi)*(-5.+105.*x*x-315*pow(x,4)+231*pow(x,6));
   if(l==7&&m==0) return 1./32.*sqrt(15./pi)*(35.*x+315*pow(x,3)-693*pow(x,5)+429*pow(x,7));
   if(l==8&&m==0) return 1./256.*sqrt(17./pi)*(35-1260*x*x+6930*pow(x,4)-12012*pow(x,6)+6435*pow(x,8));
   if(l==5&&m==1) return -1./16.*sqrt(165./2./pi)*(1-14*x*x+21*pow(x,4))*sqrt(1-x*x)*TComplex(1.,phi,1);
   if(l==7&&m==1) return -1./64.*sqrt(105./2./pi)*(-5+135*x*x-495*pow(x,4)+429*pow(x,6))*sqrt(1-x*x)*TComplex(1.,phi,1);  
   if(l==5&&m==-1) return 1./16.*sqrt(165./2./pi)*(1-14*x*x+21*pow(x,4))*sqrt(1-x*x)*TComplex(1.,-phi,1);
   if(l==7&&m==-1) return 1./64.*sqrt(105./2./pi)*(-5+135*x*x-495*pow(x,4)+429*pow(x,6))*sqrt(1-x*x)*TComplex(1.,-phi,1); 
   if(l==6&&m==-2) return 1./64.*sqrt(1365./pi)*(1-18*x*x+33*pow(x,4))*(1-x*x)*TComplex(1.,-2.*phi,1);
   if(l==8&&m==-2) return 3./128.*sqrt(595./pi)*(-1+33*x*x-143*pow(x,4)+143*pow(x,6))*(1-x*x)*TComplex(1.,-2.*phi,1);
   if(l==6&&m==2) return 1./64.*sqrt(1365./pi)*(1-18*x*x+33*pow(x,4))*(1-x*x)*TComplex(1.,2.*phi,1);
   if(l==8&&m==2) return 3./128.*sqrt(595./pi)*(-1+33*x*x-143*pow(x,4)+143*pow(x,6))*(1-x*x)*TComplex(1.,2.*phi,1);  
   return 0;
#endif
}

TComplex CoFunction(
      double xmhh, double xcosh, double xcosl, double xphih,
      double dlz_ly, double dlz_hy, int a, int b, int c, int d
      )
{
   double norm_m = 2.*(xmhh-dlz_ly)/(dlz_hy-dlz_ly)-1;
   return TComplex::Conjugate(Y(xcosl,xphih,b,c))*LegPol(xcosh,a)*LegPol(norm_m,d);
}
