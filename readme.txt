CSCI 2270 Spring 2021 Final Project - MiniGit 
Programmed by: Adam Vitti, Gabriel Vitti, Tanner Leise

Link to GitHub: https://github.com/advi4972/Csci2270_MiniGit (private repo)

Overview:
Our "MiniGit" project is a small scale, git version control software that works on your local machine. It supports 
.txt, .cpp, and .hpp files. However, the history of versions are only stored while the program is executing. Once 
the user terminates the program, within the terminal, the directory containing all the backup files will be deleted.

Usage:
When running our program the user is prompted with a menu within the terminal aksing what they would like to do. There 
are 6 menu options that are given: 1.Initialize 2.Add 3.Remove 4.Commit 5.Checkout 6.Quit 

If a user chooses "1" our program creates a new (physical) ".minigit" directory within their current directory. The naming 
convention .folderName hides the minigit directory from a graphical user interface such as Finder (on macs) and 
File Explorer (on windows). Additionally, the program initializes a new MiniGit class member named "Git" in the driver file
that contains all of the nesessary functions for our program. 

If a user chooses "2" our program will prompt the user to enter a file name for which they would like to add to the minigit 
repository. If the file exists in their current directory, the file name will be copied and added to the singly linked list 
to be staged for commiting. 

If a user chooses "3" our program will prompt the user to enter a file name for which they would like to remove from the
singly linked list so that it is not added to the .minigit directory when commiting. If the file was within the singly
linked list, the node containing that file's information will be removed from the linked list. This means the file 
will not be commited when commiting. 

If a user chooses "4" our program executes differently depending on whether the added files are brand new, changed, or identical.
If the file being commited is brand new and no versions can be found inside the minigit, we add a copy of the current file wihtout 
incrementing the version number since it is the first commit. However, if a previous file version is found within the minigit directory
we copy the file into a new file but with an incremented version number. Lastly, if the file being commited has not been edited from the 
previous version, we do nothing to the files nor the singly linked lists and simply return. 

If a user chooses "5" our program will first warn the user that checking out will overwrite their current data and asks if they would
like to continue or not. If the user decides to continue, the user is prompted to give an integer value corresponding to the commit 
version they would like to return their local directory to. If the input value is an existing commit number, our program first deletes
all files within the local directory and then retrieves the file version information from our doubly/singly linked list data structure.  
This version information is then used to retrieve the corresponding verion files within the .minigit directory and copies them back
into the local directory. After copying the files, the program disables the user from accessing any of the other minigit menu options until
they restore their local directory version to the most current commit. 

If a user chooses "6" our program simply deletes the initialzed "Git" class member, automatically calling the classes destructor. The 
destructor then handles deleting our doubly and singly linked lists, preventing any memory leaks. Additionally, the destructor will 
delete the newly created subdirectory ".minigit" and any files nested inside. The function ends and our program terminates completely. 


Functions:
Our project driver makes use of many MiniGit class functions that we wrote within the .hpp/.cpp files. Below is a list of
the functionality and operation of each class function that we wrote and use:

    1. singlyNode* newSingleNode(string name);
        - Creates a new node to be used within the singly linked lists (mostly used for our testing)
    2. doublyNode* initializeNewRepo();
        - Initializes the first doubly linked list node, sets it as the head, and then returns a pointer to it
    3. bool fileExists(string fileName); 
        - Checks the local directory if a file exists with the same name as the input string, returns true if exists, false otherwise
    4. singlyNode* traverseSLL(singlyNode* n); 
        - Traverses the entirety of a singly linked list and returns a pointer to the tail node, used to add a new node to the end of a SLL
    5. singlyNode* searchSLL(string fileName, singlyNode* start); 
        - Traverses a singly linked list looking for a node with the same name as the input string, returns a pointer to the requested node, otherwise returns NULL
    6. doublyNode* searchDLL(int cNumber); 
        - Traverses the doubly linked list and returns a pointer to the requested node by commit number, otherwise returns NULL
    7. singlyNode* getPrevSLL(string fileName, singlyNode* start);
        - Traverses a singly linked list and returns a pointer to the node that comes before the requested node (used for case 3. remove to remove SLL nodes)
    8. bool compareFiles(singlyNode* Node); 
        - Compares content of current file in local directory with its corresponding version file within the .minigit directory, returns true if identical, otherwise false
    9. void copyfileSame(singlyNode* node);  
        - Copies the content from current file in local directory to a newly created file within the .minigit directory without incrementing the version number
    10. void copyfileIncrement(singlyNode* node); 
        - Copies the content from current file in local directory to a newly created file within the .minigit directory and increments the version number
    11. void copyFromRepo(singlyNode* start); 
        - Copies the content from the .minigit file version to a newly created file within local directory, replacing what was previously there
    12. void copySLL(doublyNode* oldDLL, doublyNode* newDLL); 
        - Copies an entire singly linked list to a new doubly linked list node (for new commits)
    13. void prettyPrint(); 
        - Pretty prints our entire doubly/singly linked lists data structure
