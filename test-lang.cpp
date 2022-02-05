#include "lang.h"

using namespace std;

int main(int argc, char** argv) {

    const char* rifname = argv[1];
    const char* tfname = argv[2];
    int k = atoi(argv[3]);
    double a = atof(argv[4]);
    
    lang lang(rifname, tfname, k, a);
    lang.estimate();

    cout << (long) lang.getN() << " bits" << endl;

}