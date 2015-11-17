#include <restful_mapper/model.h>
#include <iostream>

using namespace std;
using namespace restful_mapper;

class DI : public Model<DI>
{
public:
	Primary id;
	Field <int> value;
	
	virtual void map_set(Mapper &mapper) const
	{
		mapper.set("value", value);
	}

	virtual void map_get(const Mapper &mapper)
	{
		mapper.get("value", value);
	}
	
	virtual std::string endpoint() const
	{
		return "/di";
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
	DI di = DI::find(1, api);

	cout << di.value;
}

