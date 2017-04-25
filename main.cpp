#include <iostream>
#include <vector>
#include <string>
#include "./src/SearchEngine.cpp"

int main()
{
    std::vector<FindFile> findfiles;
    
    std::string path;
    
    std::cin>>path;
    
    searchbyLine(path, "USB", findfiles);
    for(int i = 0; i < findfiles.size(); i++)
    {
        std::cout<< findfiles.at(i).nameFile<<std::endl;
        for(int j = 0; j < findfiles.at(i).lineNumbers.size(); j++)
            std::cout<< findfiles.at(i).lineNumbers.at(j)<<"   ";
        std::cout<< std::endl;
    }
    return 0;
}