#include "ctest.h"
#include "../src/SearchEngine.h"
#include <iostream>

SearchEngine se;
char path[] = "./test.txt";
char dir[] = "./";

CTEST(validationExtensionf, validationExtensionf_test)
{
    int expected = 1;
    int result = se.validationExtensionf("asd.txt", "txt");
    ASSERT_EQUAL(expected, result);
}

CTEST(concat, concat_test)
{
    char *s1, *s2;
    s1 = new char [3];
    s2 = new char [4];
    s1 = "abc";
    s2 = "defg";
    char *exp  = new char [7];
    exp = "abcdefg";
    char *real = se.concat(s1,s2);
    ASSERT_STR(exp, real);
}

CTEST(getStringF, getStringF_test)
{
    std::string exp = "/cast [@focus] парализующий удар";
    std::string result;
    se.getStringF(path, 2, result);
    ASSERT_STR(exp.c_str(), result.c_str());
}

CTEST(fileSearch, fileSearch_test)
{
    std::vector<int> vect;
    se.fileSearch(path,"MACRO", vect);
    std::vector<int> exp {0,4,8,12,15};
    int result = 1;
    int size = exp.size();
    if (size == vect.size())
    {
        for(int i = 0; i < size; i++)
        {
            if(exp.at(i) != vect.at(i))
            {
                result = 0;
                break;
            }
        }
    }
    else
        result = 0;
    ASSERT_EQUAL(result, 1);
}

CTEST(getdir, getdir_test)
{
    std::vector<char*> exp {".", "..", "2.txt", "test.txt", "tss_test"};
    std::vector<char*> vect;
    se.getdir(dir, vect);
    int result = 1;
    int size = exp.size();
    if (size == vect.size())
    {
        for(int i = 0; i < size; i++)
        {
            char *q1 = exp.at(i);
            char *q2 = vect.at(i);
            if(*q1 != *q2)
            {
                result = 0;
                break;
            }
        }
    }
    else
        result = 0;
    ASSERT_EQUAL(result, 1);
}

CTEST(searchbyLine, searchbyLine_test)
{
    std::vector<FindFile> vector;
    std::string word = "use";
    std::vector<FindFile> vect;
    FindFile w1;
    w1.lineNumbers =  std::vector<int> {3, 72, 74 ,401, 414};
    w1.nameFile = "ctest.h";
    vect.push_back(w1);
    w1.lineNumbers =  std::vector<int> {87};
    w1.nameFile = "searchengine_test.cpp";
    vect.push_back(w1);
//    w1.lineNumbers =  std::vector<int> {6, 10};
//    w1.nameFile = "./test.txt";
//    vect.push_back(w1);
    se.searchbyLine(dir, word, vector);
    int result = 1;
    int size = vect.size();
    if (size == vector.size())
    {
        for(int i = 0; i < size; i++)
        {
            std::string q1 = vect.at(i).nameFile;
            std::string q2 = vector.at(i).nameFile;
            if(q1 != q2)
            {
                result = 0;
                break;
            }
            int szr = vect.at(i).lineNumbers.size();
            int szo = vector.at(i).lineNumbers.size();
            if(szr != szo)
            {
                result = 0;
                break;
            }
            for(int j = 0; j < szr; j++)
            {
                int lnr = vector.at(i).lineNumbers.at(j);
                int dnr = vect.at(i).lineNumbers.at(j);
                if(lnr != dnr)
                {
                    result = 0;
                    break;
                }
            }
        }
    }
    else
        result = 0;
    ASSERT_EQUAL(result, 1);

}
