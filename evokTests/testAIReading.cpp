#include "evokmaps.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <chrono>
using namespace std::chrono;

int main()
{
	Api api;
	api.set_url("localhost:80/rest");
	Relay relay = Relay::find(8, api);
	
	relay.value = 1;
	relay.save(api);

	ofstream AIStream; 
	AIStream.open("AIReadLog.txt");
	for (int i=0; i<1000; i++)
	{
		high_resolution_clock::time_point t1= high_resolution_clock::now();
		AI ai = AI::find(1, api);		
		double value = ai.value;
		high_resolution_clock::time_point t2= high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		AIStream << std::fixed << std::setprecision(13) << value << "; blocking time: " << duration << std::endl;
		usleep(10*1000);	
	}
	
	AIStream.close();
	relay.value = 0;
	relay.save(api);
return 0;
	
}

	

	
