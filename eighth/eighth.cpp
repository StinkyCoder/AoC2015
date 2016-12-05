// eighth.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

int TotalChar;
int TotalMemory;
int EncodingChar;

void CalculateLine(std::string input){
	TotalChar += input.length();
	for (int i = 1; i < input.length()-1; i++) {
		char c = input[i];
		if (c == 92) {
			if (input[i + 1] == 92) {
				TotalMemory++;
				i++;
			}
			else if (input[i + 1] == '"') {
				TotalMemory++;
				i++;
			}
			else if (input[i + 1] == 'x') {
				TotalMemory++;
				i+= 3;
			}
		} else TotalMemory++;
	}
}

void CalculateLinBe(std::string input) {
	EncodingChar += 6;
	for (int i = 1; i < input.length() - 1; i++) {
		char c = input[i];
		if (c == 92) {
			if (input[i + 1] == 92) {
				EncodingChar += 4;
				i++;
			}
			else if (input[i + 1] == '"') {
				EncodingChar +=4;
				i++;
			}
			else if (input[i + 1] == 'x') {
				EncodingChar +=5;
				i += 3;
			}
		}
		else EncodingChar++;
	}
}


int main()
{
	std::string input;
	TotalChar = 0;
	TotalMemory = 0;
	EncodingChar = 0;
	std::cout << "Please, enter your input: ";
	std::getline(std::cin, input);
	while (input.size() != 0) {
		CalculateLine(input);
		CalculateLinBe(input);
		std::cout << "Please, enter your input: ";
		std::getline(std::cin, input);
	}

	std::cout << "A Part: " << '\n';
	std::cout << "TotalChar: "<< TotalChar<< '\n';
	std::cout << "TotalMemory: "<< TotalMemory << '\n';
	std::cout << "Result: " << TotalChar-TotalMemory << '\n';


	std::cout << "B Part: "  << '\n';
	std::cout << "TotalChar: " << TotalChar << '\n';
	std::cout << "EncodingChar: " << EncodingChar << '\n';
	std::cout << "Result: " << EncodingChar -TotalChar << '\n';
	std::getline(std::cin, input);
	return 0;
}

