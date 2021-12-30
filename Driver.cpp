#include<iostream> 
#include "MiniGit.hpp"
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

//CSCI 2270 Spring 2021 Final Project - MiniGit 
//Adam Vitti, Gabriel Vitti, Tanner Leise

void displayMainMenu(){
    //give all the options written in the writeup
    cout << "----------MAIN MENU----------" << endl;
    cout << "Select an option with the integer value: " << endl;
    cout << "1. initialize" << endl;
    cout << "2. add" << endl;
    cout << "3. remove" << endl;
    cout << "4. commit" << endl;
    cout << "5. checkout" << endl;
    cout << "6. quit" << endl;
    cout << "-----------------------------" << endl;
    cout << "Your selection: ";
}

int main(int argc, char* argv[]){
    int globalcounter = 0;
    bool globalEn = true;
    MiniGit* Git;
    string stringInput;
    int input = 0;
    bool done = false;
    bool mgInitialized = false;
    doublyNode* DLL;

    while(!done){
        //Main Menu:   
        displayMainMenu();
        getline(cin, stringInput);
        if(isdigit(stringInput[0])){
            input = stoi(stringInput);
        }
        else{
            input = -1;
        }
        
        //Add error handling for incorrect input...
            switch(input){
                case 1: //initialize
                {
                    if(!mgInitialized){ //checks to see if user has already initialized a repo 
                        mgInitialized = true;
                        Git = new MiniGit(); //initialize class and constructor (creates .minigit directory)
                        DLL = Git->initializeNewRepo(); //creates the DLL and sets head of SLL, returns the DLL
                        cout << "New Repo initialized!" << endl;
                    }else{
                        cout << "Repo already initialized... " << endl << endl; //Goes back to menu
                    }
                }   
                    break;

                case 2: //add file
                {   
                    if(mgInitialized && globalEn){
                        cout << "Enter file name to add: ";
                        getline(cin, stringInput);
                        if(!Git->fileExists(stringInput)){ //file doesn't exist in local directory
                            cout << "File name does not exist in current directory." << endl << endl; //Goes back to menu
                        }else{ //file exists
                            //Check SLL for file (if it has already been added)
                            if(Git->searchSLL(stringInput, DLL->singlehead) != NULL){ //Filename is already added
                                cout << "File with name \"" << stringInput << "\" already exists!" << endl << endl; //goes back to menu
                            }else{
                                singlyNode* temp;
                                singlyNode* newSinglyNode = new singlyNode;
                                newSinglyNode->fileName = stringInput;
                                newSinglyNode->versionNumber = 0; //version number will always start at 0
                                newSinglyNode->fileVersion = to_string(newSinglyNode->versionNumber) + "__" + stringInput; 
                                newSinglyNode->next = NULL;
                                //point previous node's next to new SLL Node
                                if(DLL->singlehead == NULL){
                                    DLL->singlehead = newSinglyNode;
                                }
                                else{
                                temp = Git->traverseSLL(DLL->singlehead); //returns last node in list
                                temp->next = newSinglyNode; //adds the new file node to the end of the singly list
                                }
                            }
                        }
                        Git->prettyPrint();
                    }else{
                        if(!mgInitialized){
                        cout << "Git not initialized!" << endl << endl;
                        }
                        else{
                            cout << "Must go restore to current commit: " << globalcounter << endl;
                        }
                    }

                }
                    break;
                case 3: //remove file
                {
                    if(mgInitialized && globalEn){
                singlyNode* temp = NULL;
                cout << "Please enter the file name to delete: ";
                getline(cin, stringInput);

                if (!Git->fileExists(stringInput)){ //if file doens't exist, returns to main menu
                    cout << "That file name does not exist" << endl << endl;
                }else{
                    temp = Git->searchSLL(stringInput, DLL->singlehead); //returns pointer to requested file


                    if(temp == NULL){               //If file exists but is not in the LL
                        cout << "This isn't in your added files!" << endl;
                        break;
                    }

                       if (temp == DLL->singlehead){ //handles head case
                        DLL->singlehead = temp->next;
                        delete temp;
                        temp = NULL;

                    }else if (temp->next == NULL){ //handles tail case
                        singlyNode* temp_prev = Git->getPrevSLL(stringInput, DLL->singlehead);
                        temp_prev->next = NULL;
                        delete temp;
                        temp = NULL;

                    }
                  else { //handles middle cases
                        singlyNode* temp_prev = Git->getPrevSLL(stringInput, DLL->singlehead);
                        temp_prev->next = temp->next;
                        delete temp;
                        temp = NULL;
                    }

                    cout << "File with name \"" << stringInput << "\" has been deleted" << endl << endl; //returns to menu
                    }
                    }else{
                        if(!mgInitialized){
                        cout << "Git not initialized!" << endl << endl;
                        }
                        else{
                            cout << "Must go restore to current commit: " << globalcounter << endl;
                        }
                    }
                    Git->prettyPrint();
                    break;
                }

                case 4: //commit file to minigit
                {
                    if(mgInitialized && globalEn){
                    //Traverse current SLL for every file
                    singlyNode* temp = DLL->singlehead;
                    while(temp != NULL){
                        //1. Check if SLL.filenameVersion is already inside .minigit directory
                        if(!Git->fileExists(".minigit/" + temp->fileVersion)){ //file doesn't exist in .minigit
                             //2. If not there: copy current local file into the .minigit directory with version number
                             Git->copyfileSame(temp); //does not increment version number
                        }else{ //file already exists in .minigit
                             //3. If yes there: current version is already there, compare current .minigit fileversion with current local fileversion
                            if(Git->compareFiles(temp)){ //files are identical
                                //do nothing and move on
                            }else{ //files are different
                                //copy file with increased file version for Name and SLL node
                                Git->copyfileIncrement(temp);
                            }
                        }
                        temp = temp->next;
                    }
                
            //END OF CASE create the DLL node containing the SLL       
                    doublyNode* newDLL = new doublyNode; //creates new DLL for new commit
                    doublyNode* prevDLL = DLL; //gets previous DLL
                    prevDLL->next = newDLL; //sets previous next to new DLL
                    newDLL->previous = prevDLL; //sets new DLL previous to previous DLL
                    newDLL->commitNumber = prevDLL->commitNumber+1; //increments commit number 

                    globalcounter++;
                
            //copy old SLL into new DLL 
                    Git->copySLL(DLL, newDLL);

                    DLL = newDLL;
                    
                    }else{
                        if(!mgInitialized){
                        cout << "Git not initialized!" << endl << endl;
                        }
                        else{
                            cout << "Must go restore to current commit: " << globalcounter << endl;
                        }
                    }
                    break;
                }

                case 5: //checkout previous commit
                {
                if(mgInitialized){
                    doublyNode* checkoutDLL;
                    string stringInput;
                    int inp;
                    bool done1 = false;
                    bool cancel = false;

                    while (done1 == false){ //Warns user that checkout will over overwrite current files
                        cout << "WARNING: Local file changes will be lost if not committed to the minigit directory\n1) Continue\n2) Cancel" << endl;
                        getline(cin,stringInput);
                            inp = stoi(stringInput);


                        switch (inp){
                            case 1: //Continue
                                done1 = true;
                            break;
                            case 2: //Cancel 
                                cancel = true;
                                done1 = true;
                            break;
                            default:
                                cout << "Invalid input." << endl;
                            break;
                        }
                    }
                    done1 = false;
                    if (cancel == true){
                    }else{
                        while (done1 == false){ // What previous commit to checkout
                            cout << "Please enter a commit number to checkout or -1 to cancel: ";
                            getline(cin,stringInput);
                            inp = stoi(stringInput);

                            if (inp == -1){
                                break;
                            }
                            else{
                            checkoutDLL = Git->searchDLL(inp); //Gets the DLL with the requested checkout number
                            if (checkoutDLL == NULL){
                                cout << "Invalid commit number." << endl;
                            }
                            else{
                                done1 = true;
                                singlyNode* tempSLL = DLL->singlehead; //start of current SLL
                                while(tempSLL != NULL){ // deleting all local files
                                    if(Git->fileExists(tempSLL->fileName)){
                                        fs::remove(tempSLL->fileName);
                                    }
                                    tempSLL = tempSLL->next;
                                }

                                singlyNode* newSLL = Git->searchDLL(inp)->singlehead; //start of previous SLL 
                                while(newSLL != NULL){ //copying files from the minigit to the local directory
                                    Git->copyFromRepo(newSLL);
                                    newSLL = newSLL->next;
                                }
                                
                                if (inp == globalcounter){ // disables or enables other minigit functionallity
                                    globalEn = true;
                                }
                                else{
                                    globalEn = false;
                                }
                                inp = 0;
                            }
                            }
                }
                    }

                    }
                    else{
                        cout << "Git Not Initialized" << endl << endl;
                    }
                }
                    break;

                case 6:  //quit
                {
                    if(!mgInitialized){
                        return 0;
                    }
                    delete Git; 
                    done = true;
                }   
                break;
                default:
                cout << "Invalid input: " << endl;
                break;
            }
        
    }
    return 0;
}
