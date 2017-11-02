#include "Neuron.hpp"

//constructor
Neuron::Neuron(bool classe) : state(false), buffer({0}), type(classe), refractory_time(0.0)
{
	connexions.clear();
	time_spikes.clear();
	nb_spikes=0;
}


//Destructor
Neuron::~Neuron()
{}

//give the neuron's membrane potential
double Neuron::getPotential() const
{
	return mb_potential;
}

//give the number of spikes
int Neuron::getNbSpikes() const
{
	return nb_spikes;
}


//give the time
std::vector<double>  Neuron::getTime() const
{
	return time_spikes;
}


// get the list of all connections
std::vector<int> Neuron::getConnexions() const {
	return connexions;
}

int Neuron::getConnexionsForOneNeuron() const{
	return getConnexions().size();
}

//tells if the neron is spiking or not
bool Neuron::isSpiking() const
{
	return state;
}

bool Neuron::isExcitatory()
{
	return type;
}

bool Neuron::isRefractory()
{
	return(refractory_time!=0);	
}
	
double Neuron::backgroundNoise()
{
	//generates a background noise following a poisson distribution
	std::random_device rd;  
    std::mt19937 gen(rd());
    std::poisson_distribution<> poissonGen(V_POISSON);
    return (JE*poissonGen(rd));
}

bool Neuron::updateNeuronState(int time, double I)
{
	
	state=false; //the neuron isn't spiking
	// if the membrane potential exceeds the threshold, we emit a spike
	if (mb_potential >=V_TH) {
		mb_potential = V_REST;
		state = true;
		++nb_spikes;
		time_spikes.push_back(time);
		refractory_time=REFRACT_TIME;
	}
		
	if (isRefractory()) {
		//the membrane potential resets to zero if there was a spike
		mb_potential = V_REST;
		--refractory_time;
		return state;
	}
	
	// update the membrane potential		
	updateNeuronPotential(I);
		
	++clock_;
	return state;
}


void Neuron::updateNeuronPotential(double I) 
{
	//si le buffer du neurone post synaptique au pas de temps clock_ contient une valeur, on rajoute cette valeur au potentiel de membrane
	if (buffer[clock_%(int)buffer.size()]!=0.0){
		std::cout<<"BUFFER  "<<buffer[clock_%(int)buffer.size()]<<std::endl;
		mb_potential +=(buffer[clock_%(int)buffer.size()]);
		buffer[clock_%(int)buffer.size()]=0.0;
		std::cout<<"BUFFER 2 "<<buffer[clock_%(int)buffer.size()]<<std::endl;
	}
	//calcul of the membrane potential
	mb_potential=exp(-0.1/TAU)*mb_potential+ I*R*(1.0-exp(-0.1/TAU));
	

}

void Neuron::updatePotentialWithPoisson(int time, double I)
{
	updateNeuronState(time, I);
	if(not isRefractory()){
		// we add a background noise
		mb_potential += backgroundNoise();
	}
}


//when the pre synaptic neuron is spiking, we had the constant J in the post synaptic neuron buffer with the delay 
void Neuron::getMessage(Neuron* n)
{
	if (n->isSpiking()==true)
	{
		if(n->isExcitatory()==true){
			buffer[(int)(clock_+(DELAY/STEP))%(int)buffer.size()]+=JE;
		}else{
			buffer[(int)(clock_+(DELAY/STEP))%(int)buffer.size()]+= JI;
		}
	}
}


void Neuron::simulation(int simulation_time, double i_ext)
{
	int t(T_START);
	do{
		updateNeuronState(t,i_ext);
		++t;
	}while(t<=simulation_time);
}


// add a connexion target
void Neuron::addConnexions(int idx) 
{
	connexions.push_back(idx);
}
	
