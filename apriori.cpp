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

using namespace std;

class Apriori {
    private:
    /* List of itemsets */
    vector<vector<int>> itemsets;
    /* Name of the output file */
    string transactionFileName;
    /* Number of different items in the dataset */
    int numItems;
    /* Number of transactions in transaction file */
    int numTransactions;
    /* Minimum support for a itemset to be frequent */
    double minimumSupport;

    public:
    /* Constructor to get the parameters and initialize the algorithm */
    Apriori(string fileName, double support) {
        transactionFileName = fileName;
        minimumSupport = support/100.0;

        string line;
        numItems = 0;
    	numTransactions=0;
        ifstream input(transactionFileName, ios::in);
        int number;

        if (input.is_open()) {
            while (getline(input, line)) {
                numTransactions++;
                istringstream iss(line);
                while (iss >> number) {
                    if (number+1 > numItems)
                        numItems = number+1;
                }
            }
            input.close();
        }
        cout << "Number of items: " << numItems << ", Number of transactions: " << numTransactions << endl;
    }

    void start() {
        clock_t begin = clock();

        // Generate candidates of size 1
        createCandidatesOfSizeOne();
        int itemsetSize = 1; // Current size of itemset 
        int totalFrequentSets = 0;
        while (itemsets.size() > 0) {
            createFrequentSetsFromCandidateSets();
            if (itemsets.size() != 0) {
                totalFrequentSets += itemsets.size();
                createCandidateSetsFromFrequentSets();
            }
            itemsetSize++;
        }
        clock_t end = clock();
        double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
        cout << "Execution time is: " << elapsed_secs << endl;
    }

    void createCandidatesOfSizeOne() {
        for (int i = 0; i < numItems; i++) {
            vector<int> temp{i};
            itemsets.push_back(temp);
        }
    }

    void createFrequentSetsFromCandidateSets() {
        
        vector<vector<int>> frequentItemsets;

        bool isFrequent;
        vector<int> counts(itemsets.size(), 0);

        string line;
        ifstream input(transactionFileName, ios::in);
        vector<bool> masks(numItems, false);
        int number;

        for (int i = 0; i < numTransactions; i++) {
            getline(input, line);
            istringstream iss(line);
            while (iss >> number)
                masks[number] = true;

            for (int j = 0; j < itemsets.size(); j++) {
                isFrequent = true;
                for (int item: itemsets[j])
                    if (masks[item] == false) {
                        isFrequent = false;
                        break;
                    }

                if (isFrequent)
                    counts[j]++;
            }
            istringstream iss_rev(line);
            while (iss_rev >> number)
                masks[number] = false;
        }
        input.close();

        for (int i = 0; i < itemsets.size(); i++)
			if ((counts[i]/(double)numTransactions) >= minimumSupport)
				frequentItemsets.push_back(itemsets[i]);

        itemsets = frequentItemsets;
        cout << "Done finding frequent sets: " << itemsets.size() << endl;
    }

    void createCandidateSetsFromFrequentSets() {
        int itemsetSize = itemsets[0].size();
        unordered_map<string, vector<int>> hash_map;
        int size = itemsets.size();
        for (int i = 0; i < size; i++) {
            for (int j = i+1; j < size; j++) {
                vector<int> f1 = itemsets[i];
                vector<int> f2 = itemsets[j];
                assert(f1.size() == f2.size());

                /* New itemset to be made with n-1 elements same
                nth element from f1 and n+1th element from f2
                */
                vector<int> newItemSet(f1);
                newItemSet.push_back(0);

                // Number of different items in 2 itemsets
                int different = 0;
                for (int k = 0; k < f2.size(); k++) {
                    bool found = false;
                    for (int l = 0; l < f1.size(); l++) {
                        if (f1[l] == f2[k]) {
                            found = true;
                            break;
                        }
                    }
                    if (!found) {
                        different++;
                        newItemSet[f1.size()] = f2[k];
                    }
                }
                assert(different > 0);

                // TODO Pruning

                if (different == 1) {
                    sort(newItemSet.begin(), newItemSet.end());
                    stringstream result;
                    copy(newItemSet.begin(), newItemSet.end(), ostream_iterator<int>(result, " "));
                    hash_map[result.str().c_str()] = newItemSet;
                }
            }
        }
        vector<vector<int>> temp;
        for (auto it: hash_map)
            temp.push_back(it.second);
    
        itemsets = temp;
        cout << "Done making new itemsets: " << itemsets.size() << endl;
    }
};


int main(int argc, char** argv) {
    string transactionFileName(argv[1]);
    double minimumSupport = atof(argv[2]);
    Apriori apriori(transactionFileName, minimumSupport); 
    apriori.start();
    return 0;
}