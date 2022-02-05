#include "fcm.h"

using namespace std;

int main(int argc, char ** argv) {

    const char* fname = argv[1];
    int k = atoi(argv[2]);
    double a = atof(argv[3]);
    fcm fcm(fname, k, a);

    fcm.extract();
    fcm.computeBps();
    fcm.computeAverageBps();

    // fcm.printModel();
    cout << "Average bps: " << fcm.getAverageBps() << endl;
}