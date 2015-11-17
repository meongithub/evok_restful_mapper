#include <restful_mapper/model.h>
#include <iostream>
using namespace std;
using namespace restful_mapper;

class Relay : public Model<Relay>
{
public:
	Primary id;
	Field<string> circuit;
	Field<int> value;
	Field<bool> pending;
	Field<string> dev;

	virtual void map_set(Mapper &mapper) const
	{
		//mapper.set("id", id);
		//mapper.set("circuit", circuit);
		mapper.set("value", value);
		//mapper.set("pending", pending);
		//mapper.set("dev", dev);
	}
	
	virtual void map_get(const Mapper &mapper)
	{
		//mapper.get("id", id);
		//mapper.get("circuit", circuit);
		mapper.get("value", value);
		//mapper.get("pending", pending);
		//mapper.get("dev", dev);
	}

	virtual std::string endpoint() const
	{
		return "/relay";
	}

	virtual const Primary &primary() const
	{
		return id;
	}

};

int main()
{
	Api api;
	api.set_url("localhost:80/rest");
	Relay relay = Relay::find(1, api);
	
	Api api2;
	api2.set_url("localhost:80/rest");
	Relay relay2 = Relay::find(2, api);
	std::cout << relay.value << endl;
	std::cout << relay2.value << endl;

	//Relay relay;
	//relay.value = (int) 1;
	//relay.save(api);

	relay.value = 0;
	relay.save(api);
	//std::cout << endl << relay.value << endl << relay.id << relay.circuit << endl;
	//relay.save(api);
	//std::cout << relay.value;
	return 0;
}
