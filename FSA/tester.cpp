#include <iostream>
#include <string>

#include "FSA.h"

using namespace std;

string response(string label);
void get_responses(FSA *fsa, vector<string> *labels, vector<string> *dest);

main() {
    vector<string> recognized;
    recognized.push_back("finite");
    recognized.push_back("state");
    recognized.push_back("automaton");

    FSA f1;
    f1.sep = 0;
    for (int i = 0; i < recognized.size(); ++i) {
        f1.update(recognized[i]);
    }
    //f1.show();

    vector<string> results;
    get_responses(&f1, &recognized, &results);
    for (int i = 0; i < results.size(); ++i) {
        cout << results[i] << endl;
    }
}

string get_response(FSA *fsa, string label) {
    string response = (fsa->accept(label)? "accepts" : "rejects");
    response += " " + label;
    return response;
}
void get_responses(FSA *fsa, vector<string> *labels, vector<string> *dest) {
    for (int i = 0; i < labels->size(); ++i) {
        dest->push_back(get_response(fsa, labels->at(i)));
    }
}


