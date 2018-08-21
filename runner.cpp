#include "structs.h"

using namespace std;

void GenAllItemSets(string filename,int minSup){
    FPTree tree=FPTree();

    tree.FPGrow(filename);

    vector<int> prior;

    tree.genItemSets(minSup,tree.ilist,prior);


}


int main(int argc, char** argv) {
    string transactionFileName(argv[1]);
    double minimumSupport = atof(argv[2]);
    GenAllItemSets(transactionFileName,minimumSupport);
    return 0;
}