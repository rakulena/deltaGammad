#include <TLorentzVector.h>
//-----------------------------------------------------
// Bs->JpsiPhi->u+u-K+K- as an example
//-----------------------------------------------------

// Calculate the cos KK of Kp
// The important thing is the order of Kp and Km
double CalculateHelicityPolarAngle(
	TLorentzVector pMp,
	TLorentzVector pMm,
	TLorentzVector pKp,
	TLorentzVector pKm 
      )
{   
   TLorentzVector pJpsi = pMp + pMm;
   TLorentzVector pPhi  = pKp + pKm;
   TLorentzVector pB = pJpsi + pPhi;
   TVector3 boosttoparent = -pB.BoostVector();
   pMp.Boost(boosttoparent);
   pMm.Boost(boosttoparent);
   pKp.Boost(boosttoparent);
   pKm.Boost(boosttoparent);
   //pJpsi.Boost(boosttoparent);
   pPhi.Boost(boosttoparent);

   boosttoparent = -pPhi.BoostVector();
   pKp.Boost(boosttoparent);
   TVector3 Unit = pKp.Vect().Unit();
   double psi = acos( Unit.Dot( pPhi.Vect().Unit() ) );
   double coshel = cos( psi );
   return coshel;
}

// Calculte the plane angle between planes:
// Jpsi->u+u- and Phi->K+K-

double CalculatePlaneAngle(
	TLorentzVector ParticleA, 
	TLorentzVector ParticleB,
	TLorentzVector ParticleC, 
	TLorentzVector ParticleD
	)
{

   // Input vector :  
   // Particle A(B), u+(u-);
   // Particle C(D), K+(K-);

   TLorentzVector ParticleFrame = ParticleA+ParticleB+ParticleC+ParticleD;

   TVector3 boostToFrame = -(ParticleFrame.BoostVector()); // Defined as the Bs rest frame 

   // Boost the vectors to the Bs rest frame
   TLorentzVector boostedAxis = ParticleA + ParticleB; // Jpsi vector 
   boostedAxis.Boost(boostToFrame); 
   ParticleA.Boost(boostToFrame);
   ParticleB.Boost(boostToFrame);
   ParticleC.Boost(boostToFrame);
   ParticleD.Boost(boostToFrame);

   // Define the space vectors and unit them
   TVector3 vecA = (ParticleA.Vect()).Unit();
   TVector3 vecB = (ParticleB.Vect()).Unit();
   TVector3 vecC = (ParticleC.Vect()).Unit();
   TVector3 vecD = (ParticleD.Vect()).Unit();

   // Define the normal vectors  
   TVector3 el = ( vecA.Cross( vecB ) ).Unit(); // In Jpsi plane
   TVector3 eh = ( vecC.Cross( vecD ) ).Unit(); // In Phi plane
   TVector3 ez = ( boostedAxis.Vect() ).Unit(); // Jpsi_Pz in the Bs rest frame 

   // Calculate the plane angle Phi 
   double cosPhi = ( eh.Dot(el) );
   double sinPhi = ( el.Cross(eh) ).Dot( ez ) ; //   The normal of KK and mumu planes are in a same x-y plane
   double phi    = acos( cosPhi ) ;

   return ( sinPhi > 0.0 ? phi : -phi ) ;


}
