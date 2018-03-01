// hashcode_2018.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <fstream>

using namespace std;


#define VEHICULE_DONE 1;
#define VEHICULE_NOT_DONE 0;


struct Vehicule
{
	int id;
	int startx;
	int starty;
	int endx;
	int endy;

	Vehicule(int id_) : id(id_) {}

	int move()
	{
		if (startx == endx) {
			starty += starty > endy ? -1 : 1;
		}
		else if (starty != endy) {
			startx += startx > endx ? -1 : 1;
		}
		else
			return VEHICULE_DONE;

		return VEHICULE_NOT_DONE;

	}

	vector<int> rides;
};


struct Ride
{
	int startx;
	int starty;
	int endx;
	int endy;
	int length;
	int earliest_start;
	int last_finish;
	int last_start;
};

struct  Comp
{
	bool operator()(Ride* R1, Ride* R2)
	{
		if (R1->last_finish < R2->last_finish)
		{
			return true;
		}
		else
		{
			if (R1->last_finish > R2->last_finish)
			{
				return false;
			}
			else
			{
				int dist1 = abs(R1->startx - R1->endx) + abs(R1->starty - R1->endy);
				int dist2 = abs(R2->startx - R2->endx) + abs(R2->starty - R2->endy);

				return dist1 < dist2;
			}
		}

	}
};



enum class ReadingState : char
{
	Start,
	RideInput,
	EndReading
};

void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& results)
{
	std::string::size_type pos = 0, cur = 0;

	while ((pos = str.find(delimiter.c_str(), cur)) != std::string::npos)
	{
		std::string word = str.substr(cur, pos - cur);
		results.emplace_back(word);
		cur = pos + 1;
	}

	std::string word = str.substr(cur, str.length() - cur);
	results.emplace_back(word);
}

int main()
{
	std::string line = "";
	ReadingState state = ReadingState::Start;
	int nbRows = 0, nbColumns = 0, nbVehicules = 0, nbRides = 0, nbBonus = 0, nbSteps = 0;
	std::vector<Ride*> rideList;
	std::set<Ride*, Comp> sortedRides;
	int currentRide = 0;

	// Reading input file
	while (std::getline(std::cin, line))
	{
		std::vector<std::string> words;
		split(line, " ", words);

		switch (state)
		{
		case ReadingState::Start:
		{
			nbRows = atoi(words[0].c_str());
			nbColumns = atoi(words[1].c_str());
			nbVehicules = atoi(words[2].c_str());
			nbRides = atoi(words[3].c_str());
			nbBonus = atoi(words[4].c_str());
			nbSteps = atoi(words[5].c_str());

			for (int i = 0; i < nbRides; ++i)
			{
				rideList.push_back(new Ride());
			}
			state = ReadingState::RideInput;
			break;
		}
		case ReadingState::RideInput:
		{
			int sx = atoi(words[0].c_str());
			int sy = atoi(words[1].c_str());
			int ex = atoi(words[2].c_str());
			int ey = atoi(words[3].c_str());
			rideList[currentRide]->startx = sx;
			rideList[currentRide]->starty = sy;
			rideList[currentRide]->endx = ex;
			rideList[currentRide]->endy = ey;
			rideList[currentRide]->length = abs(ey - sy) + abs(ex - sx);
			rideList[currentRide]->earliest_start = atoi(words[4].c_str());
			rideList[currentRide]->last_finish = atoi(words[5].c_str());
			rideList[currentRide]->last_start = rideList[currentRide]->last_finish - rideList[currentRide]->length;
			currentRide++;

			if (currentRide == nbRides)
			{
				state = ReadingState::EndReading;
			}
			break;
		}
		case ReadingState::EndReading:
		{
			break;
		}
		default:
		{
			break;
		}
		}
	}

	// sorting rides
	for (auto ride : rideList)
	{
		sortedRides.insert(ride);
	}
	//Writing output results

	fstream output;
	output.open("output.txt");


	return 0;
}

