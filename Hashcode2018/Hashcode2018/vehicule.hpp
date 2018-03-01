#define VEHICULE_DONE 1;
#define VEHICULE_NOT_DONE 0;


class Vehicule : {
public:
	Vehicule();
	~Vehicule() = default ;
	int	set_ride_coord();
	std::vector<std::pair<int, int>>  _pos;
	std::vector<std::pair<int, int>>  _dest;
};