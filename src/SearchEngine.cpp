/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   SearchEngine.cpp
 * Author: Admin
 * 
 * Created on 22 апреля 2017 г., 23:17
 */

#include "SearchEngine.h"

//    char *filec = new char[file.length() + 1];
//
//    std::strcpy(filec, file.c_str());
//    
//    FILE *fp = fopen(filec, "r");
//    delete[] filec;

int getStringF(std::string path, int numberS, std::string &stringF)
{
    FILE *fp = fopen(path.c_str(), "r");
    stringF = ""; 
    int n = 0;
    char buf[2];
    while(fgets(buf, 2, fp) != NULL)
    {
        if(n  > numberS)
        {
            fclose(fp);
            return 1;
        }
        if(n == numberS) stringF += buf[0];
        if(buf[0] == '\n') n++;
    }
    fclose(fp);
    if(n < numberS) return 0;
    return -1;
}

int fileSearch(std::string path, std::string str, std::vector<int> &found_numbers)
{
    FILE *fp = fopen(path.c_str(), "r");
    int n = 0;
    int ielem = 0;
    char buf[2];
    while(fgets(buf, 2, fp) != NULL)
    {
        if(buf[0] == '\n') n++;
        if(buf[0] == str.at(ielem))
            ielem++;
        else 
            ielem = 0;
        
        if(ielem == (int)str.length())
        {
            found_numbers.push_back(n);
            ielem = 0;
        }
    }
    fclose(fp);
    return 1;
}

int getdir (std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    if((dp  = opendir(dir.c_str())) == NULL) {
        return 0;
    }

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 1;
}

int validationExtensionf(std::string file, std::string extension)
{
    int n = extension.length() - 1;
    int filen =  file.length() - 1;
    for(int i = filen; i > 0; i--)
    {   
        if(file.at(i) == '.') 
            break;
        
        if(n < 0) 
            return 0;
        
        if(file.at(i) == extension.at(n)) 
            n--;
        else
            return 0;
    }
    return 1;
}

SearchEngine::SearchEngine() {
}

SearchEngine::SearchEngine(const SearchEngine& orig) {
}

SearchEngine::~SearchEngine() {
}

