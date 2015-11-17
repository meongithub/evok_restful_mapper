#include <restful_mapper/model.h>
#include <iostream>

using namespace std;
using namespace restful_mapper;

class AI : public Model<AI>
{
public:
	Primary id;
	Field <double> value;
	Field <double> interval;
	
	virtual void map_set(Mapper &mapper) const
	{
		mapper.set("value", value);
		mapper.set("interval", interval);
	}

	virtual void map_get(const Mapper &mapper)
	{
		mapper.get("value", value);
		mapper.get("interval", interval);
	}
	
	virtual std::string endpoint() const
	{
		return "/ai";
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
	AI ai = AI::find(1, api);
	cout << ai.value;

	ai.interval = 0.1;
	ai.save(api);
}

