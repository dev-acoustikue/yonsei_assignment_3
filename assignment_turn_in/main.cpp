#include <iostream>
#include <fstream>
#include <cstdlib>
#include <sstream>
#include "quicksort.h"

using namespace std;

int main (int argc, char *argv[]) {
    // Argument Count Validation
    if (argc != 3) {
        cerr << "Usage : " <<  argv[0] << " data_10.txt 5" <<endl;
        return 1;
    }

    // Argument 1 File Reading
    size_t len = 0;
    int * arr;
    ifstream is;
    is.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    string fname = argv[1];
    string suffix = ".txt";

    try {
        if (std::equal(fname.rbegin(), fname.rbegin() + suffix.size(), suffix.rbegin(), suffix.rend())){
            is.open(argv[1]);
            is.exceptions(0);
            int i;
            while ( is.good()) {
                is >> i;
                len ++;
            }
            len --;
            arr = new int[len];
            is.clear();
            is.seekg(0, ios::beg);
            for (int i =0 ; i < len ; i ++)
                is >> arr[i]; 
        } else { 
            is.open(argv[1], ios::binary);
            is.read(reinterpret_cast<char *>(&len), sizeof(size_t));
            arr = new int[len];
            is.read(reinterpret_cast<char *>(arr), len * sizeof(int));
        }
    } catch (...) {
        is.close();
        cerr << "Cannot read file " << argv[1] <<endl;
        return 4;
    }
    is.close();

    // Argument 2 Validation
    size_t k;
    if (argv[2][0] == '-') {
        cerr << "Wrong argument - Third argument should be positive." <<endl;
        return 2;
    }
    k = static_cast<size_t>(atoi(argv[2]));
    if (k > len) {
        cerr << "Wrong argument - Third argument is too big." <<endl;
        return 3;
    }

    //Process 
    int *tmp = new int[len];
    int kth;

    copy(arr,arr+len, tmp);
    kth = kthSmallestNaive(tmp,len,k);
    cout << "Naive solution : " << kth <<  endl;
    copy(arr,arr+len, tmp);
    kth = kthSmallest(tmp,len,k);
    cout << "Efficient solution : " << kth <<  endl;

    delete[] (arr);
    delete[] (tmp);

    return 0;
}
