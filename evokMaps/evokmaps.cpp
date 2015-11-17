#include "evokmaps.h"

//RELAY IMPLEMENTATIONS
void Relay::map_set(Mapper &mapper) const
{
	mapper.set("value", value);
}
	
void Relay::map_get(const Mapper &mapper)
{
	mapper.get("value", value);
}

std::string Relay::endpoint() const
{
	return "/relay";
}

const Primary& Relay::primary() const
{
	return id;
}

//DI IMPLEMENTATIONS
void DI::map_set(Mapper &mapper) const
{
	mapper.set("value", value);
}
	
void DI::map_get(const Mapper &mapper)
{
	mapper.get("value", value);
}

std::string DI::endpoint() const
{
	return "/di";
}

const Primary& DI::primary() const
{
	return id;
}

//AI IMPLEMENTATIONS
void AI::map_set(Mapper &mapper) const
{
	mapper.set("value", value);
	mapper.set("interval", interval);
}
	
void AI::map_get(const Mapper &mapper)
{
	mapper.get("value", value);
	mapper.get("interval", interval);
}

std::string AI::endpoint() const
{
	return "/ai";
}

const Primary& AI::primary() const
{
	return id;
}



