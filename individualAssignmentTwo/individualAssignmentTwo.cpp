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
    farmingdale::queue<std::string> q1;
    farmingdale::queue<std::string> q2;
    farmingdale::queue<std::string> q3;
    farmingdale::queue<std::string> q4;

    std::ifstream inFile;
    inFile.open(fileName);

    std::string fileLine;

    std::string returnedPeekValue;
    std::string returnedDequeueValue;

    int fileLineNumber = 1;

    while (std::getline(inFile, fileLine)) {
        if (fileLine == "A") {
            std::string numberAfterPound; 

            //get a substring of the number after the pound sign in the document
            numberAfterPound = fileLine.substr(fileLine.find("#") + 1); 

            //if any of the enqueues fail, give an error
            if (farmingdale::statusCode::FAILURE == q1.enqueue(numberAfterPound) ||
                farmingdale::statusCode::FAILURE == q2.enqueue(numberAfterPound) || 
                farmingdale::statusCode::FAILURE == q3.enqueue(numberAfterPound) || 
                farmingdale::statusCode::FAILURE == q4.enqueue(numberAfterPound)) {
                    std::cerr << "Enqueue error on line " << fileLineNumber << std::endl;
            }
            //otherwise, enqueue the number to each queue
            else {
                q1.enqueue(numberAfterPound);
                q2.enqueue(numberAfterPound);
                q3.enqueue(numberAfterPound);
                q4.enqueue(numberAfterPound);
            }
            
        }

        else if (fileLine == "P") {
            //if any of the peeks fail, give an error
            if (farmingdale::statusCode::FAILURE == q1.peek(returnedPeekValue) ||
                farmingdale::statusCode::FAILURE == q2.peek(returnedPeekValue) ||
                farmingdale::statusCode::FAILURE == q3.peek(returnedPeekValue) ||
                farmingdale::statusCode::FAILURE == q4.peek(returnedPeekValue)) {
                    std::cerr << "Peek error on line " << fileLineNumber << std::endl;
            }
            //here, if all the peeks are the same value, we only need to return one
            else if (q1.peek(returnedPeekValue) == 
                     q2.peek(returnedPeekValue) == 
                     q3.peek(returnedPeekValue) == 
                     q4.peek(returnedPeekValue)) {
                        q1.peek(returnedPeekValue);
            }
            

        }

        else if (fileLine == "D") {
            //if any dequeues fail, give an error
            if (farmingdale::statusCode::FAILURE == q1.dequeue(returnedDequeueValue) ||
                farmingdale::statusCode::FAILURE == q2.dequeue(returnedDequeueValue) ||
                farmingdale::statusCode::FAILURE == q3.dequeue(returnedDequeueValue) ||
                farmingdale::statusCode::FAILURE == q4.dequeue(returnedDequeueValue)) {
                std::cerr << "Dequeue error on line " << fileLineNumber << std::endl;
            }
            else {
                //dequeue all the queues
                q1.dequeue(returnedDequeueValue);
                q2.dequeue(returnedDequeueValue);
                q3.dequeue(returnedDequeueValue);
                q4.dequeue(returnedDequeueValue);

                //check to see if all the dequeued values were the same
                if (q1.dequeue(returnedDequeueValue) !=
                    q2.dequeue(returnedDequeueValue) !=
                    q3.dequeue(returnedDequeueValue) !=
                    q4.dequeue(returnedDequeueValue)) {
                    std::cerr << "Error: not all dequeued values the same" << std::endl;
                }
            }
            
        }

        else if (fileLine == "E") {
            //make sure all isEmpty agree
            if (q1.isEmpty() != q2.isEmpty() != q3.isEmpty() != q4.isEmpty()) {
                std::cerr << "Error with isEmpty(): Not all queues agree " << fileLineNumber << std::endl;
            }

        }

        else {
            true;
        }

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
