
#include <iostream>
#include <unordered_map>
#include <SFML/Graphics.hpp>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <set>
using namespace std;


struct node{
    node *children[26] = {}; //pointer array set to the size of the alphabet
    bool end;
    int occurences;
    node() : end(false), occurences(0){
        for (auto & i : children){
            i = nullptr;
        }
    }
};

class trie{


    void destroy(node* current) {
        for (auto & i : current->children) {
            if (i) {
                destroy(i);
            }
        }
        delete current;
    }
public:
    node *root;
    vector<string> top = {"TYLA", "TYLA", "TYLA", "TYLA", "TYLA", "TYLA", "TYLA", "TYLA", "TYLA", "TYLA"}; //initializing our top 10 list
    int rank_count;

    trie() : root(new node()){}
    int total_names =0;
    void insert(const string &name){
        node *current = root;
        for (char i : name){
            int letter = i - 'A';
            if (current->children[letter] == nullptr){
                current->children[letter] = new node();
                total_names += 1;
            }

            current = current->children[letter];
        }
        current->end = true;

        current->occurences++;
    }
    int get_count(basic_string<char> name){
        node *current = root;
        for (char i : name){
            int letter = i - 'A';
            if (!current->children[letter]){
                return 0;
            }
            current = current->children[letter];
        }
        if (current && current->end){ //gets to a node marking a name
            return current->occurences;
        }
        else{
            return 0;
        }
    }
    ~trie() {
        destroy(root);
    }

    void rank_traversal(node* node, string word, int number) {
        if (node->end) {
            if (node ->occurences > number)
                rank_count +=1 ; //increments value
            //cout << node->occurences << endl;
        }

        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                char nextChar = 'a' + i;
                rank_traversal(node->children[i], word + nextChar, number);
            }
        }
    }

    int get_rank(node* node, string input){
        if (get_count(input) == 0) {

        }
        else {
            int count = get_count(input);
            rank_count = 1; //initializes count to 1
            rank_traversal(node, "", count); //traverses tree and adds each time a name is more popular
            return rank_count;

        }
    }


    void getTenHelper(node* root, node* node, string word){

        if (node -> end){
            for (int i=0; i < 10; i++){
                if (node->occurences >= get_count(top[i])){ ///if a name is more popular than one in the list
                    if ( i ==9){
                        top[9] = word;
                    }
                    else{
                        for (int j = 9; j > i; j--) {
                            top[j] = top[j - 1]; ///move all the subsequent names down the list
                        }
                        top[i] = word; ///insert this new super popular dog name
                    }
                    break; ///break so it is inserted one time
                }
            }
        }
        for (int i = 0; i < 26; ++i) {
            if (node->children[i] != nullptr) {
                char nextChar = 'A' + i;
                getTenHelper(root, node->children[i], word + nextChar);
            }
        }
    }


};