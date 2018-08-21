#include"structs.h"
#include <sstream>


void Process(vector<int> s){
    for(auto &c:s){
        cout<<c<<" ";
    }
    cout<<endl;
}



FPTree::FPTree(){
    root=Node();
    flist_done=false;
}




void FPTree::AddTrans(Node* root,deque<int> &trans,int k) {
    root->count+=k;
    auto i = trans.front();

    if(!flist_done){
        flist[i]+=k;
    }

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
    flist_done = true;
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
            sort(trans.begin(),trans.end(),(*this));
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

int FPTree::getCount(){
    return root.count;
}

void FPTree::genItemSets(int minSup,set<int> &left,vector<int> &prior){
    for(const auto &iter: flist) {
        if(left.find(iter.first)!=left.end()){
            left.erase(iter.first);
            
            if(flist[iter.first]<minSup){
                continue;
            }

            FPTree CondTree = getConditionalTree(iter.first);
                
            prior.push_back(iter.first);
            Process(prior);
            
            CondTree.genItemSets(minSup,left,prior);
            prior.pop_back();
        }
    }
}




