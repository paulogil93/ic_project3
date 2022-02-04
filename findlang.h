#include<iostream>
#include<fstream>
#include<map>

using namespace std;

class findlang
{
    private:
        map<string,double> langMap;
        map<string,string> codeToLang;
        string folderName;
        string langFile;
        std::ifstream tfs;
        std::ifstream ifs;
        std::ofstream ofs;
        int order;
        double alpha;
    public:
        findlang();
        findlang(int k, double a);
        findlang(const char* langFile, int k, double a);
        void loadLangFile(const char* langFile);
        void processFile(const char* code, const char* lang, const char* fname);
        std::string findLang(const char* fname);
        void writeToLangFile(const char* code, const char* lang, double bps);
};
