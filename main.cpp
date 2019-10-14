#include "SimulationControl.h"

#ifdef _DEBUG
#include "test.h"

int main(int argc, char * argv[]) 
{
	return run(argc, argv);
}

#else

int main(int argc, const char * argv[])
{

	SimulationControl* controller = new SimulationControl();
	//run the simulation
	controller->run();
	
	delete controller;
	
	
	return 0;
}

#endif

