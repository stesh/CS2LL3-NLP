#include <fstream>
#include <stdlib.h>

#include "fsa.h"

FSA::FSA() {
    NodePtr n = 0;
    n = new Node;
    n->initial = 1;
    initial_states.push_back(n);
}

void FSA::show() {
    for(int i = 0; i < initial_states.size(); i++) {
        initial_states[i]->show();
    }
}

void FSA::dot_show() {
    ofstream f;

    string personal_fsa(getenv("LOGNAME"));
    personal_fsa = "/tmp/" + personal_fsa + "_fsa";

    string dot_file;
    dot_file = personal_fsa + ".dot";
    f.open(dot_file.c_str());

    f << "digraph G {\n";
    f << "center=true;";
    for(int i = 0; i < initial_states.size(); i++) {
        initial_states[i]->show(f);
    }
    f << "};";
    f.close();

    string dot_command;
    dot_command = "dot -Tps " + dot_file + " -o " + personal_fsa + ".ps";

    system(dot_command.c_str());
    string ghost_command;

    ghost_command = "gv " + personal_fsa + ".ps";
    system(ghost_command.c_str());
}

int FSA::accept(string input) {
    set_key_from_string(input);
    return accept();
}

int FSA::accept() {

    int k, accept = 0;

    NodePtr n1 = 0, n2 = 0;

    for(int count = 0; count < initial_states.size(); count++) {
        n1 = initial_states[count];
        for (k = 0; k < key.size(); k++) {
            if ((n2 = n1->match(key[k])) != NULL) {
                n1 = n2;
            }
            else {
                break;
            }
        }

        if (k == key.size() && n1->accept == 1) {
            accept = 1;
            break;
        }

    }
    return accept;
}

/*! sets key from input 
 *  if not already accepted adds nodes to allow it to be accepted
 */
void FSA::update(string input) {
    set_key_from_string(input);

    int k = 0, matching = 1;
    NodePtr n1, n2;

    if (accept()) {
        return;
    }

    for (int i = 0; i < initial_states.size(); ++i) {
        n1 = initial_states[i];
        for (k = 0; k < key.size(); ++k) {
            if ((n1->match(key[k])) == NULL) {
                n1 = n1->update(key[k]);
            } else {
                n2 = n1->match(key[k]);
                n1 = n2;
            }
        }

        n1->accept = 1;
    }
} 


/* splits input up setting the vector key to contain the pieces
 * the value of sep determines where to split
 * if sep is 0 then each letter is a separate element
 * if sep is ' ' then splits on white space
 */
void FSA::set_key_from_string(string input) {

    int start = 0, finish;
    int ends_on_sep = 0;
    key.clear();
    if (sep != 0) {
        while((finish = input.find(sep,start)) != string::npos) {
            key.push_back(input.substr(start,finish-start));
            if(finish == input.length()-1) {
                ends_on_sep = 1;
                break;
            }
            else {
                finish++;
                start = finish;
            }
        }

        if (ends_on_sep == 1) {}
        else {
            key.push_back(input.substr(start));
        }
    }

    else {
        for (start = 0; start < input.length(); start++) {
            key.push_back(input.substr(start,1));
        }
    }

}

/*! Updates the FSA with the sequences 
 *  contained in the specified file.
 *  This assumes that the sequences to
 *  be added appear one-per-line
 */
void FSA::add_these_sequences(char *file) {
    ifstream input_filestream(file);
    string curline;
    while (!input_filestream.eof()) {
        getline(input_filestream, curline);
        update(curline);
    }
}
