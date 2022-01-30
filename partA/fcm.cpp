#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <algorithm>
using namespace cv;
using namespace std;
#define HISTO_WINDOWSIZE_X 1000
#define HISTO_WINDOWSIZE_Y 700
// template <class T>
// void func(T x){
//     cout << "size = " << sizeof(x) << "  " << x << endl;
// }

map<char,int>::iterator it;

int max(map<char,int> histo) {
  int max = 0;
  for (it = histo.begin(); it != histo.end(); it++) {
    if (it->second > max) max = it->second;
  }
  return max;
}

double histoToEntropy(map<char,int> histo, int total) {
  double entropy;
  for (it = histo.begin(); it != histo.end(); it++) {
    double prob = (double)(it->second) / (double)(total);
    entropy -= prob*log2(prob);
  }
  return entropy;
}

Mat imageHisto(map<char,int> histo, double entropy, int total) {
  int divider = max(histo);
  int bar_size = HISTO_WINDOWSIZE_X / 52;
  Mat histogram_image(HISTO_WINDOWSIZE_Y, HISTO_WINDOWSIZE_X, CV_8UC3, Scalar(0,0,0));
  int x = 0;
  for (it = histo.begin(); it != histo.end(); it++) {
    string letter = "";
    char l = it->first;
    letter += l;
    rectangle(histogram_image,
      Point(x, HISTO_WINDOWSIZE_Y-50-(it->second*(HISTO_WINDOWSIZE_Y-100)/divider)),
      Point(x+bar_size, HISTO_WINDOWSIZE_Y-50),
      Scalar(255,255,255));
    putText(histogram_image, letter, Point(x+bar_size/2-3,HISTO_WINDOWSIZE_Y-20), FONT_HERSHEY_COMPLEX_SMALL, 0.6, Scalar(255,255,255));
    x += bar_size;
  }
  putText(histogram_image, "Entropy = "+to_string(entropy), Point(HISTO_WINDOWSIZE_X/8,200), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(255,255,255));
  putText(histogram_image, "Total letters = "+to_string(total), Point(HISTO_WINDOWSIZE_X/8,220), FONT_HERSHEY_COMPLEX_SMALL, 0.5, Scalar(255,255,255));
  return histogram_image;
}

int main(int argc, char** argv){
    char characters[69] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
                           'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
                           'O','1','2','3','4','5','6','7','8','9',',','.','!','?',';','-',' '};
    // cout << "-----------------------------" << endl;
    // string fileIn = argc>2 ? "lusiadas.txt" : argv[1];
    // string histoFile = argc>3 ? "histogram" : argv[2];
    string fileIn = "lusiadas.txt";
    string histoFile = "histogram";
    int size = argc>4 ? 1 : atoi(argv[3]);
    int alfa = argc>5 ? 1 : atoi(argv[4]);
    map<string, map<char,long>> histo;
    map<string, map<char,long>>::iterator it;
    map<char,long>::iterator iti;
    ifstream ifs("../Texts/"+fileIn);
    ofstream ofs("../Histograms/"+histoFile+".txt");
    string line;
    char buffer[size];
    int count = 0;
    int bufferSize = 0;
    while (getline(ifs,line,'\0')) {
        for (char x : line) {
          if (find(begin(characters),end(characters),x) != end(characters)) {
            // if buffer not full
            if (bufferSize < size) {
              buffer[bufferSize] = x;
              bufferSize++;
            }
            else {
              bool exists = false;
              for (it = histo.begin(); it != histo.end(); it++) {
                if (it->first == buffer) {
                  for (iti = it->second.begin(); iti != it->second.end(); iti++) {
                    if (iti->first == x) {
                      exists = true;
                    }
                  }
                }
              }
              if (it == histo.end()) histo[buffer][x] = 0;
              histo[buffer][x]++;
              // update buffer
              for (int i = 0; i < bufferSize-1; i++) {
                buffer[i] = buffer[i+1];
              }
              buffer[bufferSize-1] = x;
              cout << buffer;
              count++;
            }
        }
      }
    }
    for (it = histo.begin(); it != histo.end(); it++) {
      for (iti = it->second.begin(); iti != it->second.end(); iti++) {
        cout << it->first << " : " << iti->first << " : " << iti->second << endl;
        ofs << it->first << " : " << iti->first << " : " << iti->second << endl;
      }
    }
    // double entropy = histoToEntropy(histo,count);
    // Mat histo_image = imageHisto(histo,entropy,count);
    // string path = "../histogram.jpg";
    // namedWindow(path, WINDOW_AUTOSIZE);
    // imshow(path,histo_image);
    // imwrite(path,histo_image);
    // waitKey(0);

    return 0;  
}
