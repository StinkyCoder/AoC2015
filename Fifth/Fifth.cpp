// Fifth.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>    // std::min

typedef std::map<std::string, int> Dict;
class Child {
public:
	// APart
	int threevowels = 0;   
	bool doubleChar = false;   
	bool BadCompany = false;
	// BPart
	bool Overlaps = false;
	bool JumpRepeat = false;
	// Other
	std::string text;
	bool IsNice = false;
};
const std::string  Vowels = "aeiou##";

Child APart(std::string input) {
	Child NewChild;
	NewChild.text = input;
	if (input.find("ab") != std::string::npos || input.find("cd") != std::string::npos ||
		input.find("pq") != std::string::npos || input.find("xy") != std::string::npos) {
		NewChild.BadCompany = true;
	}

	for (unsigned i = 0; i<input.length(); ++i) {
		char c = input.at(i);
		if (Vowels.find(c) != std::string::npos) NewChild.threevowels++;
		if (i > 0) {
			if (input.at(i - 1) == input.at(i)) {
				NewChild.doubleChar = true;
			}
		}
	}
	return NewChild;
}

Child BPart(std::string input) {
	Child NewChild;
	NewChild.text = input;
	for (unsigned i = 0; i < input.length() - 2; i++) {
		std::string pair = input.substr(i, 2);
		std::vector<size_t> positions; // holds all the positions that sub occurs within str

		size_t pos = input.find(pair, 0);
		while (pos != std::string::npos)
		{
			positions.push_back(pos);
			pos = input.find(pair, pos + 2);
		}
		if (positions.size() > 1) {
			NewChild.JumpRepeat = true;
		}
		if (input.at(i) == input.at(i + 2)) {
			NewChild.Overlaps = true;
		}
	}
	if (NewChild.Overlaps && NewChild.JumpRepeat) NewChild.IsNice = true;
	return NewChild;
}

int main()
{
	std::vector<Child> ChildList;
	int NrOfChildren = 0;
	int NrOfNaughty = 0;
	int NrOfNice = 0;
	bool moveOn = true;
	std::string input;

	while (moveOn) {
		std::cout << "Please, enter your input: ";
		std::getline(std::cin, input);
		if (input.size() == 0) {
			break;
		}
		else {
			NrOfChildren++;
			Child NewChild = BPart(input);
			if (NewChild.IsNice) NrOfNice++;
			else NrOfNaughty++;
			ChildList.push_back(NewChild);
		}
	}
	
	std::cout << "TotalNumberOfChildren: " << NrOfChildren << '\n';
	std::cout << "TotalNumberOfNaughty: " << NrOfNaughty << '\n';
	std::cout << "TotalNumberOfNice: " << NrOfNice << '\n';

	std::getline(std::cin, input);
	return 0;
}
