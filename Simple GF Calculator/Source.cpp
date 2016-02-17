//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Spring 2016
// CS 303 Network Security (Crypto)
//
// Copyright 2016 Gary Muller
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A simple four-function calculator in GF(2^4). Uses table lookups for the
// multiplicative inverses.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Header files - Standard libraries and classes
#ifndef CORE_DEPENDENCIES_H_
#include <iostream> //default include for functionality
#include <string> //get working string functionality
#include <bitset> //print binary
#endif

//Global variables and defines
//

//Function Prototypes
std::bitset<4> GFAdd(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFMult(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFDiv(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFInv(std::bitset<4>, std::bitset<4>);
//

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//Main Declaration
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
	//main variables
	char operation; //what operation should be done
	std::string string1, string2;
	std::bitset<4> binaryResult; // what 
	//query user for inputs
		//ask user for operation
		std::cout << "What operation would you like to perform (+, -, *, /): ";
		std::cin >> operation;
		//ask user for inputs on that operation
		std::cout << "Enter the first input in a binary form : ";
		std::cin >> string1;
		std::bitset<4> binary1(string1);

		std::cout << "Enter the second input in a binary form: ";
		std::cin >> string2;
		std::bitset<4> binary2(string2);
		
	//perform the operation requested
		switch (operation)
		{
		case '-':
		case '+':
			binaryResult = GFAdd(binary1, binary2);
			break;

		case '*':
			binaryResult = GFMult(binary1, binary2);
			break;

		default:
			std::cout << "try again using the operators shown" << std::endl;
			binaryResult = NULL;
			break;
		}

	//output results

		std::cout << "Result: " << binaryResult << std::endl;

}


std::bitset<4> GFAdd(std::bitset<4> input1, std::bitset<4> input2)
{
	return (input1 ^ input2); //use xor operator to acheive add
}

std::bitset<4> GFMult(std::bitset<4> input1, std::bitset<4> input2)
{
	std::bitset<7> input1big(input1.to_string());
	std::bitset<7> input2big(input2.to_string());
	std::bitset<7> outputbig;
	input1big << 3;

	outputbig = input1big ^ input2big;

	return (input1 ^ input2);
}

int galois_shift_multiply(int x, int y)
{
	int w = 4;
	int prod;
	int i, j, ind;
	int k;
	int scratch[33];

	prod = 0;
	for (i = 0; i < w; i++) {
		scratch[i] = y;
		if (y & (1 << (w - 1))) {
			y = y << 1;
			y = (y ^ 023) & ((1 << 3) - 1);
		}
		else {
			y = y << 1;
		}
	}
	for (i = 0; i < w; i++) {
		ind = (1 << i);
		if (ind & x) {
			j = 1;
			for (k = 0; k < w; k++) {
				prod = prod ^ (j & scratch[i]);
				j = (j << 1);
			}
		}
	}
	return prod;
}