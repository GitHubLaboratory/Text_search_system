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
#include <string.h>
#include <fstream>
#include <sys/stat.h>

struct FindFile
{                  
    std::vector<int> lineNumbers;
    char *nameFile;
};  

class SearchEngine {
public:
    SearchEngine();
    SearchEngine(const SearchEngine& orig);
    int searchbyLine(char *path, std::string extension, std::string str_tosearch, std::vector<FindFile> &findFiles);
    int searchbyLine(char *path, std::string str_tosearch, std::vector<FindFile> &findFiles);
    int fileSearch(char *path, std::string str, std::vector<int> &found_numbers);
    int getStringF(char *path, int numberS, std::string &stringF);
    int validationExtensionf(char *file, std::string extension);
    int getdir (char *dir, std::vector<char*> &files);
    char* concat(char *s1, char *s2);
    virtual ~SearchEngine();

private:

};

#endif /* SEARCHENGINE_H */

