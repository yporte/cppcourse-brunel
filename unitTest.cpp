#include "Neuron.hpp"
#include "Network.hpp"
#include "gtest/include/gtest/gtest.h"
#include <iostream>
#include <cmath>


//test the membrane potential of four neurons (two inhibitors and two excitators)
TEST (NeuronTest, MembranePotential) {
	Neuron n(true);
	Neuron n1(false);
	Neuron n2(true);
	Neuron n3(false);
	
	//at the beggining of the simulationm the membrane potential should be around zero
	n.simulation(0, 1.01);
	EXPECT_NEAR(n2.getPotential(),0, 1);
	
	//the neuron should spikes at the time t=924, so it's potential should be near the treshold (20) at the time t=923
	n1.simulation(923, 1.01);
	EXPECT_NEAR(n1.getPotential(), 20, 1);
	
	//right after the spike, the neuron's potential should be equal to zero
	n2.simulation(924, 1.01);
	EXPECT_EQ(n2.getPotential(),0);
	
	//the neuron should be refractory after the spike. Then, it's potential should be around zero at time t=925
	n3.simulation(925, 1.01);
	EXPECT_NEAR(n3.getPotential(), 0, 1);
	
}

//test the number of spikes
TEST(NeuronTest, NumberSpikes){
	Neuron n(true);
	n.simulation(1000, 1.01);
	EXPECT_EQ(n.getNbSpikes(), 1);	
	}

//test if the membrane potential of the neuron is equal to zero when the neuron is refractory
TEST(NeuronTest, RefractoryTest){
	Neuron n(true);
	if(n.isRefractory()==true){
		EXPECT_EQ(n.getPotential(),0.0); 
	}
}

//test the membrane potential
TEST(NeuronTest, PotentialTest){
	Neuron n(true);
	n.updateNeuronState(1, 1.0);
	EXPECT_NEAR(20.0*(1.0-std::exp(0.1/20.0)),n.getPotential(),0.5);
}

//test if we have the right number of connexions for one neuron
TEST(NeuronTest, ConnexionsNeuron){
	Network n;
	//the number of connexions for one neuron should be 1250
	EXPECT_EQ(n.getNetwork()[1]->getConnexionsForOneNeuron(), 1250);
}


//test if we have the right number of connexions in the simulation
TEST(NetworkTest, NbTargets){
	Network n;
	//the total number of connexions should be equal to the number of connexions for one neuron (1250) multiply by the number of neurons (12500)
	EXPECT_EQ(n.getNbConnexions(), 1250*12500);
}


int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
	
}


