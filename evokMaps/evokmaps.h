#ifndef EVOK_MAPS_H
#define EVOK_MAPS_H

#include "restful_mapper/model.h"

using namespace std;
using namespace restful_mapper;

class Relay: public Model<Relay>
{
	public: 
		Primary id;
		Field<int> value;
		virtual void map_set(Mapper &mapper) const;
		virtual void map_get(const Mapper &mapper);
		virtual std::string endpoint() const;
		virtual const Primary &primary() const;
};

class DI: public Model<DI>
{
	public: 
		Primary id;
		Field<int> value;
		virtual void map_set(Mapper &mapper) const;
		virtual void map_get(const Mapper &mapper);
		virtual std::string endpoint() const;
		virtual const Primary &primary() const;
};

class AI: public Model<AI>
{
	public: 
		Primary id;
		Field<double> value;
		Field<double> interval;
		virtual void map_set(Mapper &mapper) const;
		virtual void map_get(const Mapper &mapper);
		virtual std::string endpoint() const;
		virtual const Primary &primary() const;
};



#endif
