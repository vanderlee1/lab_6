/*
Rebecca van der Lee
C++ 2020 Fall
Due: 11/16/2020
Lab name: Lab 6 Binary to Decimal Conversion
Description: Write a C++ program that reads characters representing binary (base 2) numbers from a data file called
BinaryIn.dat and translates them to decimal (base 10) numbers. The binary and decimal numbers should be output in two
columns with appropriate headings. Here is a sample of the input and output: There is only one binary number per input line, but an arbitrary number of blanks can precede
the number.  The program must read the binary numbers one character at a time.
As each character is read, the program multiplies the total decimal value by 2 and adds either a 1 or 0, depending on
the input character.  The program should check for bad data; if it encounters anything except a 1 or 0, it
should output the message “Bad digit on input.”  The maximum number of spaces that could exist between any
two digits of a binary number in the input file will be one, in which case, the binary digit would be considered bad.
The output for this program should be to the screen and not an output file.  In order to read in one character at a
time, you will need to use the cin.get command.  When you have completed this lab, upload a copy of the .cpp file
called Lab6.cpp and BinaryIn.dat to GitHub.
*/

#include<iostream> //Standard library for c++
#include<istream>//This Library is for get and ignore
#include<iomanip>//This library is for setwidth
#include<fstream>//This library allows for the use of ifstream 
#include<cassert>//This library is for the asset function

using namespace std;

void openfile(ifstream& infile, ifstream& infile2);
//Precondition: The flow of control is valid
//Postcondition: The fucntion opens 2 ifstreams, the program closes if the stream is not valid
void fileread(ifstream& infile, char& input);
//Precondition: The flow of control is valid and the ifstream is valid
//Postcondition: "Input" stores a new value and the flow of control continues 

void binaryinput(char, ifstream& infile, unsigned int& decval, int& binarysize, bool& valid);
//Preconditions: The flow of control and ifstream is valid
//Postcondition: A base value is calculated for each of the variables from "BinaryIn.dat". Each charcater is read through the file by making use of a while loop for the first ifstream. 
//               Then it assigns a value to "decval" depending on the number of 0s adn 1s in BinaryIn.dat. 
//               A valvue is assigned to binarysize according to the number of iterations of a while loop within the function
//               Valid can be true of false. This depends on the character that is inputted. The makrer in the iirst ifstream will be at a newline character. The flow of control continues


void binaryout(char, int, bool, ifstream& infile2);
//Precondition: The flow of control passed on from "binaryIn" and the ifstream is valid
//Postcondition: The variablde decwidth is declared. By using "binarysize" from "binaryinput", is the value for decwidth calculated. 
//               spaces are outputted on the screen. Then, the function used the second ifstream to output the binary number. The the binary numbers
//                is followed by more spaces. When "valid" from the previous funtion is false, the funtion outputs an error statement instead of outputting the binary number. 
//               The marker in the second ifstream is ate a new line character. The flow of control continues. 
void decoutput(unsigned int);
//Precondition: The flow of control passed by from "binaryout", the ifstream is valid, and "valid" is true.
//Postcondition: A new variable for width is declared. This value is calculated by using "decval". Spaces are ouputted to the screen. Then it outputs the decimal numer to the screen 
//               and the flow of control continues. 


int main()
{
	ifstream infile; //Declaration of two ifstream. This allows for acces of data from the file      
	ifstream infile2;
	char input;          //The information from the file "BinaryIn.dat"
	unsigned int decval; //"decval" will store the value of the calculated decimal number
	int binarysize;      // This stores the amount of spaces of the binary input
	bool valid;          // This the variable that let the program checks if the input is valid or not
	openfile(infile, infile2);//The files are opened

	cout << "          Binary Number              Decimal Equivalent" << endl;//The header is outputted

	fileread(infile, input);// function filerread is called

	while (infile) //while loop runs until end of file is reached
	{
		binaryinput(input, infile, decval, binarysize, valid);//funtion call
		binaryout(input, binarysize, valid, infile2);//funciton call

		if (valid)
			decoutput(decval); //if the input is valid, then "decoutput is calle"
		fileread(infile, input);  // Reads first charachter of each newline
	}

	return 0; //The program is ended

}

