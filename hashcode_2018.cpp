// hashcode_2018.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>



enum class ReadingState : char
{
   Start,
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

   // Reading input file
   while (std::getline(std::cin, line))
   {
      std::vector<std::string> words;
      split(line, " ", words);

      switch (state)
      {
         case ReadingState::Start:
         {
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

