#include "Neuron.hpp"

/**  
 *constructor oh the Neuron class
 *@param classe : the type of the neuron (inhibitor or excitator)
 */
Neuron::Neuron(bool classe) : state(false), buffer({0}), type(classe), refractory_time(0.0)
{
	connexions.clear();
	time_spikes.clear();
	nb_spikes=0;
}


/**
 *Destructor of the Neuron class
 */
Neuron::~Neuron()
{}


/**
 *getter
 @return the neuron's membrane potential
 */
double Neuron::getPotential() const
{
	return mb_potential;
}


/**
 *getter
 *@return the number of spikes
 */
int Neuron::getNbSpikes() const
{
	return nb_spikes;
}


/**
 getter
 *@return the time of the spikes
 */
std::vector<double> Neuron::getTime() const
{
	return time_spikes;
}


/**
 *getter
 *@return the list of all the connections
 */
std::vector<int> Neuron::getConnexions() const {
	return connexions;
}


/**
 *getter
 *@return the state of the neuron (1 if it is spiking, 0 if not)
 */
bool Neuron::isSpiking() const
{
	return state;
}


/**
 *getter
 *@return the type of the neuron (excitator or inhibitor)
 */
bool Neuron::isExcitatory() const
{
	return type;
}


/**
 *@return the number of conexions for one neuron
 */
int Neuron::getConnexionsForOneNeuron() const{
	return getConnexions().size();
}


/**
 *@return if the neuron is refractory or not
 */
bool Neuron::isRefractory()
{
	return(refractory_time!=0);	
}
	

/**
 *@return a random background noise that will be add to the neuron's membrane potential  
 */
double Neuron::backgroundNoise()
{
	//generates a background noise following a poisson distribution
	static std::random_device rd;  
    static std::mt19937 gen(rd());
    static std::poisson_distribution<> poissonGen(V_POISSON);
    //we multiply the random value by JE
    return (JE*poissonGen(rd));
}

/**
 *this method updates the state and the membrane potential of the neuron. 
 *it checks if the potential reaches the treshold and if the neuron is refractory.
 *it does not take into account the background noise but it will be called in another method that will add the background noise
 *@param time : time of the simulation
 *@param I : intensity of the external current
 *@return the state of the neuron (spiking or not spiking)  
 */
bool Neuron::updateNeuronState(int time, double I)
{
	
	// if the membrane potential exceeds the threshold, the neuron emits a spike
	if (mb_potential >=V_TH) {
		state = true;
		//after spiking it's potential goes back to zero
		mb_potential = V_REST;
		++nb_spikes;
		time_spikes.push_back(time);
		//we initialyse de refractory_time to a certain time : the neuron will stay refractory during this amount of time
		refractory_time=REFRACT_TIME;
	}
	
	//check if the neuron is refractorz	
	if (isRefractory()) {
		buffer[clock_%(int)buffer.size()]=0.0; //the buffer does not receive any message when the neuron is refractory
		//the membrane potential is at zero while the neuron is refractory
		mb_potential = V_REST;
		--refractory_time;
		return state;
	}
	
	//we update the membrane potential by calling another method	
	updateNeuronPotential(I);
	
	++clock_;
	state=false; //the neuron isn't spiking
	return state;
}


/**
 *this method update te neuron's membrane potential. it will be called in the updateNeuronState method
 *@param I : intensity of the external current 
 */
void Neuron::updateNeuronPotential(double I) 
{
	//if the neuron's buffer at the time ''clock_'' contains a value, we add this value to the membrane potential
	if (buffer[clock_%(int)buffer.size()]!=0.0){
		mb_potential +=(buffer[clock_%(int)buffer.size()]);
		buffer[clock_%(int)buffer.size()]=0.0;
	}
	//calcul of the membrane potential
	mb_potential=exp(-0.1/TAU)*mb_potential+ I*R*(1.0-exp(-0.1/TAU));
}


/**
 *this method update the membrane potential by calling the method updateNeuronState and add the background noise, if the neuron isn't refractory
 *@param time : time of the simulation
 *@param I: intensity of the external current 
 */
void Neuron::updatePotentialWithPoisson(int time, double I)
{
	updateNeuronState(time, I);
	//check if the neuron is refractory or not
	if(not isRefractory()){
		//we add a background noise if the neuron isn't refractory
		mb_potential += backgroundNoise();
	}
}


/**
 *in this method, we check if a neuron n is spiking. If it is, we add a constant J in the neuron buffer with the delay 
 *if n is excitator, J is equal to JE(0.1), if it is inhibitor, J is equal to JI (-0.5)
 *@param n : the neuron we want to check if it is sending a message or not
 */ 
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


/**
 *@param simulation_time : duration of the simulation
 *@param i_ext : intensity of the external current
 */
void Neuron::simulation(int simulation_time, double i_ext)
{
	int t(T_START);
	do{
		updateNeuronState(t,i_ext);
		++t;
	}while(t<=simulation_time);
}


/**
 *this method adds a connexion target
 *@param idx : we add a connexion in the vector containing all the connexions at the index ''idx''
 */
void Neuron::addConnexions(int idx) 
{
	connexions.push_back(idx);
}
	
