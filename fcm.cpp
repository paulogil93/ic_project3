#include<iostream>
#include<fstream>
#include<math.h>
#include<string>
#include<cctype>
#include<algorithm>
#include<map>
#include"fcm.h"

using namespace std;

fcm::fcm() {}

fcm::fcm(const char* fname, int k, double a)
{
    order = k;
    alpha = a;
    ifs.open(fname);
}

int fcm::open(const char* fname)
{
    ifs.open(fname);
    return ifs.good();
}

void fcm::initContextBuffer()
{
    fcm::generateAllKLengthSubstringsRec(fcm::getAlphabet(), "", fcm::getAlphabet().size(), fcm::getOrder());
}

std::map<char,int> fcm::initInputBuffer()
{
    std::map<char,int> buffer;

    for(int i = 0; i < alphabet.length(); i++)
    {
        buffer[alphabet[i]] = 0;
    }

    return buffer;
}

std::map<char,double> fcm::initDoubleInputBuffer()
{
    std::map<char,double> buffer;

    for(int i = 0; i < alphabet.length(); i++)
    {
        buffer[alphabet[i]] = 0.0;
    }

    return buffer;
}

void fcm::generateAllKLengthSubstringsRec(string set, string prefix, int n, int k)
{
    if (k == 0)
    {
        model[prefix] = fcm::initInputBuffer();
        return;
    }

    // Add all characters of alphabet
    // one by one; recursively
    // call for k equals to k-1
    for (int i = 0; i < n; i++)
    {
        string newPrefix;
        newPrefix = prefix + set[i];
        generateAllKLengthSubstringsRec(set, newPrefix, n, k - 1);
    }
}

void fcm::printModel()
{
    for(const auto& element : model)
    {
        for(const auto& input : element.second)
        {
            std::cout << element.first << " >> " << input.first << " : " << input.second << std::endl;
        }
    }
}

void fcm::extract()
{
    fcm::initContextBuffer();

    int w;
    char next;
    std::string line;
    std::string block;
    std::string context;

    while(std::getline(ifs, line))
    {
        // Convert string to lower
        std::transform(line.begin(), line.end(), line.begin(), [](unsigned char c){ return std::tolower(c); });
        
        // Loop through every substring
        // of k+1 size
        w = 0;
        while((order + w) < line.size())
        {
            block = line.substr(w, (order+1));
            context = block.substr(0, order);
            next = block[order];
            
            // Increment next outcome variable
            // if context is defined
            if(model.find(context) != model.end())
            {
                model[context][next]++;
            }
            
            w++;
        }
    }
}

void fcm::computeBps()
{
    std::map<string,int> sums;
    
    for(const auto& element : model)
    {
        sums[element.first] = 0;
        for(const auto& value : element.second)
        {
            sums[element.first] += value.second;
        }
    }

    for(const auto& element: model)
    {
        bps[element.first] = fcm::initDoubleInputBuffer();
        for(const auto& value : element.second)
        {
            double prob = (value.second + alpha)/(sums[element.first] + 4*alpha);
            double encodeBits = -log2(prob);
            bps[element.first][value.first] = encodeBits;
        }
    }
}

void fcm::computeAverageBps()
{
    int count = 0;
    double sum = 0;
    for(const auto& element : bps)
    {
        for(const auto& value : element.second)
        {
            count++;
            sum += value.second;
        }
    }

    abps = sum/count;
}

/* Basic getters and setters */

void fcm::setOrder(int k)
{
    order = k;
}

void fcm::setAlpha(double a)
{
    alpha = a;
}

void fcm::setAlphabet(string s)
{
    alphabet = s;
}

int fcm::getOrder()
{
    return order;
}

double fcm::getAlpha()
{
    return alpha;
}

std::string fcm::getAlphabet()
{
    return alphabet;
}

std::map<std::string,std::map<char,double>> fcm::getBps()
{
    return bps;
}

double fcm::getAverageBps()
{
    return abps;
}

// int main(int argc, char** argv)
// {
//     const char* fname = argv[1];
//     int k = atoi(argv[2]);
//     double a = atof(argv[3]);
//     fcm fcm(fname, k, a);
//     fcm.extract();
//     //fcm.printModel();
//     fcm.computeBps();
//     fcm.computeAverageBps();
//     std::cout << fcm.getAverageBps() << std::endl;
// }
