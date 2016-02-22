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
std::bitset<4> galiosField16[16] =
{
	std::bitset<4>("0000"),
	std::bitset<4>("0001"),
	std::bitset<4>("0010"),
	std::bitset<4>("0011"),
	std::bitset<4>("0100"),
	std::bitset<4>("0101"),
	std::bitset<4>("0110"),
	std::bitset<4>("0111"),
	std::bitset<4>("1000"),
	std::bitset<4>("1001"),
	std::bitset<4>("1010"),
	std::bitset<4>("1011"),
	std::bitset<4>("1100"),
	std::bitset<4>("1101"),
	std::bitset<4>("1110"),
	std::bitset<4>("1111")
};
//

//Function Prototypes
std::bitset<4> GFAdd(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFMult(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFDiv(std::bitset<4>, std::bitset<4>);
std::bitset<4> findInverse(std::bitset<4>);
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
		case '-': //subtraction is the same as addition in mod(2); therefore only one function is needed
		case '+':
			binaryResult = GFAdd(binary1, binary2);
			break;

		case '*':
			binaryResult = GFMult(binary1, binary2);
			break;
		case '/':
			binaryResult = GFDiv(binary1, binary2);
			break;
		default:
			std::cout << "try again using the operators shown" << std::endl;
			binaryResult = NULL;
			break;
		}

	//output results

		std::cout << "Result: " << binaryResult << std::endl;

}


std::bitset<4> GFAdd(std::bitset<4> input1, std::bitset<4> input2) //adding is the same as XOR 
{
	return (input1 ^ input2); // ^ operator is XOR
}

std::bitset<4> GFMult(std::bitset<4> input1, std::bitset<4> input2)
{
	std::bitset<8> input1big(input1.to_string()); //expand the inputs to allow for calculations
	std::bitset<8> input2big(input2.to_string());
	std::bitset<8> primitive("10011");	// the primitive/irreducible polynomial function in the GF(2^4) field
	std::bitset<8> one("0001");		// one(1) in binary 
	std::bitset<8> maxbits("1111");	// sixteen(16) in binary / the max value that can be stored in 4 bits
	std::bitset<8> productbig("0000");	// the eventual product of the multiplication 

	while (input2big.to_ulong()) {
		if ((input2big & one).to_ulong() == 1) // if b is odd, then add the corresponding a to p (final product = sum of all a's corresponding to odd b's)
			productbig ^= input1big;				// since we're in GF(2^m), addition is an XOR

		if ((input1big & maxbits).to_ulong() >= 16)	// GF modulo: if input1 >= 16, then it will overflow when shifted left, so reduce
			input1big = (input1big << 1) ^ primitive;		// XOR with the primitive polynomial x^4 + x + 1 
		else
			input1big <<= 1;	// equivalent to a*2
		input2big >>= 1;	// equivalent to b // 2
	}
	std::bitset<4> product((productbig.to_string()).erase(4));
	return product;

}

// http://web.eecs.utk.edu/~plank/plank/papers/CS-07-593/
// http://mathworld.wolfram.com/IrreduciblePolynomial.html
// http://www.cprogramming.com/tutorial/bitwise_operators.html
// https://en.wikipedia.org/wiki/Finite_field_arithmetic
// http://www.doc.ic.ac.uk/~mrh/330tutor/ch04s04.html


std::bitset<4> GFDiv(std::bitset<4> input1, std::bitset<4> input2) //division is the same as multiplying by the inverse
{
	std::bitset<4> result;
	std::bitset<4> inverse;
	
	inverse = findInverse(input1);
	result = GFMult(inverse, input2);
	
	return result;
}

std::bitset<4> findInverse(std::bitset<4> input1) //brute force inverse finder
{
	std::bitset<4> product("0000"); // create and initialize the return product
	std::bitset<4> comparison("0001"); //one in binary
	int count = 0;

	while (product != comparison) //we know we found the inverse when the result is '0001' or one(1)
	{
		product = GFMult(input1, galiosField16[count]);
		count++;
	}
	return product;
}