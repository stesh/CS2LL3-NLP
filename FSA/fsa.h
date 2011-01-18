if !defined(FSA_h)
#define FSA_h


#include "Node.h"

//! A Finite State Automaton
class FSA {
    public:
        FSA(void);       //!< makes empty FSA to then add to with update
        char sep;        //!< what character to split input at

        /******************/
        /* ACCEPT METHODS */
        /******************/


        /* turns input into a vector key using sep as separator */
        int accept(string input);   //!< test if input is accepted 

        /******************/
        /* UPDATE METHODS */
        /******************/

        void update(string input); //!< add to FSA to make input be accepted

        /******************/
        /* SHOW METHODS   */
        /******************/

        void show(void);
        void dot_show(void); 
        void add_these_sequences(char *file);

    private:
        vector<NodePtr> initial_states; 
        vector<string> key;
        void set_key_from_string(string in); //!< set key by spliting string at the sep character

        int accept(void);   //!< checks if key is accepted
};

#endif



