#include "Neuron.hpp"
#include "Network.hpp"
#include <fstream>
#include <string>


int main()
{
	Network neuron;
	double time(T_START);
	
	while(time<T_STOP)
	{
		neuron.update(time, 0.0);
		//On incrémente le temps
		time+=DT;
	}
	

	std::ofstream file;
	std::string nom_de_fichier ("spikes.dat");
	file.open(nom_de_fichier.c_str());
	
	for (size_t i(0); i<neuron.getNetwork().size(); ++i){
		for(auto t : neuron.getNetwork()[i]->getTime()){
			file<<t<<'\t'<<i<<'\n';
		}
	}
	
	
	file.close();
	
	return 0;
}


