#include <iostream>
#include <fstream>
#include <random>
#include <climits>
#include "individualAssignmentTwo.h"
#include "farmingdaleStatus.h"


//the purpose of this program is to create a file, and then write a random selection between
//1) The letter A followed by a random number or  2) a random letter from 6 possible choices, then to close the file
//this choice is written a number of times specified by the user
void randomStream(std::string filename, int length) {
    //code to generate letter
    std::random_device rd1;
    std::mt19937 gen1(rd1());
    std::uniform_int_distribution<> distrib1(0, 5);

    //code to generate number for "A" cases
    std::random_device rd2;
    std::mt19937 gen2(rd2());
    std::uniform_int_distribution<> distrib2(INT_MIN, INT_MAX);


    //open file
    std::ofstream MyFile(filename);

    //create array of letters
    std::string lettersArray[6] = { "A", "D", "P", "E", "C", "S" };

    //for loop to iterate length number of times
    for (int lineCount = 0; lineCount < length; ++lineCount) {
        int letterPicker = distrib1(gen1); //create index number to access location in array

        if (letterPicker == 0) { //if statement to catch "A" cases
            int numberPicker = distrib2(gen2); //create random number
            MyFile << lettersArray[letterPicker] << " " << numberPicker; //write "A" and number to file
        }
        else { //all other letters
            MyFile << lettersArray[letterPicker]; //write letter to file
        }

        if (lineCount != (length - 1)) {
            MyFile << "\n";
        }
    }

    MyFile.close(); //close the file
}

