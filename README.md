# cppcourse-brunel

This project consists in a simulation of 12500 neurons as described by Nicolas Brunel in its paper "Dynamics of Sparsely Connected Networks of Excitatory and Inhibitory Spiking Neurons".
As said in the title, there are two types of neurons : excitatory and inhibitory. Each neuron has a membrane potential. When the membrane potential of one neuron reaches the treshold, the neuron spikes and its potential goes back to zero. After a spike, the neuron stays refractory during a given (constant) amount of time. Each neuron is connected to 250 inhibitory neurons and 1000 excitatory ones. Once a neuron has spiked, it sends a signal to its connected neurons (that way, each neuron receives a signal from every spiking neuron who it has a connection with).

we compile with cmake : 
to run the simulation, write on the terminal:  
cmake . 
make
./Neuron

to get the image, go on https://cs116-plot.antoinealb.net/, upload the file called "spikes.dat" which contains the values (number of spikes and time of spikes), and submit
you can also do it directly in the terminal, using the python code written in the image.txt file (copy paste line by line in the terminal)

to run the test, write on the terminal:
cmake .
make
./Neuron_Unit_Test1

to use the doxygen documentation :
write on the terminal :
make doc
this will create an html file, open it, click on any folder (for example classNeuron.html)

to change the parameters of the simulation, change the constants in the file Constant.hpp. For example
-change the constant T_STOP in the constant file 
-change the constant G in the constant file
-change the constant ETA in the constant file

to change the external current of the simulation :
in the main change the second parameter of the function updateStateWithPoisson

after, recompile with make and execute the program.

I executed my program with four differents sets of parameters:
case1: G=3, ETA=2
case2: G=6, ETA=4
case3: G=5, ETA=2
case4: G=4.5 ETA=0.9


