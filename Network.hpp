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
	
		void update(int steps, double intensity);
		int getNbConnexions();	
		std::vector <Neuron*> getNetwork();
		std::vector<int> randomChoice(int a, int b, int connexion, int x);
	
		
	private:
		std::vector <Neuron*> network;	
}; 