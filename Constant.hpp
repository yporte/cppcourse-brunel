#pragma once
#include <iostream>


constexpr double  TAU(20.0);                   //membrane time constant
double const R(20.0);                          //membrane resistance                
constexpr double V_TH(20.0);                   //treshold value of the membrane potential (if the neuron's potential goes above it, the neuron spikes) 
double const V_REST(0.0);					   //after a spike, the membrane potential goes to that value and stays to that value during the RERACT_TIME  
double const DT(1);                            //step time           
int const REFRACT_TIME(3);                     //time during which the neuron stays inactive after a spike       
int const T_START(0);						   //time to which we begin the simulation
int const T_STOP(1000);				    	   //time to which we end the simulation
double const STEP(0.1); 					   //step
constexpr double J(0.2);					   //external potential
double const G=3;								   //JI/JE ratio	
double const JE(0.1);                          //constant we add to the membrane potential if a neuron receives a signal from an excitatory neuron 
double const JI=-G*JE;	                       //constant we add to the membrane potential if a neuron receives a signal from an inhibitory neuron 
double const DELAY(1.5);                       //delay after wich the post synaptic neuron responds to the presynaptic signal  
int const NB_EXCITATOR(10000);                 //total number of excitatories neurons in the simulation 
int const NB_INHIBITOR(2500); 				   //total number of inhibitories neurons in the simulation 
int const NB_TOT(12500);					   //total number of neurons in the simulation 
constexpr int CE=(0.1*NB_EXCITATOR);		   //number of connexions to excitatories neurons 
constexpr int CI=(0.1*NB_INHIBITOR);		   //number of connexions to inhibitories neurons 
constexpr double ETA(2);
constexpr double V_POISSON=(ETA*V_TH)/(J*TAU); //parameter for the poisson distribution to generate the background noise
 
