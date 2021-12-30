#include<iostream> 
#include "MiniGit.hpp"
#include <filesystem>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;

MiniGit::MiniGit(){
    fs::remove_all(".minigit"); //deletes previous directories
    fs::create_directory(".minigit"); //creates new subdirectory
}
//------------------------------------------------------------------------------------
MiniGit::~MiniGit(){ //Destructor
    doublyNode* DLL = doublehead;
    doublyNode* DLLprev = NULL;
    singlyNode* singlecurr;
    singlyNode* singleprev = NULL;
   
   
    while(DLL != NULL){   //This should delete each doubly node and single node
        singlecurr = DLL->singlehead;           //sets our temp current node to the head of our current DLL Node

        if(singlecurr != NULL){                 //This should traverse and delete every node in the SLL
            while(singlecurr != NULL){
                singleprev = singlecurr;
                singlecurr = singlecurr->next;
                delete singleprev;
            }
        }
        DLLprev = DLL;
        DLL = DLL->next;
        delete DLLprev;

    }
}
//------------------------------------------------------------------------------------
doublyNode* MiniGit::initializeNewRepo()
{
    doublyNode* DLL = new doublyNode;
    DLL->singlehead = singlehead;
    doublehead = DLL;
    DLL->commitNumber = 0;
    DLL->next = NULL;
    DLL->previous = NULL;
    return DLL;
}
//------------------------------------------------------------------------------------
singlyNode* MiniGit::newSingleNode(string name){
     singlyNode* newSinglyNode = new singlyNode;
     newSinglyNode->fileName = name;
     newSinglyNode->versionNumber = 0; //version number will always start at 0
     newSinglyNode->fileVersion = to_string(newSinglyNode->versionNumber) + "__" + name; 
     newSinglyNode->next = NULL;
     return newSinglyNode;
}
//------------------------------------------------------------------------------------
bool MiniGit::fileExists(string fileName)
{
    ifstream fin;
    fin.open(fileName);
    if(fin.is_open()){ //file was found and exists
        fin.close();
        return true;
    }else{
        return false; //file was not found and does not exist
    }
}
//------------------------------------------------------------------------------------
singlyNode* MiniGit::traverseSLL(singlyNode* start)
{
    singlyNode* n = start;
    while(n->next != NULL){
        n = n->next;
    }
    //function will return when n = tail of SLL 
    return n;
}
//------------------------------------------------------------------------------------
singlyNode* MiniGit::searchSLL(string fileName, singlyNode* start)
{
    singlyNode* curr = start;
    while(curr != NULL){
        if(curr->fileName == fileName){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
//------------------------------------------------------------------------------------
doublyNode* MiniGit::searchDLL(int cNumber){
    doublyNode* curr = doublehead;
    while(curr != NULL){
        if(curr->commitNumber == cNumber){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
//------------------------------------------------------------------------------------
singlyNode* MiniGit::getPrevSLL(string fileName, singlyNode* start)
{
    singlyNode* curr = start;
    while(curr != NULL){
        if(curr->next->fileName == fileName){
            return curr;
        }
        curr = curr->next;
    }
    return NULL;
}
//------------------------------------------------------------------------------------
bool MiniGit::compareFiles(singlyNode* Node){
    string newFileContents = "";
    string oldFileContents = "";
    ifstream nFile(Node->fileName);
    
    char ch;
    while (nFile >> noskipws >> ch){// assigns string the contents of the new file
        newFileContents += ch;
    }
    nFile.close();

    ifstream oFile(".minigit/" + Node->fileVersion);

    while (oFile >> noskipws >> ch){// assigns string the contents of the old file
        oldFileContents += ch;
    }
    oFile.close();

    if (newFileContents.compare(oldFileContents) == 0){
        return true;
    }
    return false;
}
//------------------------------------------------------------------------------------
void MiniGit::copyfileSame(singlyNode* node){    //Adam needs to make sure the copied file gets put into the directory with the fs stuff
        string line;
        string infile = node->fileName;
        ifstream fin(infile); //Opens local in progress file
        int vernum = node->versionNumber;


        string nf = to_string(vernum) + "__"  + infile; //creates name for new file
        ofstream fout; //Creates a new file for .minigit directory ?? check this works
        fout.open(".minigit/"+nf);

        //copies contents from original file to new file
        if(fin && fout){ 
            while(getline(fin,line)){
                fout << line;
            }

            fin.close();
            fout.close();
            cout << "File was copied successfully!" << endl; //used for testing
            return;  
            }
        
        else{
            cout << "Error copying file." << endl; //used for testing
            return;
        }
    }
//------------------------------------------------------------------------------------
void MiniGit::copyfileIncrement(singlyNode* node){    
        string line;
        string infile = node->fileName;
        ifstream fin(infile); //Opens local in progress file
        int vernum = node->versionNumber;


        string nf = to_string(vernum+1) + "__"  + infile; //creates name for new file
        ofstream fout; //Creates a new file for .minigit directory ?? check this works
        fout.open(".minigit/"+nf);

        node->versionNumber++; //incremenets SLL version too
        node->fileVersion = nf; //increments SLL fileVersion name

        //copies contents from original file to new file
        if(fin && fout){ 
            while(getline(fin,line)){
                fout << line;
            }

            fin.close();
            fout.close();
            cout << "File was copied successfully!" << endl; //used for testing
            return;  
            }
        
        else{
            cout << "Error copying file." << endl; //used for testing
            return;
        }
    }
//------------------------------------------------------------------------------------
void MiniGit::copyFromRepo(singlyNode* node){
    string line;
    ifstream fin(".minigit/" + node->fileVersion); //Opens local in progress file

        ofstream fout; //Creates a new file for .minigit directory ?? check this works
        fout.open(node->fileName);

        //copies contents from original file to new file
        if(fin && fout){ 
            while(getline(fin,line)){
                fout << line;
            }

            fin.close();
            fout.close();
            cout << "File was copied successfully!" << endl; //used for testing
            return;  
            }
        
        else{
            cout << "Error copying file." << endl; //used for testing
            return;
        }


}
//------------------------------------------------------------------------------------
void MiniGit::copySLL(doublyNode* oldDLL, doublyNode* newDLL)
{
    singlyNode* SLLcopy = oldDLL->singlehead;
    singlyNode* prev = NULL;

    bool needHeadSet = true;
    while(SLLcopy != NULL){
        singlyNode* newSLL = new singlyNode;
        newSLL->fileName = SLLcopy->fileName;
        newSLL->fileVersion = SLLcopy->fileVersion;
        newSLL->versionNumber = SLLcopy->versionNumber;
        newSLL->next = NULL;
        if(needHeadSet){ //sets first head SLL
            newDLL->singlehead = newSLL;
            prev = newDLL->singlehead;
            needHeadSet = false;
        }else{
            prev->next = newSLL;
            prev = newSLL;
        }
        SLLcopy = SLLcopy->next;

    }   
}

//------------------------------------------------------------------------------------
void MiniGit::prettyPrint(){
    doublyNode* DLL = doublehead;
    singlyNode* singlecurr;
   
   
    while(DLL != NULL){
        cout << "DLL commit #" << DLL->commitNumber << "-> ";

        singlecurr = DLL->singlehead;           //sets our temp current node to the head of our current DLL Node

        if(singlecurr != NULL){                 //This should traverse and delete every node in the SLL
            while(singlecurr != NULL){
                cout << singlecurr->fileName << "->";
                singlecurr = singlecurr->next;
            }
        }
        cout << endl;
        DLL = DLL->next;
    }
}


