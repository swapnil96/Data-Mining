#include"structs.h"
#include <sstream>


FPTree::FPTree(){
    root=Node();

}


bool FPTree::comp(int i1,int i2){
    if(flist[i1]!=flist[i2]){
        return flist[i1]<flist[i2];
    }
    return i1<i2;
}


void FPTree::AddTrans(Node* root,deque<int> &trans,int k) {
    root->count+=k;
    auto i = trans.front();

    if(root->children.find(i)==root->children.end()){
        root->children[i] = new Node(i,0);     
        root->children[i]->parent = root;
        if(headerTable[i]==nullptr){
            headerTable[i]=root->children[i];
        } else {
            Node* hptr = headerTable[i];
            while(hptr->next!=nullptr)
                hptr = hptr->next;
            hptr->next=root->children[i];
        }
        
    }


    trans.pop_front();
    AddTrans(root->children[i],trans,k);
    
}

void FPTree::FPGrow(string filename){
    string line;

    ifstream input(filename, ios::in);
    int number;

    //Init the flist and ilist.
    if (input.is_open()) {
        while (getline(input, line)) {
            istringstream iss(line);
            while (iss >> number) {
                flist[number]++;
                ilist.insert(number);
            }
        }
        input.close();
    }

    input.clear();
    input.seekg(0, ios::beg);

    if(input.is_open()) {
        while (getline(input, line)) {
            istringstream iss(line);
            deque<int> trans;
            trans.assign(istream_iterator<int>( iss ), istream_iterator<int>());
            sort(trans.begin(),trans.end(),comp);
            AddTrans(&root,trans,1);
        }
    }
}

Node* FPTree::getRoot(){
    return &root;
}

FPTree FPTree::getConditionalTree(int item){
    FPTree CondTree = FPTree();

    Node* nextptr = headerTable[item];

    while(nextptr!=nullptr){
        deque<int> branch;
        Node* headptr = nextptr;
        int k=nextptr->count;
        while(headptr->item!=-1){
            branch.push_front(headptr->item);
            headptr=headptr->parent;            
        }
        CondTree.AddTrans(CondTree.getRoot(),branch,k);
    }

    return CondTree;
}


void FPTree::genItemSets(){
    
}


