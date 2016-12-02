// Sixth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>


enum Operation { TurnOn, TurnOff,Toggle };

class Light {
public:
	int Powerlevel = 0;
	bool Powered = false;
	void DoOperation(Operation op) {
		if (op == TurnOn) {
			Powered = true;
			Powerlevel++;
		}
		else if (op == TurnOff) {
			Powered = false;
			Powerlevel--;
			if (Powerlevel < 0) Powerlevel = 0;
		}
		else if (op == Toggle) {
			Powered = !Powered;
			Powerlevel += 2;
		}
	}
};

typedef std::vector < std::vector<Light> > LightArray;

std::vector<std::string> Split(std::string input, char delim) {
	std::stringstream ss;
	std::vector<std::string> seglist;
	std::string segment;
	ss.str(input);
	while (std::getline(ss, segment, delim))
	{
		seglist.push_back(segment);
	}
	return seglist;
}

class Command {
public:
	Operation op;
	int minX, minY;
	int maxX, maxY;
	void ParseCommand(std::vector<std::string> List) {
		int i = 0;
		if (List[i] == "turn") {
			i++;
			if (List[i] == "on") op = TurnOn;			
			else op = TurnOff;	
		}
		else op = Toggle;	
			i++;
		parseCoord(List[i], List[i + 2]);
	}
private:
	void parseCoord(std::string coord1, std::string coord2) {
		std::vector<std::string> Coord1 = Split(coord1,',');
		std::vector<std::string> Coord2 = Split(coord2,',');
		minX = stoi(Coord1[0]);
		minY = stoi(Coord1[1]);
		maxX = stoi(Coord2[0]);
		maxY = stoi(Coord2[1]);
	}
};


int main()
{
LightArray LightArray;
	std::string input;
	for (int x = 0; x < 1000; x++) {
		std::vector<Light> LigthString;
		for (int y = 0; y < 1000; y++) {
			Light NewLight;
			LigthString.push_back(NewLight);
		}
		LightArray.push_back(LigthString);
	}
	while (true) {
		std::cout << "Please, enter your input: ";
		std::getline(std::cin, input);
		if (input.size() == 0) {
			break;
		}
		else {
			Command Command;
			std::vector<std::string> List = Split(input, ' ');
			Command.ParseCommand(List);
			for (int x = Command.minX; x <= Command.maxX; x++) {
				for (int y = Command.minY; y <= Command.maxY; y++) {
					LightArray[x][y].DoOperation(Command.op);
				}
			}
		}
	}
	int TotalPowerLevel = 0;
	int LightsOn = 0;
	for (int x = 0; x < 1000; x++) {
		for (int y = 0; y < 1000; y++) {
			if (LightArray[x][y].Powered) LightsOn++;
			 TotalPowerLevel+= LightArray[x][y].Powerlevel;
		}
	}
	std::cout << "NrOfLightsOn: "<< LightsOn << '\n';
	std::cout << "TotalPowerLevel: " << TotalPowerLevel << '\n';

	std::getline(std::cin, input);
    return 0;
}

