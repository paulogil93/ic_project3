#include<iostream>
#include<fstream>
#include<map>
#include"fcm.h"

class lang
{
    private:
        std::ifstream ri;
        std::ifstream t;
        fcm f;
        double N;
        int order;
        double alpha;
    public:
        lang();
        lang(const char* rifname, const char* tfname, int k, double a);
        int openri(const char* fname);
        int opent(const char* fname);
        void initFcm(const char* fname, int k, double a);
        std::map<std::string,std::map<char,double>> getFcm();
        void estimate();
        double getN();
};
