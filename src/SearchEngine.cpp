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

int SearchEngine::getStringF(std::string path, int numberS, std::string &stringF)
{
    FILE *fp = fopen(path.c_str(), "rb");
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
        if(n == numberS) 
            stringF += buf[0];
        
        if(buf[0] == '\n') n++;
    }
    fclose(fp);
    return 0;
}

int SearchEngine::fileSearch(std::string path, std::string str, std::vector<int> &lineNumbers)
{
    FILE *fp = fopen(path.c_str(), "rb");
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
            lineNumbers.push_back(n);
            ielem = 0;
        }
    }
    fclose(fp);
    return 1;
}

int SearchEngine::getdir(std::string dir, std::vector<std::string> &files)
{
    DIR *dp;
    struct dirent *dirp;
    
    if((dp  = opendir(dir.c_str())) == NULL)
        return 0;

    while ((dirp = readdir(dp)) != NULL) {
        files.push_back(std::string(dirp->d_name));
    }
    closedir(dp);
    return 1;
}

int SearchEngine::validationExtensionf(std::string file, std::string extension)
{
    int n = extension.length() - 1;
    for(int i = file.length() - 1; i >= 0; i--)
    {   
        if(file.at(i) == '.') 
            return 1;
        
        if(n < 0) 
            return 0;
        
        if(file.at(i) == extension.at(n)) 
            n--;
        else
            return 0;
    }
    return 0;
}

int SearchEngine::searchbyLine(std::string path, std::string extension, std::string str_tosearch, std::vector<FindFile> &findFiles)
{
    std::vector<std::string> files;
    int dir = getdir(path, files);
    if(dir)
    {
        int size = files.size();
        for(int i = 0; i < size; i++)
        {
            if(validationExtensionf(files.at(i), extension))
            {
                std::vector<int> lineNumbers;
                int fileSearchR = fileSearch(path + '\\' + files.at(i), str_tosearch, lineNumbers);
                if(fileSearchR && lineNumbers.size() > 0)
                {
                    FindFile findFile;
                    findFile.lineNumbers = lineNumbers;
                    findFile.nameFile = files.at(i);
                    findFiles.push_back(findFile);
                }
                lineNumbers.clear();
            }
        }
        files.clear();
        return 1;
    }
    else
    {
        files.clear();
        return 0;
    }
}

int SearchEngine::searchbyLine(std::string path, std::string str_tosearch, std::vector<FindFile> &findFiles)
{
    std::vector<std::string> files;
    int dir = getdir(path, files);
    if(dir)
    {
        int size = files.size();
        for(int i = 0; i < size; i++)
        {
            std::vector<int> lineNumbers;
            int fileSearchR = fileSearch(path + '\\' + files.at(i), str_tosearch, lineNumbers);
            if(fileSearchR && lineNumbers.size() > 0)
            {
                FindFile findFile;
                findFile.lineNumbers = lineNumbers;
                findFile.nameFile = files.at(i);
                findFiles.push_back(findFile);
            }
            lineNumbers.clear();
        }
        return 1;
    }
    else
    {
        files.clear();
        return 0;
    }
}

SearchEngine::SearchEngine() {
}

SearchEngine::SearchEngine(const SearchEngine& orig) {
}

SearchEngine::~SearchEngine() {
}