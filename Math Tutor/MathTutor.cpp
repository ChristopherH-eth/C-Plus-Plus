// Math Tutor Program
// Version 1.0
//
// Christopher Hardy
// PRG/410
// February 29th, 2016
// Gholam Ali Shaykhian
//
// Description:
// The Math Tutor Program allows the user to go through as many addition math problems they would like with two different
// numbers ranging from one to 300.  The program will pause after the problem is displayed, and after the user presses
// any key the solution is displayed as well.  The program will continue to go through problems for as long as the program
// is running.

#include "stdafx.h"
#include <iostream>
using namespace std;


int main()
{
	double number1, number2, sum;
	bool RUNNING = true;

	// welcome message
	cout << "Welcome to the Math Tutor Program!\n" << endl;
	cout << "This program will provide the user with simple addition problems, provide time \nto solve them, and display the ";
	cout << "correct answer when the user is ready by \npressing any key.\n\n" << endl;

	// loop to allow for more than one problem while running the program
	while (RUNNING)
	{
		number1 = 1 + rand() % 300;
		number2 = 1 + rand() % 300;
		sum = number1 + number2;

		cout << number1 << " + " << number2 << " = " << endl;
		system("pause");
		cout << number1 << " + " << number2 << " = " << sum << endl;
		system("pause");
		cout << "\n";
	}

    return 0;
}