int testStream(std::string fileName) {
    //creating the queues
    farmingdale::queue<std::string> q1;
    farmingdale::queue<std::string> q2;
    farmingdale::queue<std::string> q3;
    farmingdale::queue<std::string> q4;

    //opening the file to be read
    std::ifstream inFile;
    inFile.open(fileName);

    //initializing the string variable to hold the line in the file
    std::string fileLine;

    //file line number to give the right error location
    int fileLineNumber = 1;


    //assign functions to a variable
    while (std::getline(inFile, fileLine)) {
        if (fileLine == "A") {
            std::string numberAfterPound1;
            std::string numberAfterPound2;
            std::string numberAfterPound3;
            std::string numberAfterPound4;

            //get a substring of the number after the pound sign in the document
            numberAfterPound1 = fileLine.substr(fileLine.find("#") + 1);
            numberAfterPound2 = fileLine.substr(fileLine.find("#") + 1);
            numberAfterPound3 = fileLine.substr(fileLine.find("#") + 1);
            numberAfterPound4 = fileLine.substr(fileLine.find("#") + 1);

            farmingdale::statusCode en1 = q1.enqueue(numberAfterPound1);
            farmingdale::statusCode en2 = q2.enqueue(numberAfterPound2);
            farmingdale::statusCode en3 = q3.enqueue(numberAfterPound3);
            farmingdale::statusCode en4 = q4.enqueue(numberAfterPound4);

            //Make sure all the enqueues return success or failure. As long as they all return the same thing.
            if (not ((en1 == en2) && (en2 == en3) && (en3 == en4))) {
                std::cerr << "Peek error on line " << fileLineNumber << std::endl;
            }

            //if any of the enqueues fail, give an error
            if (farmingdale::statusCode::FAILURE == en1) {
                std::cerr << "Enqueue error on line " << fileLineNumber << std::endl;
                exit(0);
            }
            else if (farmingdale::statusCode::FAILURE == en2) {
                std::cerr << "Enqueue error on line " << fileLineNumber << std::endl;
                exit(0);
            }
            else if (farmingdale::statusCode::FAILURE == en3) {
                std::cerr << "Enqueue error on line " << fileLineNumber << std::endl;
                exit(0);
            }
            else if (farmingdale::statusCode::FAILURE == en4) {
                std::cerr << "Enqueue error on line " << fileLineNumber << std::endl;
                exit(0);
            }

        }

        else if (fileLine == "P") {
            std::string returnedPeekValue1;
            std::string returnedPeekValue2;
            std::string returnedPeekValue3;
            std::string returnedPeekValue4;

            //make 4 return peek values
            farmingdale::statusCode pk1 = q1.peek(returnedPeekValue1);
            farmingdale::statusCode pk2 = q2.peek(returnedPeekValue2);
            farmingdale::statusCode pk3 = q3.peek(returnedPeekValue3);
            farmingdale::statusCode pk4 = q4.peek(returnedPeekValue4);

            //Make sure all the peeks return success or failure. As long as they all return the same thing.
            if (not ((pk1 == pk2) && (pk2 == pk3) && (pk3 == pk4))) {
                std::cerr << "Peek error on line " << fileLineNumber << std::endl;
            }
            //if success, make sure peeks returned the same thing
            else if (farmingdale::statusCode::SUCCESS == pk1) {
                if (not ((returnedPeekValue1 == returnedPeekValue2) && 
                    (returnedPeekValue2 == returnedPeekValue3) && 
                    (returnedPeekValue3 == returnedPeekValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            else if (farmingdale::statusCode::SUCCESS == pk2) {
                if (not ((returnedPeekValue1 == returnedPeekValue2) &&
                    (returnedPeekValue2 == returnedPeekValue3) &&
                    (returnedPeekValue3 == returnedPeekValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            else if (farmingdale::statusCode::SUCCESS == pk3) {
                if (not ((returnedPeekValue1 == returnedPeekValue2) &&
                    (returnedPeekValue2 == returnedPeekValue3) &&
                    (returnedPeekValue3 == returnedPeekValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            else if (farmingdale::statusCode::SUCCESS == pk4) {
                if (not ((returnedPeekValue1 == returnedPeekValue2) &&
                    (returnedPeekValue2 == returnedPeekValue3) &&
                    (returnedPeekValue3 == returnedPeekValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }


        }

        else if (fileLine == "D") {
            std::string returnedDequeueValue1;
            std::string returnedDequeueValue2;
            std::string returnedDequeueValue3;
            std::string returnedDequeueValue4;

            farmingdale::statusCode dq1 = q1.dequeue(returnedDequeueValue1);
            farmingdale::statusCode dq2 = q2.dequeue(returnedDequeueValue2);
            farmingdale::statusCode dq3 = q2.dequeue(returnedDequeueValue3);
            farmingdale::statusCode dq4 = q2.dequeue(returnedDequeueValue4);

            //if any dequeues fail, give an error
            if (not ((dq1 == dq2) && (dq2 == dq3) && (dq3 == dq4))) {
                std::cerr << "Peek error on line " << fileLineNumber << std::endl;
            }

            //if success, make sure dequeues returned the same thing
            else if (farmingdale::statusCode::SUCCESS == dq1) {
                if (not ((returnedDequeueValue1 == returnedDequeueValue2) &&
                    (returnedDequeueValue2 == returnedDequeueValue3) &&
                    (returnedDequeueValue4 == returnedDequeueValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            else if (farmingdale::statusCode::SUCCESS == dq2) {
                if (not ((returnedDequeueValue1 == returnedDequeueValue2) &&
                    (returnedDequeueValue2 == returnedDequeueValue3) &&
                    (returnedDequeueValue4 == returnedDequeueValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            else if (farmingdale::statusCode::SUCCESS == dq3) {
                if (not ((returnedDequeueValue1 == returnedDequeueValue2) &&
                    (returnedDequeueValue2 == returnedDequeueValue3) &&
                    (returnedDequeueValue4 == returnedDequeueValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            else if (farmingdale::statusCode::SUCCESS == dq4) {
                if (not ((returnedDequeueValue1 == returnedDequeueValue2) &&
                    (returnedDequeueValue2 == returnedDequeueValue3) &&
                    (returnedDequeueValue4 == returnedDequeueValue4))) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
                }
            }
            

        }

        else if (fileLine == "E") {
            //make sure all isEmpty agree
            //do two at a time
            if ((q1.isEmpty() != q2.isEmpty()) && (q2.isEmpty() != q3.isEmpty()) && (q3.isEmpty() != q4.isEmpty())) {
                std::cerr << "Error with isEmpty(): Not all queues agree " << fileLineNumber << std::endl;
            }

        }

        else {
            //if any other letters than A, D, P, or E; do nothing
            true;
        }

        //increment the file line counter
        ++fileLineNumber;
    }

    return farmingdale::SUCCESS;
}

int main() {
    std::string fileName;
    int numIterations, choice;

    do {
        std::cout << "Please make a selection:" << std::endl;
        std::cout << "1: Quit" << std::endl;
        std::cout << "2: Run RandomStream" << std::endl;
        std::cout << "3: Run TestStream" << std::endl;
        std::cout << "4: Run RandomStream AND TestStream" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            exit(0);
        case 2:
            std::cout << "Please input a filename: ";
            std::cin >> fileName;

            std::cout << "How many iterations: ";
            std::cin >> numIterations;

            randomStream(fileName, numIterations);
        case 3:
            std::cout << "Please input a filename: ";
            std::cin >> fileName;

            testStream(fileName);
        case 4:
            std::cout << "Please input a filename: ";
            std::cin >> fileName;

            std::cout << "How many iterations: ";
            std::cin >> numIterations;

            randomStream(fileName, numIterations);
            testStream(fileName);
        }
    }

    while (choice != 1);

}
