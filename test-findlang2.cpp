#include "findlang.h"

using namespace std;

int main(int argc, char** argv) {

    const char* fname = argv[1];
    const char* langfile = argv[2];
    int k = atoi(argv[3]);
    double a = atof(argv[4]);

    findlang fl(k, a);
    fl.loadLangFile(langfile);
    cout << "Idioma: " << fl.findLang(fname) << endl;

}