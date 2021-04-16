#include <iostream>
#include <fstream>
#include <stdexcept>
#include <string>

#include "Types.h"
#include "Node.h"
#include "NodeList.h"
#include "PathSolver.h"

// Helper test functions
void testNode();
void testNodeList();

// Read a environment from standard input.
void readEnvStdin(Env env);
//output the environment
void testPe(Env env);
// Print out a Environment to standard output with path.
// To be implemented for Milestone 3
void printEnvStdout(Env env, NodeList *solution);

int main(int argc, char **argv)
{
    //The entire code has six tests (including sample1 in stratcode), including all possible situations,
    // and also printout the original env and all path points. In the forwardsearch part, find the next
    // point by finding all the points whose Manhattan distance is 1 from the current point, and then add
    // it to the openlist. And add the points that have been passed to the close list, then find the point
    // with the smallest estimated distance in the plist as the next point, and finally clist is all Point passed.
    // The backtracking part first traverses the clist, finds the path back according to the distance traveled,
    // and finally returns the path (from the end to the start). 
    //The entire code fully implements Milestone1, 2, 3, but Milestone4 is not implemented because it is too difficult.
    std::cout << "TESTING - COMMENT THE OUT TESTING BEFORE YOU SUBMIT!!!" << std::endl;
    testNode();
    testNodeList();
    std::cout << "DONE TESTING" << std::endl
              << std::endl;

    // Load Environment
    Env env;
    readEnvStdin(env);
    //Output map to test whether the import is successful
    testPe(env);
    PathSolver *pathSolver = new PathSolver();
    pathSolver->forwardSearch(env);
    // Get the path
    NodeList* solution = pathSolver->getPath(env);
    printEnvStdout(env, solution);
    delete pathSolver;
    delete solution;
}

void readEnvStdin(Env env)
{
    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            std::cin >> env[j][i];
        }
    }
}
// printout the env to test
void testPe(Env env)
{
    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            std::cout << env[j][i];
        }
        std::cout << "\n";
    }
}
//set the move down, up, right, left char in types.h ,By calculating the difference between the two points(row and col)
// to get the Up down left and right symbols
void printEnvStdout(Env env, NodeList *solution)
{
    for(int i = 0; i < solution->getLength(); i++)
    {
        if(solution->getNode(i)->getRow() - solution->getNode(i + 1)->getRow() == 1 && 
           solution->getNode(i)->getCol() - solution->getNode(i + 1)->getCol() == 0)
           {
               env[solution->getNode(i + 1)->getCol()][solution->getNode(i + 1)->getRow()] = char(MOVE_DOWN);
           }
        else if(solution->getNode(i)->getRow() - solution->getNode(i + 1)->getRow() == 0 &&
                solution->getNode(i)->getCol() - solution->getNode(i + 1)->getCol() == 1)
                {
                    env[solution->getNode(i + 1)->getCol()][solution->getNode(i + 1)->getRow()] = char(MOVE_RIGHT);
                }
        else if(solution->getNode(i)->getRow() - solution->getNode(i + 1)->getRow() == 0 &&
                solution->getNode(i)->getCol() - solution->getNode(i + 1)->getCol() == -1)
                {
                    env[solution->getNode(i + 1)->getCol()][solution->getNode(i + 1)->getRow()] = char(MOVE_LEFT);
                }
        else if(solution->getNode(i)->getRow() - solution->getNode(i + 1)->getRow() == -1 &&
                solution->getNode(i)->getCol() - solution->getNode(i + 1)->getCol() == 0)
                {
                    env[solution->getNode(i + 1)->getCol()][solution->getNode(i + 1)->getRow()] = char(MOVE_UP);
                }
    }
    //Set the start symbol to s
    env[solution->getNode(solution->getLength()-1)->getCol()][solution->getNode(solution->getLength()-1)->getRow()] = char(SYMBOL_START);
    for (int i = 0; i < ENV_DIM; i++)
    {
        for (int j = 0; j < ENV_DIM; j++)
        {
            std::cout << env[j][i];
        }
        std::cout << "\n";
    }
}

void testNode()
{
    std::cout << "TESTING Node" << std::endl;

    // Make a Node and print out the contents
    Node *node = new Node(1, 1, 2);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;

    // Change Node and print again
    node = new Node(4, 2, 3);
    std::cout << node->getRow() << ",";
    std::cout << node->getCol() << ",";
    std::cout << node->getDistanceTraveled() << std::endl;
    delete node;
}

void testNodeList()
{
    std::cout << "TESTING NodeList" << std::endl;

    // Make a simple NodeList, should be empty size
    NodeList *nodeList = new NodeList();
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add a Node to the NodeList, print size
    Node *b1 = new Node(1, 1, 1);
    nodeList->addElement(b1);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Add second Nodetest
    Node *b2 = new Node(0, 0, 1);
    nodeList->addElement(b2);
    std::cout << "NodeList size: " << nodeList->getLength() << std::endl;

    // Test Get-ith - should be 0,0,1
    Node *getB = nodeList->getNode(1);
    std::cout << getB->getRow() << ",";
    std::cout << getB->getCol() << ",";
    std::cout << getB->getDistanceTraveled() << std::endl;

    // Print out the NodeList
    std::cout << "PRINTING OUT A NODELIST IS AN EXERCISE FOR YOU TO DO" << std::endl;
}
