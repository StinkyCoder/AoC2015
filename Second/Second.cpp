// Second.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>    // std::min
class Package {
public:
	int length = 0;   // Length of a box
	int width  = 0;  // depth of a box
	int height = 0;   // Height of a box
};


int main()
{
	std::vector<Package> PackageList;
	int NrOfP = 0;
	bool moveOn = true;
	std::string input;
	int TotalPackageFeet = 0;
	int TotalRibbonFeet = 0;

	while (moveOn) {
		std::cout << "Please, enter your input: ";
		std::getline(std::cin, input);
		if (input.size() == 0) {
			break;
		}
		else {
			NrOfP++;
			Package NewPackage;
			std::string current;			
			for (char& c : input) {
				if (c == 'x') {
					if (NewPackage.length == 0) {
						NewPackage.length = stoi(current);
					}
					else if (NewPackage.width == 0) {
						NewPackage.width = stoi(current);
					}					
					current = "";
				}
				else {
					current += c;
				}
			}
				NewPackage.height = stoi(current);
				PackageList.push_back(NewPackage);
		}		
	}
	for (Package P : PackageList) {
		int a = P.length * P.width;
		int b = P.width * P.height;
		int c = P.height * P.length;
		
		int mini = std::min(a, std::min(b, c));
		int RibbonForPackage = P.width*P.height*P.length;
		int longestSide = std::max(P.width,std::max(P.height, P.length));

		if (longestSide == P.width) {
			RibbonForPackage += (P.length + P.length) + (P.height+ P.height);
		}
		else if (longestSide == P.length) {
			RibbonForPackage += (P.width + P.width) + (P.height + P.height);
		}
		else if (longestSide == P.height) {
			RibbonForPackage += (P.length + P.length) + (P.width + P.width);
		}
 
		TotalRibbonFeet += RibbonForPackage;
		TotalPackageFeet += a * 2 + b * 2 + c * 2 + mini;
	}
	std::cout << "TotalNumberOfPackages: " << NrOfP << '\n';
	std::cout << "TotalPackageFeet: " << TotalPackageFeet << '\n';
	std::cout << "TotalRibbonFeet: " << TotalRibbonFeet << '\n';
	
	std::getline(std::cin, input);
	return 0;
}


