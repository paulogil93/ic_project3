#include<iostream>
#include<fstream>
#include<math.h>
#include<map>

using namespace std;

#define CHARSET_LENGTH 26
#define ALPHA 1/2

string alphabet = "abcdefghijklmnopqrstuvwxyz";

std::map<string,char> specialChars 
{
    {"á", 'a'},
    {"à", 'a'},
    {"ã", 'a'},
    {"é", 'e'},
    {"è", 'e'},
    {"ê", 'e'},
    {"í", 'i'},
    {"ì", 'i'},
    {"ó", 'o'},
    {"ò", 'o'},
    {"õ", 'o'},
    {"ô", 'o'},
    {"ú", 'u'},
    {"ù", 'u'},
    {"ç", 'c'}
};

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

std::map<char,double> getMapBufferDouble()
{
    std::map<char,double> result;

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

std::map<string,std::map<char,int>> trainModel(int k, const char* fname)
{
    std::map<string,std::map<char,int>> model;
    model = initBuffers(k);
    ifstream ifs(fname);
    char ch;
    string key = "";
    int hasKey = 0;

    while(ifs.get(ch))
    {
        
        // Convert character to lower case
        ch = tolower(ch);
        
        // Check for valid character
        if(alphabet.find(ch) == std::string::npos)
        {
            if(specialChars.find(string(1,ch)) == specialChars.end())
            {
                key = "";
                continue;
            }
            else
            {
                ch = specialChars[string(1,ch)];
            }
        }
        
        // Set key
        if(key.size() < k)
        {
            key.push_back(ch);
        }
        else
        {
            model[key][ch]++;
            key[0] = key[1];
            key[1] = ch;
        }
    }
    return model;
}

std::map<string,std::map<char,double>> computeBps(std::map<string,std::map<char,int>> model, double alpha)
{
    std::map<string,int> sums;
    std::map<string,std::map<char,double>> bps;
    
    for(const auto& element : model)
    {
        sums[element.first] = 0;
        for(const auto& value : element.second)
        {
            sums[element.first] += value.second;
        }
        //std::cout << element.first << " >> " << sums[element.first] << std::endl;
    }

    for(const auto& element: model)
    {
        bps[element.first] = getMapBufferDouble();
        for(const auto& value : element.second)
        {
            double prob = (value.second + alpha)/(sums[element.first] + 4*alpha);
            double encodeBits = -log2(prob);
            bps[element.first][value.first] = encodeBits;
        }
    }

    return bps;
}

double computeAverageBps(std::map<string,std::map<char,double>> model)
{
    int count = 0;
    double sum = 0;
    for(const auto& element : model)
    {
        for(const auto& value : element.second)
        {
            count++;
            sum += value.second;
        }
    }

    return sum/count;
}

int main(int argc, char** argv)
{
    // Set alpha
    double alpha = 0.1;
    // Init model map
    std::map<string,std::map<char,int>> model;
    std::map<string,std::map<char,double>> bps;
    // Get filename
    const char* fname = argv[1];
    // Train model
    model = trainModel(2, fname);
    // Compute bps
    bps = computeBps(model, alpha);
    // Compute average bps
    double averageBps = computeAverageBps(bps);
    // Print average bps
    std::cout << "[" << fname << "] BPS: " << averageBps << std::endl;
}
