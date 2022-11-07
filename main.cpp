/* Benyamain Yacoob
02-07-2022
Intro to Programming II
Dr. Mina Maleki
"Project1" Exercise */

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Global variable for array size declaration of row and column
const int ARRAY_SIZE = 20;

// printingCommands: Prints the list of commands from input file
// INPUT: Reads data from (arrayPtr) to be printed with (lengthCounter) parameter
// Function is called to read and print the commands
// OUTPUT: Prints the list of commands
void printingCommands(string arrayPtr[], int lengthCounter)
{
    // Nested for loops to print list of commands
    for (int i = 0; i < lengthCounter; i++)
    {
        if (arrayPtr[i] == "5" || arrayPtr[i] == "7")
        {
            cout << arrayPtr[i] << " " << arrayPtr[i + 1];

            ++i;
        }
        else
            cout << arrayPtr[i];

        cout << endl;
    }
}

// processInputCommands: Process input commands to find the graphic
// INPUT: Reading data from the array between first column (currentCommand) and second column (nextCommand)
// Function is called to find graphic based on list of commands given
// OUTPUT: N/A
void processInputCommands(string arrayPtr[], int sketchFigure[][ARRAY_SIZE], int lengthCounter)
{
    // Static declaration of variables so their values do not change after program exits the function
    static int currentPenPosition = 0, currentDirection = 0, currentRow = 0, currentColumn = 0;
    string currentCommand, nextCommand;

    for (int i = 0; i < lengthCounter; i++)
    {
        currentCommand = arrayPtr[i];

        if (currentCommand == "5" || currentCommand == "7")
        {
            nextCommand = arrayPtr[i + 1];

            arrayPtr[i + 1] = "0";  // A number needed for the stoi conversion; that is, the function breaks for case 0
        }
        
        switch (stoi(currentCommand))   // Using "stoi" converts string to int
        {
        case 0:
            break;
        case 1:   currentPenPosition = 0;   // Moving freely when pen is up; array is filled with " "
            break;
        case 2:   currentPenPosition = 1;   // Starts to trace movement of turtle graphic; pen is down and array is filled with "*"
            break;
        case 3:   currentDirection++;   // Increases in rows
            break;
        case 4:   currentDirection--;   // Decreases in rows
            break;
        case 5: 
            
            if (currentDirection == 0)  // Move forward; increase in column 
            {
                for (int i = 0; i < stoi(nextCommand); i++)
                    sketchFigure[currentRow][++currentColumn] = currentPenPosition;
            }
            else if (currentDirection == 1)   // Turn right; increase in row
            {
                for (int i = 0; i < stoi(nextCommand); i++)
                    sketchFigure[++currentRow][currentColumn] = currentPenPosition;
            }
            else if (currentDirection == 2)   // Move backward; decrease in column
            {
                for (int i = 0; i < stoi(nextCommand); i++)
                    sketchFigure[currentRow][--currentColumn] = currentPenPosition;
            }
            else if (currentDirection == 3)   // Turn left; decrease in row
            {
                for (int i = 0; i < stoi(nextCommand); i++)
                    sketchFigure[--currentRow][currentColumn] = currentPenPosition; // Position of pen always known
            }

              break;
        case 6:   cout << endl;

            for (int a = 0; a < ARRAY_SIZE + 2; a++)    // Printing first row of the border hyphens
                cout << "-";

            cout << endl;

            // Printing the turtle graphic
            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                cout << "|";

                for (int k = 0; k < ARRAY_SIZE; k++)
                {

                    if (sketchFigure[i][k] == 0)
                        cout << " ";
                    else
                        cout << "*";
                }

                cout << "|";
                cout << endl;
            }

            for (int a = 0; a < ARRAY_SIZE + 2; a++)
                cout << "-";

            cout << endl << endl;

            break;
        case 7: {

            fstream outputFile(nextCommand, ios::out);  // File handler to save array into output file

            for (int a = 0; a < ARRAY_SIZE + 2; a++)
                outputFile << "-";

            outputFile << endl;

            for (int i = 0; i < ARRAY_SIZE; i++)
            {
                outputFile << "|";

                for (int k = 0; k < ARRAY_SIZE; k++)
                {

                    if (sketchFigure[i][k] == 0)
                        outputFile << " ";
                    else
                        outputFile << "*";
                }

                outputFile << "|";
                outputFile << endl;
            }

            for (int a = 0; a < ARRAY_SIZE + 2; a++)
                outputFile << "-";

            outputFile.close(); // Closing the file
        }

              break;
        case 9: cout << "That is the end of the program. Thanks for being here!\n";
            break;
        default:
            break;
        }
    }
}

// validateInputFile: Asks program user to confirm the name of the entered input file
// INPUT: A character ( inputConfirmation ) that is 'Y' or 'N' & the name of the input file
// Function called when input file name needs to be confirmed from the user
// OUTPUT: N/A
string validateInputFile()
{
    // Declaration of variables
    char inputConfirmation;
    string inputFileName;
    
    // User prompt to enter name of input file to be opened
    cout << "Enter the name of the input file: ";

    getline(cin, inputFileName);    // String

    cout << "Did you mean to type " << inputFileName << " (Y/N)?: ";

    cin >> inputConfirmation;
    
    inputConfirmation = toupper(inputConfirmation); // Uppercases the letter

    while (true)
    {
        if (inputConfirmation == 'Y')
            break;
        else if (inputConfirmation == 'N')
        {
            cout << "Please enter the name of the input file again: ";
            cin >> inputFileName;

            cout << "Did you mean to type " << inputFileName << " (Y/N)?: ";
            cin >> inputConfirmation;

            inputConfirmation = toupper(inputConfirmation);
        }
        else if (inputConfirmation != 'Y' && inputConfirmation != 'N')  // Make sure user types in 'Y' or 'N'
        {
            cout << "ERROR: Invalid input.\n";
            cout << "Please type (Y/N): ";
            cin >> inputConfirmation;

            inputConfirmation = toupper(inputConfirmation);
        }
    }

    cout << endl;

    return inputFileName;
}

int main()
{
    // Declaration of variables
    fstream inputFile, secondInputFile;
    int sketchFigure[ARRAY_SIZE][ARRAY_SIZE] = { 0 }, lengthCounter = 0, i = 0;   // sketchFigure: 20-20 array set to 0's
    string readFileArr[ARRAY_SIZE][ARRAY_SIZE], inputFileName, temp,  *arrayPtr = nullptr; // Declaring a pointer to be used

    inputFileName = validateInputFile();    // Storing the file name from outside function

    inputFile.open(inputFileName, ios::in);   // Opens the file if it does exist

    if (!inputFile)
        cout << "Unable to open the file!\n";
    else
    {
        // Finds the length of the inputFile
        while (!inputFile.eof())
        {
            inputFile >> temp;

            lengthCounter++;
        }

        arrayPtr = new string[lengthCounter];   // Dynamically allocate memory to specified number of lines
        
        secondInputFile.open(inputFileName, ios::in);
        
        // Stores data into the arrayPtr
        while (!secondInputFile.eof())
        {
            secondInputFile >> arrayPtr[i];

            i++;
        }

        printingCommands(arrayPtr, lengthCounter);  // Calling the function to show list of commands
        
        processInputCommands(arrayPtr, sketchFigure, lengthCounter);   // Calling another function to print graphic based on list of commands
    }

    // Closing the file
    inputFile.close();
    secondInputFile.close();

    return 0;
}