//"openfile" opens the input into two ifstreams. These ifstreams differ from each other.
//This function uses reference parameters. 
void openfile(ifstream& infile, ifstream& infile2)
{
	string BinaryInput = "C:/Users/VANDERLEE1/source/repos/lab_6/lab_6/BinaryIn.dat";
	infile.open(BinaryInput);  // First ifstream is opened.
	if (!infile)
	{
		cout << "Cannot read the file: ";
		assert(infile); // this checks for an error in the file name.
	}
	infile2.open(BinaryInput); // Second ifstream is opened.

}

//This reads in the first character of each new line, but it does not read spaces or zeros.
// This function uses value parameters
void fileread(ifstream& infile, char& input)
{
	infile >> input;   // The first character is read
	while (infile && input != '1' && input == ' ' || input == '0')
	{
		infile.get(input);    //Input is read until it reaches a 1 or an invalid character 
	}
}



//binaryin will read all the charcater on a line and determine wheter the data from the file was valid or not
//it will calculate the decimal equivalent of the binary number in the file. Then the function will calculate
//the total amount of characters of the binary number. The char "input" is a value parameter and the others are reference parameters.

void binaryinput(char input, ifstream& infile, unsigned int& decval, int& binarysize, bool& valid)
{
	decval = 0;    //Each of the variables are set to a base value, so that each iteration of the   
	binarysize = 0; //end of file loop in the main funtion will be consisten
	valid = true;

	while (infile && input != '\n') //The while loop lets the program just read one line at the time
									//The loop will exit if it hits when it reads the end of the file
	{
		switch (input)
		{
		case '0': decval = (decval * 2) + 0; // A switch statement is used to determine the calculation for the decimal number. 
											 // Thereby, checks the validity of input. A bad digit will change "valid"  in false.

			break;
		case '1': decval = (decval * 2) + 1;
			break;
		default: valid = false;
		}
		binarysize++; //For each iteration of the loop the size of the number increases by 1 character
		infile.get(input);//The next character on the line is readed
	}

}

//"binaryout" takes the date from "binaryinput" and determines what the output should be. This only happens if the binary input was valid.
//The function calculates how amny spaces will be outptted before the binary number, in order to output in the center. 
//Then the characters from the file are read through the second ifstream and the binary number is outputted on the screen.
//This only happens if the input was valid. Invalid datat will output an error message. The function uses mostly value parameters. 
// Only the ifstream must be reference parameter.
void binaryout(char input, int binarysize, bool valid, ifstream& infile2)
{
	int binarywidth; // Declaration of the variable that stores the width of the binary number

	if (binarysize % 2 == 0)              //Based on the size of binary number, is the width calculated 

		binarywidth = ((binarysize) / -2) + 18; //There is a calculation for both even and odd sizes
	else
		binarywidth = ((binarysize) / -2) + 17;
	if (valid)
		cout << setw(binarywidth); //outputting the width
	infile2.ignore(200, '1'); //This will let the program ignore anything that is not the first digit of binary code 
	input = '1';

	while (infile2 && input != '\n') //The while loop will output one binary number each time. 
	{                                 //A new line character seperates each binary number. The loop will stop when it reaches the end of 
									  //the file
		if (valid)
			cout << input;  // Each character is read and outputted. If the character is invalid this just happens one time
		infile2.get(input);
	}

	if (valid)
	{
		cout << setw(binarywidth);  //This will output the space after the binary number
		cout << "\t";
	}
	else
		cout << "      Bad digit on input" << endl; //The meassage that is outputted when the data from the file is invalid

}
//First, "decoutput", calculates the number of spaces that should be outputted for each decimal number, then it outputs bothe the spaces and the decimal number 
//to the sreen. The function only birngs in the data for the decimal number. This will result in just one value parameter.
void decoutput(unsigned int decval)
{
	int decsize; // this is the amount of characters of the decimal number
	int decwidth;//amount of characters to be outputted before the deciaml number
	unsigned int decval2; //copy of decval

	decsize = 0; //base value for "decval"

	decval2 = decval; //coopy of "decval"
	while (decval2 >= 1)
	{
		decval2 /= 10; //decsize is being determined
		decsize++;
	}

	if (decsize % 2 == 0)            //The width is calculated on the size of the decimal numbers
		decwidth = ((decsize) / -2) + 6; // Bothe even sizes and odd sizes are calculated
	else
		decwidth = ((decsize) / -2) + 5;
	for (decwidth; decwidth > 0; decwidth--)
	{
		cout << " ";//  will make sure that there enough spaces are outputted
	}

	cout << decval << endl;//will output decimal number on the screen

}