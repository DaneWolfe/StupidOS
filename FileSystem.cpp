/*
    Author: Dane Wolfe
    Date: 2/22/2025
    Description: An implementation of a File class (represents files and their locations in memory) and a FileManager class (A representation of a hard drive management system)
*/

#include <string>
#include <vector>
#include <fstream>
#include "LinkedList.hpp"
#include "FileSystem.h"

/* A constructor for a new File */
File::File(std::string fileName){
    this->fileName = fileName;
    contents = new LinkedList<int>;
}

/* A deconstructor for a File object */
File::~File(){
    delete contents;
}


/* Gets the file name */
std::string File::getFileName(){
    return fileName;
}

/* Adds the index for a block of data onto the contents linked list */
void File::addBlock(int block){
    contents->addTail(block);
}

/* Returns the size of the contents linked list */
int File::fileSize(){
    return contents->getSize();
}

/* Returns an array of the indexes for the file in the hard drive */
int* File::getFileBlocks(){
    int* fileBlocks = new int[contents->getSize()];
    Node<int>* current = contents->getFront();
    for(int i = 0; i < contents->getSize(); i++){
        fileBlocks[i] = current->getData();
        current = current->getNext();
    }

    return fileBlocks;
}

/* A constructor for a FileManager object, so that the size can be set */
FileManager::FileManager(int size){
    blockQueue = new Queue<int>();
    storedFiles = new LinkedList<File*>();
    hardDrive = new char[size];
    for(int i = 0; i < size; i++){
        hardDrive[i] = '\0';
        blockQueue->enqueue(i);
    }
    this->size = size;
}

/* A deconstructor for a FileManager object, to delete the allocated memory of the hardDrive */
FileManager::~FileManager(){
    delete[] hardDrive;
    delete blockQueue;
    delete storedFiles;
}


/* Adds a file to the hard drive */
void FileManager::addFile(std::string fileName, std::string contents){
    
    if(blockQueue->isEmpty()){
        std::cout << "The hard drive is full!" << std::endl;
        return;
    }
    
    File* newFile = new File(fileName);

    /* Find the alphabetical place of the new file (capitalized letters have higher precedence) */
    /*
    Node<File*>* current = storedFiles->getFront();
    Node<File*>* previous = nullptr;
    while(current != nullptr){
        if(fileName < current->getData()->getFileName()){
            break;
        }
        else{
            previous = current;
            current = current->getNext();
        }
    }

    if(previous == nullptr){
        storedFiles->addFront(newFile);
    }
    else{
        Node<File*>* newNode = new Node<File*>(newFile);
        storedFiles->arbitraryInsert(previous, newNode);
    }
    */
    /* I had prior coded the above section for alphabetical ordering, but didn't see the removal of this requirement. */
    storedFiles->addTail(newFile);

    /* Find the blocks necessray for the file contents */
    int index;
    for(char c : contents){
        if(blockQueue->isEmpty()){
            std::cout << "The hard drive is full!" << std::endl;
            return;
        }
        index = blockQueue->dequeue();
        hardDrive[index] = c;
        newFile->addBlock(index);
    }
}

/* Deletes a file from the hard drive, and stores the emptied blocks back to the blockQueue */
void FileManager::deleteFile(std::string fileName){
    
    /* Finds the file in the storedFiles list */
    Node<File*>* target = storedFiles->getFront();
    while(target != nullptr && target->getData()->getFileName() != fileName){
        target = target->getNext();
    }

    if(target == nullptr){
        std::cout << "There is no file by that name." << std::endl;
        return;
    }

    /* Store the emptied blocks back to the blockQueue, and delete the file pointer */
    int* fileBlocks = target->getData()->getFileBlocks();
    for(int i = 0; i < target->getData()->fileSize(); i++){
        hardDrive[fileBlocks[i]] = '\0';
        blockQueue->enqueue(fileBlocks[i]);
    }


    delete[] fileBlocks;
    storedFiles->remove(target->getData());
}

/* Returns the contents of a specified file */
std::string FileManager::readFile(std::string fileName){

    /* Find the file Node in the linked list */
    Node<File*>* target = storedFiles->getFront();
    while(target != nullptr){
        //std::cout << target->getData()->getFileName() << std::endl;
        if(target->getData()->getFileName() == fileName){
            break;
        }
        else{
            target = target->getNext();
        }
    }

    if(target ==  nullptr){
        return "\n";
    }
    else{
        std::string retString = "";
        int* fileBlocks = target->getData()->getFileBlocks();
        for(int i = 0; i < target->getData()->fileSize(); i++){
            retString += hardDrive[fileBlocks[i]];
        }
        return retString;
    }
}

/* returns all the file names in the hard drive */
std::vector<std::string> FileManager::getFileNames(){
    std::vector<std::string> fileNames;
    Node<File*>* current = storedFiles->getFront();
    while(current != nullptr){
        fileNames.push_back(current->getData()->getFileName());
        current = current->getNext();
    }
    return fileNames;
}

/* Finds a file in the hard drive, and returns it */
File* FileManager::getFileByName(std::string fileName){
    Node<File*>* current = storedFiles->getFront();
    while(current != nullptr && current->getData()->getFileName() != fileName){
        current = current->getNext();
    }
    if(current != nullptr){
        return current->getData();
    }
    return nullptr;
}

/* For option 999: Print all chars of the hard drive to the dump.hd file */
void FileManager::op999(){
    
    FILE* myFile = fopen("dump.hd", "w");

    for(int i = 0; i < size; i++){
        fprintf(myFile, "%c", hardDrive[i]);
    }

    fclose(myFile);

}

