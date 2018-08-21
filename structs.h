#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <unordered_map>
#include <assert.h>
#include <algorithm>
#include <ostream>
#include <iterator>
#include <map>
#include <set>
#include <deque>

using namespace std;

struct Node{
    int item;
    int count;

    Node* parent;
    Node* next;
    map<int,struct Node*> children;

    Node():item(-1),count(0){

    };

    Node(int i,int c):item(i),count(c){
        next = nullptr;
        parent = nullptr;
    };

};


class FPTree{
    private:
    
    Node root;

    map<int,int,greater<int>> flist;

    set<int> ilist;

    map<int,Node*> headerTable;

    set<vector<int>> itemsets;

    public:
    //Constructor.
    FPTree();

    //Compare function to sort in flist order.
    bool comp(int i1,int i2);

    Node* getRoot();

    int getCount();

    //Add a transaction and modify the FPTree.
    void AddTrans(Node* root,deque<int> &trans,int k);

    //FPGrow function.Takes the filename to grow the fp tree rooted at root.
    void FPGrow(string filename);

    FPTree getConditionalTree(int item);

    void genItemSets(int minSup,set<int> &left,vector<int> &prior,set<vector<int>> &itemsets);


};