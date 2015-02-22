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
    double Getdm1in();
    double Getdm2in();
    double Gettheta0in();
  private:                
    double lambda1,lambda2; 
    double alpha,sigmat;
    double a_input, a_misurato;
    double b_input, b_misurato;
    double n1_input, n1_misurato;
    double n2_input, n2_misurato;
    double t0_input, t0_misurato;
    double t1_input, t1_misurato;
    double t2_input, t2_misurato;
    double dm1,dm2;
    double dm1in,dm2in;
};
EsperimentoPrisma::EsperimentoPrisma() :
  lambda1(579.1E-9),
  lambda2(404.7E-9),
  alpha(60*M_PI/180.),
 sigmat(0.3E-3),
  a_input(2.7),
  b_input(60000E-18)
{
  //calcolo degli indici di rifrazione attesi
  n1_input = sqrt(a_input+b_input/(pow(lambda1,2)));
  n2_input = sqrt(a_input+b_input/(pow(lambda2,2)));
// calcolo dei valori attesi degli angoli misurati
  t0_input = M_PI/2;  //theta0 e' arbitrario
  dm1in = 2.*asin(n1_input*sin(0.5*alpha))-alpha;
  t1_input = t0_input+dm1;
  dm2in = 2.*asin(n2_input*sin(0.5*alpha))-alpha;
  t2_input = t0_input+dm2;
}
void EsperimentoPrisma::Esegui(){
  std::normal_distribution<double> distribution0(t0_input,sigmat);        // in questo modo uso la STD per creare le grandezze come se fossero una gaussiana cetrata dove
  t0_misurato=distribution0(generator);                                   // voglio io e con RMS che voglio io
  std::normal_distribution<double> distribution1(t1_input,sigmat);
  t1_misurato=distribution1(generator);
  std::normal_distribution<double> distribution2(t2_input,sigmat);
  t2_misurato=distribution2(generator);
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

double EsperimentoPrisma::Getdm1in(){
  return dm1in;
}
double EsperimentoPrisma::Getdm2in(){
  return dm2in;
}

void EsperimentoPrisma::Analizza(){
dm1=t1_misurato-t0_misurato;
dm2=t2_misurato-t0_misurato;
n1_misurato=(sin(dm1+alpha)/2)/sin(alpha/2);
n2_misurato=(sin(dm2+alpha)/2)/sin(alpha/2);
a_misurato=pow(lambda2,2)*pow(n2_misurato,2)-pow(n1_misurato,2)*pow(lambda2,2);
b_misurato=(pow(n2_misurato,2)-pow(n1_misurato,2))/(1/pow(lambda2,2)-1/pow(lambda1,2));
}

#endif
