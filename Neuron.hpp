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
		
		//Setter
		void setBuffer(int i, double potential);
		
		bool isExcitatory();
		bool isRefractory();
		double backgroundNoise();
		bool updateNeuronState(int time, double I);
		void updateNeuronPotential(double I);
		void updatePotentialWithPoisson(int time, double I);
		bool isReceivingSignal(Neuron neuron);
		void getMessage(Neuron* n);
		void simulation(int simulation_time, double i_ext);
		void addConnexions(int idx);
		
	private:
		double mb_potential;
		int nb_spikes;
		std::vector<double> time_spikes;
		int clock_;
		double refractory_time;
		bool state; //if the neuron is spiking it's state is "1", else it is "0"
		bool type;
		std::array <double, 29> buffer;
		std::vector<int> connexions;
		
};
