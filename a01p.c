// do not change this code except in the following ways:
//   * write code for the following functions:
//      * bigOrSmallEndian()
//      * getNextHexInt()
//      * printNumberData()
//   * change studentName by changing "I. Forgot" to your actual name

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

static char *studentName = "Nina Hoang";

// report whether machine is big or small endian
void bigOrSmallEndian()
{
	unsigned int	i = 1;
	char* 			p = (char *)&i;

	printf("byte order: ");

	if (*p)		// dereference p to determine the order of the 1 unsigned int (4 bytes)
	{
		printf("little-endian\n");	// if starts with the biggest number 
	}
	else
	{
		printf("big-endian\n");		// if starts with the smallest number
	}
	printf("\n");
}

// get next int (entered in hex) using scanf()
// returns true (success) or false (failure)
// if call succeeded, return int value via iPtr
bool getNextHexInt(unsigned int *iPtr)
{
	// replace this code with the call to scanf()
	//*iPtr = 0;
	unsigned int	i;
	unsigned int	nParsed;


	nParsed = scanf("%X", &i);

	if (nParsed == 1)	// makes sure input is a valid hex number
	{
		*iPtr = i;
		return true;
	}
	return false;
}

// print requested data for the given number
void printNumberData(int i)
{
	int 	bias = 127;							// bias for single precision
	int		signBit = !!(i & 0x80000000);		// double NOT transforms the output of the function into 1 or 0
	int 	expBits = (i & 0x7f800000) >> 23; 	// masked and took out the 8 bits for exponential bits
	int 	fractBits = (i & 0x007FFFFF);		// masked to take out the last 23 bits of 32 bits integer

	printf("signBit %1d, expBits %d, fractBits 0x%08X\n", 
	signBit, expBits, fractBits);

	if (expBits == 0)	// if all 0's in expBits (binary)
	{
		if (fractBits != 0)
		{
			printf("denormalized: exp = %d\n", (1 - bias));
		}
		else
		{
			if (signBit == 0)
			{
				printf("+zero\n");
			}
			else
			{
				printf("-zero\n");
			}
		}
	}
	else if (expBits == 255)	// if all 1's in expBits (binary)
	{
		if (fractBits == 0)
		{
			if (signBit == 0)
			{
				printf("+infinity\n");
			}
			else
			{
				printf("-infinity\n");
			}
		}
		else
		{
			if ((fractBits >>= 22) == 1)	// if the first bit of fractBits is 1
			{
				printf("QNaN\n");
			}
			else
			{
				printf("SNaN\n");
			}
		}
	}
	else	// if mixed of 0 and 1 in expBits (binary)
	{
		printf("normalized:   exp = %d\n", (expBits - bias));
	}
	printf("\n");
}

// do not change this function in any way
int main(int argc, char **argv)
{
	unsigned int	i;					// number currently being analyzed
	bool			validInput;			// was user input valid?

	printf("CS201 - A01p - %s\n\n", studentName);
	bigOrSmallEndian();
	for (;;) {
		if (argc == 1)						// allow grading script to control ...
			printf("> ");					// ... whether prompt character is printed
		validInput = getNextHexInt(&i);
		printf("0x%08X\n", i);
		if (! validInput) {					// encountered bad input
			printf("bad input\n");
			while (getchar() != '\n') ;		// flush bad line from input buffer
			continue;
			}
		printNumberData(i);
		if (i == 0) {
			printf("bye...\n");
			break;
			}
		}
	printf("\n");
	return 0;
}
