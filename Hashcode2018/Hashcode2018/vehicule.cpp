#include "vehicule.hpp"

Vehicule::Vehicule(std::vector src, std::vector dest)
 : _pos(src),
   _dest(dest)
{
}

int Vehicule::move()
{
	if (_pos.first == _dest.first) {
		_pos.second += _pos.second > _dest.second ? -1 : -1;
	} else if (_pos.second != _dest.second) {
		_pos.first += _pos.first > _dest.first ? -1 : -1;
	} else
		return (VEHICULE_DONE);
	return (VEHICULE_NOT_DONE)
}