#include "Neuron.hpp"
#include "Network.hpp"
#include "gtest/include/gtest/gtest.h"
#include <iostream>
#include <cmath>

TEST (NeuronTest, MembranePotential) {
	Neuron n(true);
	Neuron n1(true);
	Neuron n2(true);
	Neuron n3(true);
	
	
	n.simulation(0, 1.01);
	EXPECT_NEAR(n2.getPotential(),0, 1);
	
	n1.simulation(923, 1.01);
	EXPECT_NEAR(n1.getPotential(), 20, 1);
	
	n2.simulation(924, 1.01);
	EXPECT_EQ(n2.getPotential(),0);
	
	n3.simulation(925, 1.01);
	EXPECT_NEAR(n3.getPotential(), 0, 1);
	
}

TEST(NeuronTest, NumberSpikes){
	Neuron n(true);
	n.simulation(1000, 1.01);
	EXPECT_EQ(n.getNbSpikes(), 1);	
	}


TEST(NeuronTest, RefractoryTest){
	Neuron n(true);
	if(n.isRefractory()==true){
		EXPECT_EQ(n.getPotential(),0.0); 
	}
}

TEST(NetworkTest, NbTargets){
	Network n;
	EXPECT_EQ(n.getNbConnexions(), 1250*12500);
}

TEST(NeuronTest, PotentialTest){
	Neuron n(true);
	n.updateNeuronState(1, 1.0);
	EXPECT_NEAR(20.0*(1.0-std::exp(0.1/20.0)),n.getPotential(),0.5);
}

int main(int argc, char**argv)
{
	::testing::InitGoogleTest(&argc, argv);
	
	return RUN_ALL_TESTS();
	
}


