#include<iostream>
#include<fstream>
#include<map>
#include<string>
#include<cctype>
#include<algorithm>
#include"lang.h"

using namespace std;

lang::lang() {};

lang::lang(const char* rifname, const char* tfname, int k, double a)
{
    N = 0.0;
    order = k;
    alpha = a;
    t.open(tfname);
    lang::initFcm(rifname, k, a);
}

void lang::initFcm(const char* rifname, int k, double a)
{
    f.open(rifname);
    f.setAlpha(a);
    f.setOrder(k);
    f.extract();
    f.computeBps();
    f.computeAverageBps();
}

int lang::openri(const char* fname)
{
    ri.open(fname);
    return ri.good();
}

int lang::opent(const char* fname)
{
    t.open(fname);
    return t.good();
}

std::map<std::string,std::map<char,double>> lang::getFcm()
{
    return f.getBps();
}

void lang::estimate()
{
    int k;
    char next;
    std::string line;
    std::string block;
    std::string context;
    std::map<std::string,std::map<char,double>> riFcm = lang::getFcm();
    while(std::getline(t,line))
    {
        // Convert string to lower
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c){ return std::tolower(c); });

        // Loop through every substring
        // of k+1 size
        k = 0;
        while((order + k) < line.size())
        {
            block = line.substr(k, (order+1));
            context = block.substr(0, order);
            next = block[order];

            // Increment N variable
            // if context is defined
            if(riFcm.find(context) != riFcm.end())
            {
                N += riFcm[context][next];
            }
            
            k++;
        }
    }
}

double lang::getN()
{
    return N;
}

// int main(int argc, char** argv)
// {
//     const char* rifname = argv[1];
//     const char* tfname = argv[2];
//     int k = atoi(argv[3]);
//     double a = atof(argv[4]);

//     lang lang(rifname, tfname, k, a);
//     lang.estimate();
//     std::cout << (long) lang.getN() << " bits" << std::endl;
// }
