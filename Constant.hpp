#pragma once
#include <iostream>


constexpr double  TAU(20.0);      //membrane time constant
double const R(20.0);        //membrane resistance                
constexpr double V_TH(19.8);     //valeur seuil du potentiel de membrane 
double const V_REST(0.0);
double const DT(1);          //pas de temps           
int const REFRACT_TIME(2);   //temps pendant lequel le neurone reste inactif apres un spike       
int const T_STOP(100);
int const T_START(0); 
constexpr double  JE(0.1);  //constant we add to the membrane potential if a neuron receives a signal from an excitatory neuron 
double const JI(0.5);		   //constant we add to the membrane potential if a neuron receives a signal from an inhibitory neuron 
double const DELAY(1.5); //delay after wich the post synaptic neuron responds 
double const STEP(0.1); 
int const NB_EXCITATOR(10000);
int const NB_INHIBITOR(2500);
int const NB_TOT(12500);
constexpr int CE=(int) (0.1*NB_EXCITATOR);
constexpr int CI=(int) (0.1*NB_INHIBITOR);
constexpr double V_EXT=V_TH/(CE*JE*TAU);
