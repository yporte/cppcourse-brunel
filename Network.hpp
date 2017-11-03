#pragma once
#include "Neuron.hpp"
#include <memory>
#include <cmath>
#include <iostream>
#include "Constant.hpp"
#include <list>
#include <array>
#include <vector>
#include <random>
#include <fstream>

class Network 
{
	public :
		//Constructor
		Network();
		
		//Destructor
		~Network();
	
	
		//Getter
		int getNbConnexions();	
		std::vector <Neuron*> getNetwork();
		
		void update(int time, double intensity);
		
		std::vector<int> randomChoice(int a, int b, int connexion, bool t);
	
		
	private:
		std::vector <Neuron*> network;	 //contains all the neuons of the simulation 
};
