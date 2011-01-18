#if !defined(node_h)
#define node_h
#include <string>
#include <vector>
#include <iostream>

using namespace std;


class Node;  // forward declaratoin

//! NodePtr used as typedef in Node
typedef Node * NodePtr;

//! a helper class for Node representing a single arc out of a node
class mypair {
    public:
        string label;
        NodePtr next;
};


//! represents a state in an FSA
class Node{
    public:
        Node(void);

        int out_arc_count(){return arcs.size();}
        NodePtr update(string label);   //!< makes new node target for given label 
        NodePtr match(string label);    //!< returns node target for given label 
        int accept;  //!< is this an accept node 
        int initial; //!< is this an initial node
        void show(void); //!< show this node and recursive descendents
        void show(ostream&); 
        string identifier; //!< used for debugging 
        void show_language();
        void show_language(string delim);
        void show_language(char delim);

    private:
        vector<mypair> arcs; //!< the arcs going out of a node
        static int node_count; //!< used for debugging
};


#endif

