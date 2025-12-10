/*
    Author: Dane Wolfe
    Date: 2/25/2025
    Description: A header file for the File and FileManager classes
*/

#pragma once

#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include <string>
#include <vector>
#include "LinkedList.hpp"

/* A class for representing a file's location in storage on the hard drive */
class File{
    private:
        std::string fileName;
        LinkedList<int>* contents;
    public:
        File(std::string fileName);
        ~File();
        std::string getFileName();
        void addBlock(int block);
        int fileSize();
        int* getFileBlocks();
};

/* A class for representing the File Manager system of a hard drive, which manages the different files and open blocks on the hard drive */
class FileManager{
    private:
        char* hardDrive;
        int size;
        Queue<int>* blockQueue;
        LinkedList<File*>* storedFiles;
    public:
        FileManager(int size);
        ~FileManager();
        void addFile(std::string fileName, std::string contents);
        void deleteFile(std::string fileName);
        std::string readFile(std::string fileName);
        std::vector<std::string> getFileNames();
        File* getFileByName(std::string fileName);
        void op999();
};



#endif
