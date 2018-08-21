#include"structs.h"
#include <sstream>


bool debug = false;

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


void FPTree::printTree(){
    queue<Node> q;
    q.push(root);
    while (!q.empty()) {
        auto top = q.front();
        q.pop();
        if (top.item == -2) {
            cout << endl;
            continue;
        }
        else if (top.item == -1)
            cout << top.item << ":" << top.count << endl;
        else
            cout << top.item << ":" << top.count << "\t";
        for (auto it: top.children) {
            q.push(*it.second);
        }
        Node temp = Node();
        temp.item = -2;
        q.push(temp);
    }
}




void FPTree::AddTrans(Node* root,vector<int> &trans,int k) {
    root->count+=k;
    if(trans.empty())
        return;
    auto i = trans.back();

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


    trans.pop_back();
    AddTrans(root->children[i],trans,k);
    
}

void FPTree::FPGrow(string filename,int minSup){
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

    

    ifstream input2(filename, ios::in);
    
    
    if(input2.is_open()) {
        while (getline(input2, line)) {
            istringstream iss(line);
            vector<int> trans;
            while (iss >> number) {
                if(flist[number]>=minSup)
                    trans.push_back(number);
            }
            if(trans.empty())
                continue;
            sort(trans.begin(),trans.end(),(*this));
            if(debug){
                cout<<"trans"<<endl;
                for(auto&t:trans)
                    cout<<t<<" ";
                cout<<endl;
            }
            //AddTrans(&root,trans,1);
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
        vector<int> branch;
        Node* headptr = nextptr;
        int k=nextptr->count;
        headptr=headptr->parent;
        while(headptr->item!=-1){
            branch.push_back(headptr->item);
            headptr=headptr->parent;            
        }
        if(debug){
            cout<<"Brach\n";
            for(auto&b:branch)
                cout<<b<<" ";
            cout<<endl;
        }
        CondTree.AddTrans(CondTree.getRoot(),branch,k);
        nextptr=nextptr->next;
    }

    return CondTree;
}

int FPTree::getCount(){
    return root.count;
}

void FPTree::genItemSets(int minSup,vector<int> &prior){
    set<int> proccesed;
    for(const auto &iter: flist) {
        if(proccesed.find(iter.first)==proccesed.end()){
            
            if(flist[iter.first]<minSup){
                continue;
            }

            

            FPTree CondTree = getConditionalTree(iter.first);

            if(debug)
                cout<<iter.first<<":"<<CondTree.getCount()<<endl;
                
            prior.push_back(iter.first);
            Process(prior);
            
            CondTree.genItemSets(minSup,prior);
            prior.pop_back();
        }
        proccesed.insert(iter.first);
        
    }
}




