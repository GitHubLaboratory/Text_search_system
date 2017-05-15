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

int SearchEngine::getStringF(char *path, int numberS, std::string &stringF)
{
    struct stat st;
    if(stat(path, &st) != 0)
        return 0;
    if(!S_ISREG(st.st_mode))
        return 0;

    FILE *fp = fopen(path, "r");
    stringF = ""; 
    int n = 0;
    char buf[2];
    while(fgets(buf, 2, fp) != NULL)
    {
        if (n > numberS)
            break;

        if (n == numberS)
            stringF += buf[0];
        
        if(buf[0] == '\n')
            n++;
    }
    if(stringF == "")
    {
        fclose(fp);
        return 0;
    }
    else
    {
        fclose(fp);
        return 1;
    }
}

int SearchEngine::fileSearch(char *path, std::string str, std::vector<int> &lineNumbers)
{
    struct stat st;
    if(stat(path, &st) != 0)
        return 0;
    if(!S_ISREG(st.st_mode))
        return 0;

    FILE *fp = fopen(path, "r");

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

int SearchEngine::getdir(char *dir, std::vector<char*> &files)
{
    DIR *dp;

    if((dp  = opendir(dir)) == NULL)
        return 0;

    struct dirent *dirp;
    while ((dirp = readdir(dp)) != NULL)
    {
        char *dire = new char[strlen(dirp->d_name) + 1];
        strcpy(dire, dirp->d_name);
        files.push_back(dire);
    }
    closedir(dp);
    return 1;
}

int SearchEngine::validationExtensionf(char *file, std::string extension)
{
    int n = extension.length() - 1;
    for(size_t i = strlen(file) - 1; i >= 0; i--)
    {
        if(file[i] == '.')
            return 1;

        if(n < 0)
            return 0;
        
        if(file[i] == extension.at(n))
            n--;
        else
            return 0;
    }
    return 0;
}
char* SearchEngine::concat(char *s1, char *s2)
{
    size_t len1 = strlen(s1);
    size_t len2 = strlen(s2);
    char *result = new char[(len1 + len2 + 1)];
    if (!result)
        return NULL;

    memcpy(result, s1, len1);
    memcpy(result + len1, s2, len2 + 1);
    return result;
}

int SearchEngine::searchbyLine(char *path, std::string str_tosearch, std::vector<FindFile> &findFiles)
{
    std::vector<char*> files;
    int dir = getdir(path, files);
    if(dir)
    {
        int size = files.size();
        for(int i = 0; i < size; i++)
        {
            std::vector<int> lineNumbers;
            char *ch = concat(path, files.at(i));
            int fileSearchR = fileSearch(ch, str_tosearch, lineNumbers);
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


int SearchEngine::searchbyLine(char *path, std::string extension, std::string str_tosearch, std::vector<FindFile> &findFiles)
{
    std::vector<char*> files;
    int dir = getdir(path, files);
    if(dir)
    {
        int size = files.size();
        for(int i = 0; i < size; i++)
        {
            char *file = files.at(i);
            if(validationExtensionf(file, extension))
            {
                std::vector<int> lineNumbers;
                char *ch = concat(path, file);
                int fileSearchR = fileSearch(ch, str_tosearch, lineNumbers);
                if(fileSearchR && lineNumbers.size() > 0)
                {
                    FindFile findFile;
                    findFile.lineNumbers = lineNumbers;
                    findFile.nameFile = file;
                    findFiles.push_back(findFile);
                }
                lineNumbers.clear();
            }
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
