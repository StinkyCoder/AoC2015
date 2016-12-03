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
Wires wires;

void SetValue(std::string c, unsigned short val) {
	wires[c] = val;
}

bool GetValue(std::string c, unsigned short &input) {
	try {
		input = stoi(c);
		return true;
	}
	catch (...) {
		if (wires.count(c) > 0) {
			input= wires.at(c);
			return true;
		}
	}	
	return false;
}

class Connection {
public:
	Operation op;
	std::string ID1 = "";
	std::string ID2 = "";
	unsigned short  Input1 = 0;
	unsigned short  Input2 = 0;
	unsigned short EndValue = 0;
	std::string Desitination;

};

typedef std::vector<std::string> StrList;
typedef std::map<std::string, unsigned short>::iterator it_type;
typedef std::vector<Connection> Connections;
Connections cons;

StrList Split(std::string input, char delim) {
	std::stringstream ss;
	StrList seglist;
	std::string segment;
	ss.str(input);
	while (std::getline(ss, segment, delim))
	{
		seglist.push_back(segment);
	}
	return seglist;
}

Connection ParseCommand(std::string input) {
	Connection Command;
	StrList List = Split(input, ' ');
	if (List.size() == 3) {
		Command.op = ASSIGN;
		Command.ID1 = List[0];
		Command.Desitination = List[2];
	}
	else if (List.size() == 4) {
		Command.op = NOT;
		Command.ID1 = List[1];
		Command.Desitination = List[3];
	}
	else if (List.size() == 5) {
		if (List[1] == "AND")Command.op = AND;
		else if (List[1] == "OR")  Command.op = OR;
		else if (List[1] == "RSHIFT")  Command.op = RSHIFT;
		else if (List[1] == "LSHIFT")  Command.op = LSHIFT;
		Command.ID1 = List[0];		
		Command.ID2 = List[2];
		Command.Desitination = List[4];
	}
	return Command;
}

void PreformCommand(Connection* Command) {	
	if (GetValue(Command->ID1, Command->Input1)) {		
		if (Command->op == NOT) {
			Command->EndValue = ~Command->Input1;
			SetValue(Command->Desitination, Command->EndValue);
		}
		else if (Command->op == ASSIGN) {
			SetValue(Command->Desitination, Command->Input1);
		}
		else if (GetValue(Command->ID2, Command->Input2)) {
			if (Command->op == AND || Command->op == OR) {
				if (Command->op == AND) Command->EndValue = Command->Input1 &  Command->Input2;
				else if (Command->op == OR) Command->EndValue = Command->Input1 | Command->Input2;
				SetValue(Command->Desitination, Command->EndValue);
			}
			else if (Command->op == LSHIFT || Command->op == RSHIFT) {
				if (Command->op == LSHIFT) Command->EndValue = Command->Input1 << Command->Input2;
				else if (Command->op == RSHIFT) Command->EndValue = Command->Input1 >> Command->Input2;
				SetValue(Command->Desitination, Command->EndValue);
			}
		}
	}
}

int main()
{
	std::string input;
	std::cout << "Please, enter your input: ";
	std::getline(std::cin, input);
	while (input.size() != 0) {
		Connection Command = ParseCommand(input);
		cons.push_back(Command);
		std::cout << "Please, enter your input: ";
		std::getline(std::cin, input);
	}

	while (wires.size() != cons.size()) {
		for (Connection con : cons) {
			PreformCommand(&con);
		}
	}

	for (it_type iterator = wires.begin(); iterator != wires.end(); iterator++) {
		std::cout << iterator->first << ": " << iterator->second  << '\n';
	}

	std::getline(std::cin, input);
	return 0;
}

