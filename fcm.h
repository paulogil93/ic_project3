#include<iostream>
#include<fstream>
#include<map>

class fcm
{
    private:
        std::string alphabet = "abcdefghijklmnopqrstuvwxyz0123456789.,;-!? ";
        std::map<std::string,std::map<char,int>> model;
        std::map<std::string,std::map<char,double>> bps;
        double abps;
        int order;
        double alpha;
        std::ifstream ifs;
        void generateAllKLengthSubstringsRec(std::string alphabet, std::string prefix, int size, int k);
        void initContextBuffer();
        std::map<char,int> initInputBuffer();
        std::map<char,double> initDoubleInputBuffer();
    public:
        fcm();
        fcm(const char* fname, int k, double a);
        int open(const char* fname);
        void printModel();
        void extract();
        void computeBps();
        void computeAverageBps();
        // Basic getters and setters
        void setOrder(int k);
        void setAlpha(double alpha);
        void setAlphabet(std::string s);
        int getOrder();
        double getAlpha();
        std::string getAlphabet();
        std::map<std::string,std::map<char,double>> getBps();
        double getAverageBps();      
};
