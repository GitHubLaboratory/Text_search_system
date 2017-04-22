#include <iostream>
#include <vector>
#include <string>
#include "./src/ClassTest.h"
#include "./src/SearchEngine.cpp"

int main()
{
    std::vector<std::string> files;
    std::string stringF;
    
    std::vector<int> stri;

    fileSearch("G:\\log.txt", "USB", stri);
    for(int i = 0; i < stri.size(); i++)
    {
        std::cout<<stri.at(i)<<"  ";
        std::cout<<getStringF("G:\\log.txt", stri.at(i), stringF)<<" "<<stringF<<std::endl;
    }
    
//    int dir = getdir("C:\\", files);
//    if(dir)
//    {
//        int size = files.size();
//        for(int i = 0; i < size; i++)
//        {
//            std::cout<<files.at(i)<<std::endl;
//        }
//    }
    return 0;
}