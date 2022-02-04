#include<iostream>
#include<fstream>
#include<map>
#include<math.h>
#include<string>
#include<cctype>
#include<filesystem>
#include<algorithm>
#include<vector>
#include<sstream>
#include"findlang.h"
#include"fcm.h"

using namespace std;

findlang::findlang() {};

findlang::findlang(int k, double a)
{
    order = k;
    alpha = a;
}

findlang::findlang(const char* langfname, int k, double a)
{
    langFile = langfname;
    order = k;
    alpha = a;
}

void findlang::loadLangFile(const char* fname)
{
    ifs.open(fname);
    std::string line, word;
    vector<string> row;

    while(std::getline(ifs,line))
    {
        row.clear();
        stringstream str(line);
        while(std::getline(str, word, ','))
        {
            row.push_back(word);
        }
        codeToLang[row[0]] = row[1];
        langMap[row[0]] = stof(row[2]);
    } 
}

void findlang::processFile(const char* code, const char* lang, const char* fname)
{
    fcm fcm(fname, order, alpha);
    fcm.extract();
    fcm.computeBps();
    fcm.computeAverageBps();
    langMap[code] = fcm.getAverageBps();
    codeToLang[code] = lang;
    findlang::writeToLangFile(code, lang, fcm.getAverageBps());
}

std::string findlang::findLang(const char* fname)
{
    fcm fcm(fname, order, alpha);
    fcm.extract();
    fcm.computeBps();
    fcm.computeAverageBps();
    double bps = fcm.getAverageBps();

    double avg = 99.0;
    std::string code;

    for(const auto& element : langMap)
    {
        if(abs(element.second - bps) < avg)
        {
            avg = abs(element.second - bps);
            code = element.first;
        }
    }

    return codeToLang[code];
}

void findlang::writeToLangFile(const char* code, const char* lang, double bps)
{
    ofs.open(langFile, std::ios_base::app);
    ofs << code << "," << lang << "," << bps << std::endl;
}

// int main(int argc, char** argv)
// {
//     const char* fname = argv[1];
//     const char* langfile = argv[2];
//     int k = atoi(argv[3]);
//     double a = atof(argv[4]);

//     findlang fl(langfile, k, a);
//     fl.processFile("en", "English", fname);
// }
