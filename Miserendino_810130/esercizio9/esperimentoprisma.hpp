#ifndef ESPERIMENTOPRISMA_HPP 
#define ESPERIMENTOPRISMA_HPP
#include <cmath>
#include <random>
using namespace std;
#define M_PI           3.14159265358979323846  /* pi */

  std::default_random_engine generator;

class EsperimentoPrisma {
  public:
    EsperimentoPrisma();
    void Esegui();
    void Analizza();
    double Get_sigmat();
    double Gettheta1();
    double Gettheta0();
    double Gettheta2();
    double Gettheta1in();
    double Gettheta2in();
    double Getdm1();
    double Getn1in();
    double Getn2in();
    double Getn1();
    double Getn2();
    double Getdm2();
    double Getain();
    double Getbin();
    double GetA();
    double GetB();
    double Getdm1in();
    double Getdm2in();
    double Gettheta0in();
    double Get_mediat0();
    double Get_mediat1();
    double Get_mediat2();
    double Get_devA();
    double Get_devB();
    double Get_corrdm();
    double Get_corrn();
    double Get_corrAB();
  private:                
    double lambda1,lambda2; 
    double alpha;
    double a_input, a_misurato=0;
    double b_input, b_misurato=0;
    double n1_input, n1_misurato;
    double n2_input, n2_misurato;
    double t0_input, t0_misurato;
    double t1_input, t1_misurato;
    double t2_input, t2_misurato;
    double dm1,dm2;
    double dm1in,dm2in;
    double _sommat0;
    double _sommat1;
    double _sommat2;
    double _sigmat;
    double _mediat0;
    double _mediat1;
    double _mediat2;

    int _cont;

    double _devA,_devB;

    double _x_dm, _y_dm, _x2_dm, _y2_dm, _xy_dm;
    double _x_n, _y_n, _x2_n, _y2_n, _xy_n;
    double _x_AB, _y_AB, _x2_AB, _y2_AB, _xy_AB;
};
EsperimentoPrisma::EsperimentoPrisma() :
  lambda1(579.1E-9),
  lambda2(404.7E-9),
  alpha(60*M_PI/180.),
 _sigmat(0.3E-3),
  a_input(2.7),
  b_input(60000E-18),
  _sommat0(0.),
  _sommat1(0.),
  _sommat2(0.),
  _cont(0.)
{
  //calcolo degli indici di rifrazione attesi
  n1_input = sqrt(a_input+b_input/(pow(lambda1,2)));
  n2_input = sqrt(a_input+b_input/(pow(lambda2,2)));
// calcolo dei valori attesi degli angoli misurati
  t0_input = M_PI/2;  //theta0 e' arbitrario
  dm1in = 2.*asin(n1_input*sin(0.5*alpha))-alpha;
  t1_input = t0_input+dm1in;
  dm2in = 2.*asin(n2_input*sin(0.5*alpha))-alpha;
  t2_input = t0_input+dm2in;
  //Inizializzazione delle varibili per calcolare i coefficienti di correlazione
      _x_dm = 0.;
      _y_dm = 0.;
      _x2_dm = 0.;
      _y2_dm = 0.; 
      _xy_dm = 0.; 
      _x_n = 0.; 
      _y_n = 0.; 
      _x2_n = 0.; 
      _y2_n = 0.; 
      _xy_n = 0.; 
      _x_AB = 0.; 
      _y_AB = 0.; 
      _x2_AB = 0.; 
      _y2_AB = 0.; 
      _xy_AB = 0.; 
}
void EsperimentoPrisma::Esegui(){
  std::normal_distribution<double> distribution0(t0_input,_sigmat);        // in questo modo uso la STD per creare le grandezze come se fossero una gaussiana cetrata dove
  t0_misurato=distribution0(generator);                                   // voglio io e con RMS che voglio io
  std::normal_distribution<double> distribution1(t1_input,_sigmat);
  t1_misurato=distribution1(generator);
  std::normal_distribution<double> distribution2(t2_input,_sigmat);
  t2_misurato=distribution2(generator);
   _sommat0 = _sommat0+t0_misurato;

      _sommat1 = _sommat1+t1_misurato;

      _sommat2 = _sommat2+t2_misurato;

      _cont++;
}
double EsperimentoPrisma::Gettheta1(){
  return t1_misurato;
}
double EsperimentoPrisma::Gettheta2(){
  return t2_misurato;
}

double EsperimentoPrisma::Gettheta0(){
  return t0_misurato;
}

double EsperimentoPrisma::Gettheta0in(){
  return t0_input;
}

double EsperimentoPrisma::Gettheta1in(){
  return t1_input;
}

