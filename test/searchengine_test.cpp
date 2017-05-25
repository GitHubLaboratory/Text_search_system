#include "ctest.h"
#include "../src/SearchEngine.h"
#include <iostream>

SearchEngine se;
char path[] = "./bin/test.txt";
char dir[] = "./bin/";

CTEST(validationExtensionf, validationExtensionf_test)
{
    int expected = 1;
    char ch[] = "asd.txt";
    int result = se.validationExtensionf(ch, "txt");
    ASSERT_EQUAL(expected, result);
}

CTEST(concat, concat_test)
{
    char ch1[] = "abc";
    char ch2[] = "defg";
    char exp[] = "abcdefg";
    char *real = se.concat(ch1,ch2);
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
    size_t size = exp.size();
    if (size == vect.size())
    {
        for(size_t i = 0; i < size; i++)
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
    std::vector<char*> exp {(char *) ".", (char *) "..", (char *) "test.txt", (char *) "test"};
    std::vector<char*> vect;
    se.getdir(dir, vect);
    int result = 1;

    if (exp.size() == vect.size())
    {
        for(size_t i = 0; i < vect.size() && result; i++)
        {
            char *q1 = vect.at(i);
            size_t size = exp.size();
            if (!size)
                continue;

            for (size_t j = 0; j < size; j++)
            {
                char *q2 = exp.at(j);
                if (!strcmp(q1, q2))
                {
                    exp.erase(exp.begin() + j);
                    break;
                }
            }
            if(size == exp.size())
                result = 0;
        }
    }
    else
        result = 0;
    ASSERT_EQUAL(result, 1);
}

bool vector_compare(FindFile a1, FindFile a2)
{
    if(strcmp(a1.nameFile, a2.nameFile))
        return false;

    if(a1.lineNumbers.size() != a2.lineNumbers.size())
        return false;

    size_t size = a1.lineNumbers.size();

    FindFile a2c = a2;

    for(size_t i = 0; i < size; i++)
    {
        size_t sz = a2c.lineNumbers.size();
        if(!sz)
            continue;

        for(size_t j = 0; j < sz; j++)
        {
            if(a1.lineNumbers.at(i) == a2c.lineNumbers.at(j))
            {
                a2c.lineNumbers.erase(a2c.lineNumbers.begin() + j);
                break;
            }
        }
        if(a2c.lineNumbers.size() == sz)
            return false;
    }
    if(a2c.lineNumbers.size() == 0)
        return true;
    else
        return false;
}

CTEST(searchbyLine, searchbyLine_test)
{
    std::vector<FindFile> vector;
    std::string word = "use";
    std::vector<FindFile> vect;
    FindFile w1;
    w1.lineNumbers =  std::vector<int> {6, 10};
    w1.nameFile = (char *) "test.txt";
    vect.push_back(w1);
    se.searchbyLine(dir, word, vector);
    int result = 1;
    if (vect.size() == vector.size())
    {
        size_t size = vect.size();
        for(size_t i = 0; i < size; i++)
        {
            size_t sz = vector.size();
            if(!sz)
                continue;

            for(size_t j = 0; j < sz; j++)
            {
                if(vector_compare(vect.at(i), vector.at(j)))
                {
                    vector.erase(vector.begin() + j);
                    break;
                }
            }
            if(vector.size() == sz)
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
