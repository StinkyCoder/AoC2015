// Sixth.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>


enum Operation { ASSIGN, OR, LSHIFT, RSHIFT, AND, NOT };

typedef std::map<std::string, unsigned short> Wires;
typedef std::vector<std::string> StrList;
typedef std::map<std::string, unsigned short>::iterator it_type;
Wires wires;

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

class Connection {
public:
	bool Isdependent;
	Operation op;
	unsigned short InValue1;
	unsigned short InValue2;
	unsigned short EndValue;
	std::string  Desitination;
};

unsigned short* GetWire(std::string  c) {
	if (wires.count(c) == 0) wires[c] = 0;
	return &wires.at(c);
}

unsigned short GetValue(std::string c) {
	if (wires.count(c) == 0) wires[c] = 0;
	return wires.at(c);
}

Connection ParseCommand(std::string input) {
	Connection Command;
	StrList List = Split(input, ' ');
	if (List.size() == 3) {
		Command.op = ASSIGN;
		try {
			Command.EndValue = stoi(List[0]);
			Command.Isdependent = false;
		}
		catch (...) {
			Command.Isdependent = true;
			Command.EndValue = GetValue(List[0]);
		}
		Command.Desitination = List[2];
	}
	else if (List.size() == 4) {
		Command.op = NOT;
		Command.InValue1 = GetValue(List[1]);
		Command.Desitination = List[3];
	}
	else if (List.size() == 5) {
		if (List[1] == "AND")Command.op = AND;
		else if (List[1] == "OR")  Command.op = OR;
		else if (List[1] == "RSHIFT")  Command.op = RSHIFT;
		else if (List[1] == "LSHIFT")  Command.op = LSHIFT;
		Command.Isdependent = false;
		try {
			Command.InValue1 = stoi(List[0]);
		}
		catch (...) {
			Command.Isdependent = true;
			Command.InValue1 = GetValue(List[0]);
		}
		try {
			Command.InValue2 = stoi(List[2]);
		}
		catch (...) {
			Command.Isdependent = true;
			Command.InValue2 = GetValue(List[2]);
		}
		Command.Desitination = List[4];
	}
	return Command;
}

void PreformCommand(Connection Command) {
	if (Command.op == AND || Command.op == OR) {
		if (Command.op == AND ) Command.EndValue = Command.InValue1 &  Command.InValue2;
		else if (Command.op == OR ) Command.EndValue = Command.InValue1 | Command.InValue2;
		unsigned short* Wire = GetWire(Command.Desitination);
		*Wire = Command.EndValue;
	}
	else if (Command.op == LSHIFT || Command.op == RSHIFT) {
		if (Command.op == LSHIFT) Command.EndValue = Command.InValue1 << Command.InValue2;
		else if (Command.op == RSHIFT) Command.EndValue = Command.InValue1 >> Command.InValue2;
		unsigned short* Wire = GetWire(Command.Desitination);
		*Wire = Command.EndValue;
	}
	else if (Command.op == NOT) {
		Command.EndValue = ~Command.InValue1;
		unsigned short* Wire = GetWire(Command.Desitination);
		*Wire = Command.EndValue;
	}
	else if (Command.op == ASSIGN) {
		unsigned short* Wire = GetWire(Command.Desitination);
		*Wire = Command.EndValue;
	}
}

int main()
{
	std::string input;
	while (true) {
		std::cout << "Please, enter your input: ";
		std::getline(std::cin, input);
		if (input.size() == 0) {
			break;
		}
		else {
			Connection Command = ParseCommand(input);
			PreformCommand(Command);
		}
	}

	for (it_type iterator = wires.begin(); iterator != wires.end(); iterator++) {
		std::cout << iterator->first << ": " << iterator->second << '\n';
	}
	std::getline(std::cin, input);
	return 0;
}

