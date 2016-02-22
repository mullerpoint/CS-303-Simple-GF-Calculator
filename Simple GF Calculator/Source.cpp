//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
// Gary Muller
// Spring 2016
// CS 303 Network Security (Crypto)
//
// Copyright 2016 Gary Muller
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A simple four-function calculator in GF(2^4). Can use table lookups
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


//Header files - Standard libraries and classes
#ifndef CORE_DEPENDENCIES_H_
#include <iostream> //default include for functionality
#include <string> //get working string functionality
#include <bitset> //print binary
#include <algorithm> //arrays searching
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
std::bitset<4> GFMultTable[16][16] =  //multiplication table for GF(2^4) mod(2)
{
	/*01*/{ std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"),
	std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"),
	std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"),
	std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000"), std::bitset<4>("0000") },
	/*02*/{ std::bitset<4>("0000"), std::bitset<4>("0001"), std::bitset<4>("0010"), std::bitset<4>("0011"),
	std::bitset<4>("0100"), std::bitset<4>("0101"), std::bitset<4>("0110"), std::bitset<4>("0111"),
	std::bitset<4>("1000"), std::bitset<4>("1001"), std::bitset<4>("1010"), std::bitset<4>("1011"),
	std::bitset<4>("1100"), std::bitset<4>("1101"), std::bitset<4>("1110"), std::bitset<4>("1111") },
	/*03*/{ std::bitset<4>("0000"), std::bitset<4>("0010"), std::bitset<4>("0100"), std::bitset<4>("0110"),
	std::bitset<4>("1000"), std::bitset<4>("1010"), std::bitset<4>("1100"), std::bitset<4>("1110"),
	std::bitset<4>("0011"), std::bitset<4>("0001"), std::bitset<4>("0111"), std::bitset<4>("0101"),
	std::bitset<4>("1011"), std::bitset<4>("1001"), std::bitset<4>("1111"), std::bitset<4>("1101") },
	/*04*/{ std::bitset<4>("0000"), std::bitset<4>("0011"), std::bitset<4>("0110"), std::bitset<4>("0101"),
	std::bitset<4>("1100"), std::bitset<4>("1111"), std::bitset<4>("1010"), std::bitset<4>("1001"),
	std::bitset<4>("1011"), std::bitset<4>("1000"), std::bitset<4>("1101"), std::bitset<4>("1110"),
	std::bitset<4>("0111"), std::bitset<4>("0100"), std::bitset<4>("0001"), std::bitset<4>("0010") },
	/*05*/{ std::bitset<4>("0000"), std::bitset<4>("0100"), std::bitset<4>("1000"), std::bitset<4>("1100"),
	std::bitset<4>("0011"), std::bitset<4>("0111"), std::bitset<4>("1011"), std::bitset<4>("1111"),
	std::bitset<4>("0110"), std::bitset<4>("0010"), std::bitset<4>("1110"), std::bitset<4>("1010"),
	std::bitset<4>("0101"), std::bitset<4>("0001"), std::bitset<4>("1101"), std::bitset<4>("1001") },
	/*06*/{ std::bitset<4>("0000"), std::bitset<4>("0101"), std::bitset<4>("1010"), std::bitset<4>("1111"),
	std::bitset<4>("0111"), std::bitset<4>("0010"), std::bitset<4>("1101"), std::bitset<4>("1000"),
	std::bitset<4>("1110"), std::bitset<4>("1011"), std::bitset<4>("0100"), std::bitset<4>("0001"),
	std::bitset<4>("1001"), std::bitset<4>("1100"), std::bitset<4>("0011"), std::bitset<4>("0110") },
	/*07*/{ std::bitset<4>("0000"), std::bitset<4>("0110"), std::bitset<4>("1100"), std::bitset<4>("1010"),
	std::bitset<4>("1011"), std::bitset<4>("1101"), std::bitset<4>("0111"), std::bitset<4>("0001"),
	std::bitset<4>("0101"), std::bitset<4>("0011"), std::bitset<4>("1001"), std::bitset<4>("1111"),
	std::bitset<4>("1110"), std::bitset<4>("1000"), std::bitset<4>("0010"), std::bitset<4>("0100") },
	/*08*/{ std::bitset<4>("0000"), std::bitset<4>("0111"), std::bitset<4>("1110"), std::bitset<4>("1001"),
	std::bitset<4>("1111"), std::bitset<4>("1000"), std::bitset<4>("0001"), std::bitset<4>("0110"),
	std::bitset<4>("1101"), std::bitset<4>("1010"), std::bitset<4>("0011"), std::bitset<4>("0100"),
	std::bitset<4>("0010"), std::bitset<4>("0101"), std::bitset<4>("1100"), std::bitset<4>("1011") },
	/*09*/{ std::bitset<4>("0000"), std::bitset<4>("1000"), std::bitset<4>("0011"), std::bitset<4>("1011"),
	std::bitset<4>("0110"), std::bitset<4>("1110"), std::bitset<4>("0101"), std::bitset<4>("1101"),
	std::bitset<4>("1100"), std::bitset<4>("0100"), std::bitset<4>("1111"), std::bitset<4>("0111"),
	std::bitset<4>("1010"), std::bitset<4>("0010"), std::bitset<4>("1001"), std::bitset<4>("0001") },
	/*10*/{ std::bitset<4>("0000"), std::bitset<4>("1001"), std::bitset<4>("0001"), std::bitset<4>("1000"),
	std::bitset<4>("0010"), std::bitset<4>("1011"), std::bitset<4>("0011"), std::bitset<4>("1010"),
	std::bitset<4>("0100"), std::bitset<4>("1101"), std::bitset<4>("0101"), std::bitset<4>("1100"),
	std::bitset<4>("0110"), std::bitset<4>("1111"), std::bitset<4>("0111"), std::bitset<4>("1110") },
	/*11*/{ std::bitset<4>("0000"), std::bitset<4>("1010"), std::bitset<4>("0111"), std::bitset<4>("1101"),
	std::bitset<4>("1110"), std::bitset<4>("0100"), std::bitset<4>("1001"), std::bitset<4>("0011"),
	std::bitset<4>("1111"), std::bitset<4>("0101"), std::bitset<4>("1000"), std::bitset<4>("0010"),
	std::bitset<4>("0001"), std::bitset<4>("1011"), std::bitset<4>("1100"), std::bitset<4>("0110") },
	/*12*/{ std::bitset<4>("0000"), std::bitset<4>("1011"), std::bitset<4>("0101"), std::bitset<4>("1110"),
	std::bitset<4>("1010"), std::bitset<4>("0001"), std::bitset<4>("1111"), std::bitset<4>("0100"),
	std::bitset<4>("0111"), std::bitset<4>("1100"), std::bitset<4>("0010"), std::bitset<4>("1001"),
	std::bitset<4>("1101"), std::bitset<4>("0110"), std::bitset<4>("1000"), std::bitset<4>("0011") },
	/*13*/{ std::bitset<4>("0000"), std::bitset<4>("1100"), std::bitset<4>("1011"), std::bitset<4>("0111"),
	std::bitset<4>("0101"), std::bitset<4>("1001"), std::bitset<4>("1110"), std::bitset<4>("0010"),
	std::bitset<4>("1010"), std::bitset<4>("0110"), std::bitset<4>("0001"), std::bitset<4>("1101"),
	std::bitset<4>("1111"), std::bitset<4>("0011"), std::bitset<4>("0100"), std::bitset<4>("1000") },
	/*14*/{ std::bitset<4>("0000"), std::bitset<4>("1101"), std::bitset<4>("1001"), std::bitset<4>("0100"),
	std::bitset<4>("0001"), std::bitset<4>("1100"), std::bitset<4>("1000"), std::bitset<4>("0101"),
	std::bitset<4>("0010"), std::bitset<4>("1111"), std::bitset<4>("1011"), std::bitset<4>("0110"),
	std::bitset<4>("0011"), std::bitset<4>("0111"), std::bitset<4>("1010"), std::bitset<4>("0111") },
	/*15*/{ std::bitset<4>("0000"), std::bitset<4>("1110"), std::bitset<4>("1111"), std::bitset<4>("0001"),
	std::bitset<4>("1101"), std::bitset<4>("0011"), std::bitset<4>("0010"), std::bitset<4>("1100"),
	std::bitset<4>("1001"), std::bitset<4>("0111"), std::bitset<4>("0110"), std::bitset<4>("1000"),
	std::bitset<4>("0100"), std::bitset<4>("1010"), std::bitset<4>("1011"), std::bitset<4>("0101") },
	/*16*/{ std::bitset<4>("0000"), std::bitset<4>("1111"), std::bitset<4>("1101"), std::bitset<4>("0010"),
	std::bitset<4>("1001"), std::bitset<4>("0110"), std::bitset<4>("0100"), std::bitset<4>("1011"),
	std::bitset<4>("0001"), std::bitset<4>("1110"), std::bitset<4>("1100"), std::bitset<4>("0011"),
	std::bitset<4>("1000"), std::bitset<4>("0111"), std::bitset<4>("0101"), std::bitset<4>("1010") }
};
//

//Function Prototypes
std::bitset<4> GFAdd(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFMult(std::bitset<4>, std::bitset<4>);
std::bitset<4> GFDiv(std::bitset<4>, std::bitset<4>);
std::bitset<4> findInverse(std::bitset<4>);
int locationFind(std::bitset<4>);
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
		std::string string1, string2; // temporary string variables to read user inputs into
		std::bitset<4> binaryResult; // variable for value returned to be saved in
	
	//query user for inputs
		//ask user for inputs on that operation
		std::cout << "Enter the first operand in a binary form : ";
		std::cin >> string1;
		std::bitset<4> binary1(string1);

		std::cout << "Enter the second operand in a binary form: ";
		std::cin >> string2;
		std::bitset<4> binary2(string2);

		//ask user for operation
		std::cout << "What operation would you like to perform on these operands(+, -, *, /): ";
		std::cin >> operation;


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
			if (binary2 == galiosField16[0])//if an input is zero(0) ie '0000' then division is impossible
			{
				binaryResult = NULL;
			}
			else
			{
				binaryResult = GFDiv(binary1, binary2);
			}
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
	//declare local variables
		int x, y; //the x,y position of the answer the table

	//perform calculations
		x = locationFind(input1);
		y = locationFind(input2);

	//return results
		return GFMultTable[x][y];

}


int locationFind(std::bitset<4> searchBits)
{
	int count = 0;
	while (galiosField16[count] != searchBits)
	{
		count++;
	}
	return count;
}
// http://web.eecs.utk.edu/~plank/plank/papers/CS-07-593/
// http://mathworld.wolfram.com/IrreduciblePolynomial.html
// http://www.cprogramming.com/tutorial/bitwise_operators.html
// https://en.wikipedia.org/wiki/Finite_field_arithmetic
// http://www.doc.ic.ac.uk/~mrh/330tutor/ch04s04.html


std::bitset<4> GFDiv(std::bitset<4> input1, std::bitset<4> input2) //division is the same as multiplying by the inverse
{
	//declare local variables
		std::bitset<4> result;
		std::bitset<4> inverse;
	
	//perform calculations
		inverse = findInverse(input2); //find the inverse

		result = GFMult(input1, inverse); //multiply the  first operand, and inverse of the second operand to get the answer
	
	//return results
		return result;
}

std::bitset<4> findInverse(std::bitset<4> input) //brute force inverse finder
{
	//declare local variables
		std::bitset<4> product("0000"); // create and initialize the return product
		std::bitset<4> comparison("0001"); //one in binary
		int count = 1; //skip 0

	//perform calculations
	while (product != comparison) //we know we found the inverse when the result is '0001' or one(1)
	{
		product = GFMult(input, galiosField16[count]); //try every possible number
		count++;
	}

	//return results
	return galiosField16[count-1]; // remove one(1) from count to get the right answer
}