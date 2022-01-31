#include<iostream>
#include<fstream>
#include<math.h>
#include<map>

using namespace std;

#define CHARSET_LENGTH 26

std::map<char,int> getMapBuffer()
{
    std::map<char,int> result;

    char i;
    for(i = 'a'; i <= 'z'; i++)
    {
        result[i] = 0;
    }

    return result;
}

std::map<string,map<char,int>> initBuffers(int k)
{
    int size = (int) pow(CHARSET_LENGTH, k);
    std::cout << size << std::endl;
    string tmp = string(k, 'a');

    std::map<string,std::map<char,int>> model;
    model[tmp] = getMapBuffer();

    int i = 1;
    char last;
    while(tmp != string(k, 'z'))
    {
        if(tmp[k-1] != 'z')
        {
            last = tmp[k-1];
            tmp[k-1] = last + 1;
        }
        else
        {
            tmp[k-1] = 'a';
            int j = 2;
            while(tmp[k-(j+1)] == 'z')
            {
                tmp[k-(j+1)] = 'a';
                j++;
            }
            char c = tmp[k-j];
            tmp[k-j] = c + 1;
        }
        model[tmp] = getMapBuffer();

    }

    return model;
}

void printModel(map<string,map<char,int>> model)
{
    for(const auto& elem : model)
    {
        for(const auto& sec : elem.second)
        {
            std::cout << elem.first << " >> " << sec.first << " : " << sec.second << std::endl;
        }
    }
}

int main(int argc, char** argv)
{
    std::map<string,std::map<char,int>> model;
    // Get filename
    const char* fname = argv[1];
   
    model = initBuffers(2);
    printModel(model);
}
