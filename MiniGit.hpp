#pragma once
#include <iostream>
using namespace std;

//CSCI 2270 Spring 2021 Final Project - MiniGit 
//Adam Vitti, Gabriel Vitti, Tanner Leise


//STRUCTS: 
struct singlyNode{
    string fileName; // Name of local file
    string fileVersion; // Name of file in .minigit folder
    int versionNumber;
    singlyNode* next;

};

struct doublyNode
{
    int commitNumber;
    singlyNode* singlehead;
    doublyNode* previous;
    doublyNode* next;
};
/////////////////////////////////////////////////
//Functions:

class MiniGit
{
    public:
        MiniGit(); //Constructor
        ~MiniGit(); //Destructor
        singlyNode* newSingleNode(string name);
        doublyNode* initializeNewRepo(); //Initializes the first DLL and returns it
        bool fileExists(string fileName); //Checks local directory for existence of requested file 
        singlyNode* traverseSLL(singlyNode* n); //returns the tail of a SLL
        singlyNode* searchSLL(string fileName, singlyNode* start); //returns node of requested SLL
        doublyNode* searchDLL(int cNumber); //returns node of requested DLL
        singlyNode* getPrevSLL(string fileName, singlyNode* start); //returns previous node of requested SLL
        bool compareFiles(singlyNode* Node); //compares content of two files, returns true if content is identical
        void copyfileSame(singlyNode* node); //Copies old file contents into a new file with same version number 
        void copyfileIncrement(singlyNode* node); //Copies old file contents into a new file with incremented version number
        void copyFromRepo(singlyNode* start); //Copies old file contents from .minigit repo into the local directory
        void copySLL(doublyNode* oldDLL, doublyNode* newDLL); //Copies a full SLL when commiting to a new DLL 
        void prettyPrint(); //Pretty prints our DLL and SLL data structure


    private:
        singlyNode* singlehead;
        doublyNode* doublehead;
};









