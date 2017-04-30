#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <vector>
#include <string>
#include "./src/SearchEngine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();


    SearchEngine searchEngined;
    std::vector<FindFile> findfiles;

    std::string path;

    std::string str;


    searchEngined.getStringF("C:/log.txt", 5, str);

    std::cout<<str;

    std::cin>>path;
    searchEngined.searchbyLine(path, "USB", findfiles);
    for(int i = 0; i < findfiles.size(); i++)
    {
        std::cout<< findfiles.at(i).nameFile<<std::endl;
        for(int j = 0; j < findfiles.at(i).lineNumbers.size(); j++)
            std::cout<< findfiles.at(i).lineNumbers.at(j)<<"   ";
        std::cout<< std::endl;
    }


    return a.exec();
}
