/*
    Author: Dane Wolfe
    Date: 2/22/2025
    Description: For now, a test main for the other class implementations
*/

#include "queue_Wolfe.hpp"
#include "LinkedList.hpp"
#include "FileSystem.h"
#include <iostream>
#include <string>
#include <fstream>

int main(int argc, char** argv){

    int hardDriveSize = 0;
    FileManager* hardDrive;
    
    /* To deal with the terminal flags */
    /* Three arguments; -s and size */
    if(argc == 3){
        /* Handles the size of the hard drive */
        if(std::string(argv[1]).compare("-s") == 0){
            for(int i = 0; argv[2][i] != '\0'; i++){
                hardDriveSize *= 10;
                hardDriveSize += argv[2][i] - '0';
            }

            hardDrive = new FileManager(hardDriveSize);
        }
        else{
            std::cout << "Incorrect usage of arguments" << std::endl;
            exit(0);
        }
    }
    /* Five arguments; includes -f and fileName */
    else if(argc == 5){
        /* Also handles the size of the hard drive */
        if(std::string(argv[1]).compare("-s") == 0){
            for(int i = 0; argv[2][i] != '\0'; i++){
                hardDriveSize *= 10;
                hardDriveSize += argv[2][i] - '0';
            }
        }
        else{
            std::cout << "Incorrect usage of arguments" << std::endl;
            exit(0);
        }

        hardDrive = new FileManager(hardDriveSize);

        /* Handles the initial start files */
        if(std::string(argv[3]).compare("-f") == 0){
            std::ifstream readFile;
            readFile.open(std::string(argv[4]));
        
            std::string line;
            while(std::getline(readFile, line)){
                std::string fileName = line.substr(0, line.find(':'));
                std::string contents = line.substr(line.find(':') + 1);
                hardDrive->addFile(fileName, contents);
            }
            readFile.close();
        }
        else{
            std::cout << "Incorrect usage of arguments" << std::endl;
        }
    }
    else{
        std::cout << "Incorrect number of arguments" << std::endl;
        std::cout << "Usage: ./exe -s SIZE [-f  FILE]" << std::endl;
        exit(0);
    }

    /* Main simulation loop */
    int choice = -1;
    while(choice != 0){

        std::cout << "Menu:" << std::endl;
        std::cout << "1 - Show files on hard drive" << std::endl;
        std::cout << "2 - Add a file" << std::endl;
        std::cout << "3 - Delete a file" << std::endl;
        std::cout << "4 - Output a file" << std::endl;
        std::cout << "0 - Exit simulation" << std::endl;
        
        std::cin >> choice;

        /* If the input is not an int */
        if(std::cin.fail()){
            //std::cout << "Incorrect input." << std::endl;
            choice = 0;
        }
        else if(choice == 0){}
        /* To handle choice 1: Printing the files and their sizes */
        else if(choice == 1){
            std::vector<std::string> names = hardDrive->getFileNames();
            printf("%-44s%10s\n", "Filename", "size");
            /* This prints by grabbing the first item in the vector then popping it off. Not the ideal implementation but I have bigger worries */
            while(!names.empty()){
                std::string name = names[0];
                printf("%-44s%10s\n", name.c_str(), (std::to_string(hardDrive->getFileByName(name)->fileSize()) + " blk").c_str());
                names.erase(names.begin());
            }
        }
        /* To handle choice 2: Adding in a new file given file name and contents */
        else if(choice == 2){
            std::cin.ignore();
            std::cout << "Enter filename: ";
            std::string fileName;
            std::getline(std::cin, fileName);
            std::cout << "Enter content string: ";
            std::string contents;
            std::getline(std::cin, contents);
            
            hardDrive->addFile(fileName, contents);
        }
        /* To handle choice 3: Given a file name, remove that file from the hard drive */
        else if(choice == 3){
            std::cin.ignore();
            std::cout << "Enter filename: ";
            std::string fileName;
            std::getline(std::cin, fileName);

            hardDrive->deleteFile(fileName);
        }
        /* To handle choice 4: Given a file name, display the contents of that file */
        else if(choice == 4){
            std::cin.ignore();
            std::cout << "Enter filename: ";
            std::string fileName;
            std::getline(std::cin, fileName);

            std::string contents = hardDrive->readFile(fileName);
            if(contents == "\n"){
                std::cout << "There is no file by that name." << std::endl;
            }
            else{
                printf("%-30sContents\n", "Filename");
                printf("%-30s%s\n", fileName.c_str(), contents.c_str());
            }
        }
        /* To handle choice 111: Outputs option 1 to a file named "dump.names" */
        else if(choice == 111){
            
            FILE* myFile = fopen("./dump.names", "w");
            fprintf(myFile, "%-44s%10s\n", "Filename", "size");

            std::vector<std::string> names = hardDrive->getFileNames();
            for(std::string name : names){
                fprintf(myFile, "%-44s%10s\n", name.c_str(), (std::to_string(hardDrive->getFileByName(name)->fileSize()) + " blk").c_str());
            }

            fclose(myFile);
        }
        /* To handle choice 999: dumps all the chars of the hard drive to "dump.hd" */
        else if(choice == 999){

            hardDrive->op999();

        }
        else{
            //std::cout << "Incorrect option. Try again." << std::endl;
        }
    }
    
    delete hardDrive;
    return 0;
}
