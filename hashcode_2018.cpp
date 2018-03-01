// hashcode_2018.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>



struct Ride
{
   int startx;
   int starty;
   int endx;
   int endy;
   int earliest_start;
   int last_finish;
   int last_start;
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
            rideList[currentRide]->startx = atoi(words[0].c_str());
            rideList[currentRide]->starty = atoi(words[1].c_str());
            rideList[currentRide]->endx = atoi(words[2].c_str());
            rideList[currentRide]->endy = atoi(words[3].c_str());
            rideList[currentRide]->earliest_start = atoi(words[4].c_str());
            rideList[currentRide]->last_finish = atoi(words[5].c_str());
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


   //Writing output results
   return 0;
}

