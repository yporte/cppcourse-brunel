#include "Network.hpp"
#include "gtest/include/gtest/gtest.h"

/**
 * Constructor of network class
 */
 
Network::Network()
{	 
	//fill the network 
	bool isExcitator=true;
	for(int i(0);  i<NB_TOT; ++i){
		if(i<NB_EXCITATOR){
			//add NB_EXCITATOR excitators neurons in the network
			isExcitator=true;
		}else{
			//add (NB_TOT-NB_EXCITATOR) inhibitors neurons in the network
			isExcitator=false;
		}
		network.push_back(new Neuron(isExcitator));
	}

	//choose randomly CE and CI connexions 
	
	std::vector<int> table;
	for(size_t i(0); i < network.size(); ++i){
		table = randomChoice(0,NB_EXCITATOR,CE, true);
		for (auto t : table){
			assert(t<(int)network.size());
			network[i]->addConnexions(t);
		}
		table.clear();
		table = randomChoice(NB_EXCITATOR,NB_EXCITATOR+NB_INHIBITOR, CI, false);
		for(auto t : table){
			assert(t<(int)network.size());
			network[i]->addConnexions(t);
		}
		table.clear();
	}
	table.clear();
}


/**
 * Destructor of network class
 */

Network::~Network()
{
	for (auto& neuron: network)
	{
		delete neuron;
		neuron=nullptr;
	}
}

/**
 * @return the network (the vectors containing all the neurons of the simulation) 
 */
std::vector <Neuron*> Network::getNetwork()
{
	return network;
}


/**
 *@return the number of connexions in the network
*/
int Network::getNbConnexions(){
	int nb=0;
	for (size_t i(0); i< network.size(); ++i){
				nb += (int)network[i]->getConnexions().size();
	}
	return nb;
}


/** 
 *@param time : time of the simulation
 *@param intensity: intensity of the current
 */
void Network::update(int time, double intensity)		
{
	//We update all the neurons of the network and check their connections
	for(auto& n : network){
		for(auto t : n->getConnexions()){
			assert(t<(int)network.size());
			n->getMessage(network[t]);
		}
	}
	for(auto& n : network){
			n->updatePotentialWithPoisson(time, intensity);
	}
}

/**
 *this method chooses random numbers between two bounderies.
 *@param a: lower borne
 *@param b: higher borne
 *@param connexion: the number of random numbers we want
 *@param t: the type of the neuron (we distinguish if the neuron is excitator or inhibitor)  
 *@return a vector<int> containing all the randomly choosen numbers 
 */
 
 
std::vector<int> Network::randomChoice(int a, int b, int connexion, bool t){
	std::default_random_engine random;
	std::uniform_int_distribution<int> disN(a, b);
    std::uniform_int_distribution<int> dis2N(a, b);
    
    //we declare a table that will store all the choosen numbers
    std::vector<int> table;
    //we clear it
    table.clear();
     
	int i(0);
	do{
		int aleatory(0);
		//if the neuron is excitator
		if(t==true){
			aleatory = disN(random);
		//if the neuron is inhibitor
		}else{
			aleatory = dis2N(random);
		}
		//we add the randomly choosen number in the table
		table.push_back(aleatory);
		++i;
	}while (i < connexion);
	return table;
}


