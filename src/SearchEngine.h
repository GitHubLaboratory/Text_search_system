/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SearchEngine.h
 * Author: Admin
 *
 * Created on 22 апреля 2017 г., 23:17
 */

#ifndef SEARCHENGINE_H
#define SEARCHENGINE_H
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>

struct FindFile
{                  
    std::vector<int> lineNumbers;
    std::string nameFile;
};  

class SearchEngine {
public:
    SearchEngine();
    SearchEngine(const SearchEngine& orig);
    int getStringF(std::string path, int numberS, std::string &stringF);
    int searchbyLine(std::string path, std::string extension, std::string str_tosearch, std::vector<FindFile> &findFiles);
    int searchbyLine(std::string path, std::string str_tosearch, std::vector<FindFile> &findFiles);
    virtual ~SearchEngine();
private:
    int fileSearch(std::string path, std::string str, std::vector<int> &found_numbers);
    int getdir (std::string dir, std::vector<std::string> &files);
    int validationExtensionf(std::string file, std::string extension);
};

#endif /* SEARCHENGINE_H */

