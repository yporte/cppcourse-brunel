#include "Network.hpp"

//constructor
Network::Network()
{
	network.clear();
	bool isExcitator=true;
	for(int i(0);  i<NB_TOT; ++i){
		if(i<NB_EXCITATOR){
			bool isExcitator=true;
		}else{
			bool isExcitator=false;
		}
		network.push_back(new Neuron(isExcitator));
	}
	
	//choose random connexions 
	std::vector<int> table;
	for(size_t i(0); i < network.size(); ++i){
		table = randomChoice(0,NB_EXCITATOR,CE,i);
		for (auto t : table){
			network[i]->addConnexions(t);
		}
		table.clear();
		table = randomChoice(NB_EXCITATOR,NB_EXCITATOR+NB_INHIBITOR, CI, i);
		for(auto t : table){
			network[i]->addConnexions(t);
		}
		table.clear();
	}
}

//destructor

Network::~Network()
{
	for (auto& neuron: network)
	{
		delete neuron;
		neuron=nullptr;
	}
}


std::vector <Neuron*> Network::getNetwork()
{
	return network;
}


/**
 * update the network 
 *@param steps 
 *@param intensity
 * */

void Network::update(int steps, double intensity)		
{
	//We update all the Neurons and check if they are connected or not
	for(auto& n : network){
		for(auto t : n->getConnexions()){
			n->getMessage(network[t]);
		}
	}
	for(auto& n: network){
		n->updatePotentialWithPoisson(steps, intensity);
	}
	std::cout<<"potentiel:"<<network[1]->getPotential()<<"   spikes:"<<network[1]->getNbSpikes()<<"     time:"<< steps<<std::endl;
	std::cout<<"potentiel:"<<network[2]->getPotential()<<"   spikes:"<<network[2]->getNbSpikes()<<"     time:"<< steps<<std::endl;
	
}


int Network::getNbConnexions(){
	int nb;
	for (size_t i(0); i< network.size(); ++i){
				nb += (int)network[i]->getConnexions().size();
	}
	return nb;
}


std::vector<int> Network::randomChoice(int a, int b, int connexion, int x){
	std::default_random_engine random; 
    std::uniform_int_distribution<int> disN(a, b);
    std::vector<int> table;
    table.clear(); //make sure there is nothing inside
	int i(0);
	do{
		int aleatory(0);
		aleatory = disN(random);
		if(aleatory != x){
			table.push_back(aleatory);
			++i;
		}
	} while (i < connexion);
	
	return table;
   
}