double EsperimentoPrisma::Gettheta2in(){
  return t2_input;
}

double EsperimentoPrisma::Getdm1(){
  return dm1;
}
double EsperimentoPrisma::Getdm2(){
  return dm2;
}

double EsperimentoPrisma::Getn1in(){
  return n1_input;
}

double EsperimentoPrisma::Getn2in(){
  return n2_input;
}

double EsperimentoPrisma::Getn1(){
  return n1_misurato;
}

double EsperimentoPrisma::Getn2(){
  return n2_misurato;
}

double EsperimentoPrisma::GetA(){
  return  a_misurato;
}
double EsperimentoPrisma::GetB(){
  return b_misurato;
}

double EsperimentoPrisma::Getain(){
  return a_input;
}

double EsperimentoPrisma::Getbin(){
  return b_input;
}
double EsperimentoPrisma::Getdm1in(){
  return dm1in;
}
double EsperimentoPrisma::Getdm2in(){
  return dm2in;
}
double EsperimentoPrisma::Get_sigmat () { return _sigmat; }

double EsperimentoPrisma::Get_mediat0 () { return _sommat0/_cont; }

double EsperimentoPrisma::Get_mediat1 () { return _sommat1/_cont; }

double EsperimentoPrisma::Get_mediat2 () { return _sommat2/_cont; }

double EsperimentoPrisma::Get_devA () { return sqrt(_devA/_cont); }

double EsperimentoPrisma::Get_devB () { return sqrt(_devB/_cont); }


double EsperimentoPrisma::Get_corrdm() { 
   
   double xm = _x_dm/_cont;
   double ym = _y_dm/_cont;
   double x2m = _x2_dm/_cont;
   double y2m = _y2_dm/_cont;
   double xym = _xy_dm/_cont;
   double sigmax = sqrt( x2m - pow(xm,2) );
   double sigmay = sqrt( y2m - pow(ym,2) );

   return ( xym - xm*ym ) / ( sigmax * sigmay ); 

}

double EsperimentoPrisma::Get_corrn() {
 
   double xm = _x_dm/_cont;
   double ym = _y_dm/_cont;
   double x2m = _x2_dm/_cont;
   double y2m = _y2_dm/_cont;
   double xym = _xy_dm/_cont;

   double sigmax = sqrt( x2m - pow(xm,2) );
   double sigmay = sqrt( y2m - pow(ym,2) );

   return ( xym - xm*ym ) / ( sigmax * sigmay ); 

}

double EsperimentoPrisma::Get_corrAB() { 

   double xm = _x_AB/_cont;
   double ym = _y_AB/_cont;
   double x2m = _x2_AB/_cont;
   double y2m = _y2_AB/_cont;
   double xym = _xy_AB/_cont;

   double sigmax = sqrt( x2m - pow(xm,2) );
   double sigmay = sqrt( y2m - pow(ym,2) );

   return ( xym - xm*ym ) / ( sigmax * sigmay );

}



void EsperimentoPrisma::Analizza(){
dm1=t1_misurato-t0_misurato;
dm2=t2_misurato-t0_misurato;
n1_misurato=sin((dm1+alpha)/2)/sin(alpha/2);
n2_misurato=sin((dm2+alpha)/2)/sin(alpha/2);
a_misurato= (pow(lambda2*n2_misurato,2)-pow(lambda1*n1_misurato,2))/(lambda2*lambda2-lambda1*lambda1);
b_misurato=(pow(n2_misurato,2)-pow(n1_misurato,2))/(pow(lambda2,-2)-pow(lambda1,-2));

     _devA = _devA + pow(a_input-a_misurato,2);
     _devB = _devB + pow(b_input-b_misurato,2);

//Per la correlazione dei dm
     _x_dm = _x_dm + dm1;
     _y_dm = _y_dm + dm2;
     _x2_dm = _x2_dm + dm1*dm1;
     _y2_dm = _y2_dm + dm2*dm2;
     _xy_dm = _xy_dm + dm1*dm2;

//Per la correlazione degli n
     _x_n = _x_n + n1_misurato;
     _y_n = _y_n + n2_misurato;
     _x2_n = _x2_n + n1_misurato*n1_misurato;
     _y2_n = _y2_n + n2_misurato*n2_misurato;
     _xy_n = _xy_n + n1_misurato*n2_misurato;

//Per la correlazione di A e B
     _x_AB = _x_AB + a_misurato;
     _y_AB = _y_AB + b_misurato;
     _x2_AB = _x2_AB + a_misurato*a_misurato;
     _y2_AB = _y2_AB + b_misurato*b_misurato;
     _xy_AB = _xy_AB + a_misurato*b_misurato;
}

#endif
