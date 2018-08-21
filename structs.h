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
#include <queue>

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


    map<int,int> flist;

    
    map<int,Node*> headerTable;

    bool flist_done;

    public:

    void printTree();

    bool operator()( const int & i1, const int & i2  )
    { 
        if(flist[i1]!=flist[i2]){
            return flist[i1]<flist[i2];
        }
        return i1<i2;
    }

    set<int> ilist;

    //Constructor.
    FPTree();

    
    Node* getRoot();

    int getCount();

    //Add a transaction and modify the FPTree.
    void AddTrans(Node* root,vector<int> &trans,int k);

    //FPGrow function.Takes the filename to grow the fp tree rooted at root.
    void FPGrow(string filename,int minSup);

    FPTree getConditionalTree(int item);

    void genItemSets(int minSup,vector<int> &prior);


};