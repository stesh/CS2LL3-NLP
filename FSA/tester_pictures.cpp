#include <iostream>
#include <fstream>
#include <string>

#include "FSA.h"

using namespace std;

main() {

    FSA f1;
    f1.sep = 0;
    ifstream dict("words.txt");
    string current_word;

    while (dict >> current_word) {
        f1.update(current_word);
    }

    f1.dot_show();
}
