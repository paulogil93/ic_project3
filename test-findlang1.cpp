#include "findlang.h"

using namespace std;

int main(int argc, char** argv) {

    const char* fname = argv[1];
    const char* langfile = argv[2];
    const char* code = argv[3];
    const char* lang = argv[4];
    int k = atoi(argv[5]);
    double a = atof(argv[6]);


    findlang fl(langfile, k, a);
    fl.processFile(code, lang, fname);

}