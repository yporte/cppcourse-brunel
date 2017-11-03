#pragma once
#include <iostream>
#include "Constant.hpp"
#include <array>
#include <vector>
#include <random>
#include <cmath>

class Neuron
{
	public:
	
		//Constructor
		Neuron(bool type);
		
		//Destructor
		~Neuron();
		
		//Getter
		double getPotential() const;
		int getNbSpikes() const;
		std::vector<double>  getTime() const;
		std::vector<int> getConnexions() const;
		bool isSpiking() const;
		bool isExcitatory()const;
		int getConnexionsForOneNeuron() const;
		
		//update
		bool updateNeuronState(int time, double I);
		void updateNeuronPotential(double I);
		void updatePotentialWithPoisson(int time, double I);
		
		
		bool isRefractory();
		double backgroundNoise();
		void getMessage(Neuron* n);
		void addConnexions(int idx);
		void simulation(int simulation_time, double i_ext);
		
		
	private:
		bool state;                       //if the neuron is spiking it's state is "1", else it is "0"
		std::array <double, 29> buffer;
		bool type;  		              //tells if the neurone is excitator (true) of inhibitor(false)
		double mb_potential;              //potential of the neuron's membrane
		int nb_spikes;                    //number of spikes of the neuron
		std::vector<double> time_spikes;  //stores the time of each spike
		int clock_; 
		double refractory_time;           
		std::vector<int> connexions;       
		
};
