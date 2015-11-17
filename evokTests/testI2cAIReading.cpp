#include "pigpio.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include <chrono>
using namespace std::chrono;

int main()
{
	gpioInitialise();
	int handle = i2cOpen(1, 0x68, 0);

	ofstream AIStream; 
	AIStream.open("AIReadLog.txt");
	for (int i=0; i<50; i++)
	{
		high_resolution_clock::time_point t1= high_resolution_clock::now();
		
		char in[128];

		i2cWriteDevice(handle, "\x10", 1);

		i2cReadDevice(handle, in, 3);
		char* current = in;
		bitset<8> data1(*current);
		++current;
		bitset<8> data2(*current);
		++current;
		bitset<8> config(*current);
		
		while(config[7])
		{
			i2cReadDevice(handle, in, 3);
			char* current = in;
			bitset<8> temp1(*current);
			data1 = temp1;
			++current;
			bitset<8> temp2(*current);
			data2 = temp2;
			++current;
			bitset<8> temp3(*current);
			config = temp3;
		}

		string data_bit_str = data1.to_string() + data2.to_string();

		data_bit_str = data_bit_str.erase(0, 4);

		bitset<12> data(data_bit_str);

		if (data[11] == 1)
		{
			data.flip();
			for(int i=0; i<data.size(); ++i)
			{
				if (data[i]) { data[i] = 0;}
				else { data[i] = 1; break; }
			}
		}

		double convert = double(data.to_ulong())/1000.0;
		convert = convert*5.56;

	
		double value = convert;
		high_resolution_clock::time_point t2= high_resolution_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
		AIStream << std::fixed << std::setprecision(13) << value << "; blocking time: " << duration << std::endl;
		usleep(100*1000);	
	}
	
	AIStream.close();
	i2cClose(handle);
	gpioTerminate();
	return 0;
	
}

	

	
