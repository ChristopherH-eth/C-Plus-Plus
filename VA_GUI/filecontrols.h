// Basic file controls
#include <iostream>
#include <fstream>

using namespace std;

// Globals
wchar_t fJobTitle[100], fLocation[100];

// MakeFile function creates a temporary file to store user input data for use in Python script
void MakeFile() {
	wofstream tempfile;
	tempfile.open ("jobtemp.txt");
	tempfile << fJobTitle << endl;
	tempfile << fLocation << endl;
	tempfile.close();
}