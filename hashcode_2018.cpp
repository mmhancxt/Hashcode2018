// hashcode_2018.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <set>
#include <utility>

#define VEHICULE_DONE 1;
#define VEHICULE_NOT_DONE 0;
struct Vehicule
{
   int id;
   int startx;
   int starty;
   int endx;
   int endy;
   std::vector<int> myrides;
   bool status;
   int ride_id;

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
};

std::vector<Vehicule*> vehicules;




struct Ride
{
   int id;
   int startx;
   int starty;
   int endx;
   int endy;
   int earliest_start;
   int last_finish;
   int last_start;
   int length;
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

int getNearestVehicule(int current_time, int last_finish, int startx, int starty)
{
   int best_vehicule = 0;
   int best_distance = -1;
   int new_distance = -1;
   //while (1);

   for (auto vehicule : vehicules) {
      /*new_distance = abs(vehicule->startx - vehicule->endx) + abs(vehicule->starty - vehicule->endy)
         + abs(vehicule->endx - startx) + abs(vehicule->endy - starty);*/
      new_distance = abs(vehicule->startx - startx) + abs(vehicule->starty - starty);

      if (best_distance == -1)
      {
         best_distance = new_distance;
         best_vehicule = vehicule->id - 1;

      }    
      else if (new_distance < best_distance) {
        
         best_distance = new_distance;
         best_vehicule = vehicule->id - 1;
         
      }
      
   }
   vehicules[best_vehicule]->startx = startx;
   vehicules[best_vehicule]->starty = starty;
   return best_vehicule;

}


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
               auto ride = new Ride();
               ride->id = i;
               rideList.push_back(ride);
            }

            for (int i = 0; i < nbVehicules; ++i)
            {
               auto vehicule = new Vehicule();
               vehicule->id = i+1;
               vehicules.push_back(vehicule);
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
            rideList[currentRide]->id = currentRide;
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

   //simulation
   int tick = 0;
   for (auto ride : sortedRides)
   {
      int id_vehicule = getNearestVehicule(tick, ride->last_start, ride->startx, ride->starty);
      vehicules[id_vehicule]->myrides.push_back(ride->id);
      vehicules[id_vehicule]->status = false;
      
      tick += ride->length;
   }
   //while (1);
   //Writing output results
   for (auto vehicule : vehicules)
   {
      //while (1);
      std::cout << vehicule->myrides.size();
      for (auto idride : vehicule->myrides)
      {
         std::cout << " ";
         std::cout << idride;
      }
      std::cout << "\n";
   }
   
   return 0;
}

