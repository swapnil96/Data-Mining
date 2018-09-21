#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <ctime>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ostream>
#include <iterator>
#include "kdtree.h"

using namespace std;
#define OUTLIER -2

class DBScan {

    private:
    /* Maximum radius of the neighborhood to be considered */
    float epsilon;

    /* Minimum number of points needed for a cluster */
    int minPts;

    /* Total number of points */
    int numData;

    /* Dimension of the data point */
    int dimension;

    /* Final total clusters */
    int C;

    /* Output file handle */
    ofstream output;

    /* Main data */
    vector<float*> points;

    /* Array to maintain which points are visited */
    vector<bool> visited;

    /* Neighbors of a point and different for expanding time, lastly merging into neighbors */
    vector<int> neighbors, currentNeighbors;

    /* The labels finally assigned */
    vector<int> assigned;
    unordered_map<int, unordered_set<int>> final_assign;

    /* Pointer of kdtree */
    kdtree *kd;

    public:
    /* Constructor to get the parameters and initialize the algorithm */
    DBScan(int pts, double eps, string inputFileName) {
        minPts = pts;
        epsilon = eps;

        bool firstInputData = false;

        string line;
        numData = 0;
    	ifstream input(inputFileName, ios::in);
        float number;
        if (input.is_open()) {
            while (getline(input, line)) {
                istringstream iss(line);
                float *x;

                if (!firstInputData) {
                    vector<float> y;
                    while (iss >> number)
                        y.push_back(number);

                    dimension = y.size();
                    kd = kd_create(dimension);
                    firstInputData = true;
                    x = new float[dimension];
                    for (int idx = 0; idx < dimension; idx++)
                        x[idx] = y[idx];
                }
                else {
                    x = new float[dimension];
                    int idx = 0;
                    while (iss >> number) {
                        x[idx] = number;
                        idx++;
                    }
                }   
                points.push_back(x);
                kd_insertf(kd, x, (void *)((long)numData));
                numData++;
            }
            input.close();
        }
        assigned.assign(numData, -1);
        visited.resize(numData);
    }

    double getEpsilon() {
        return epsilon;
    }

    int getMinPts() {
        return minPts;
    }

    void cluster() {    
        C = 0;
        for (int index = 0; index < numData; index++) {
            if (visited[index])
                continue;
            
            visited[index] = true;
            getNeighbors(index, 0);
            if (neighbors.size() < minPts) {
                assigned[index] = OUTLIER;
                final_assign[OUTLIER].insert(index);
            }
            else {
                expandCluster(index, C);
                C++;
            }
        }

        output.open("dbscan.txt", ios::out);
        for (int i = 0; i < C; i++) {
            output << "#" << i << endl;
            for (auto it: final_assign[i])
                output << it << endl;
        }
        if (final_assign.find(OUTLIER) != final_assign.end()) {
            output << "#outlier" << endl;
            for (auto it: final_assign[OUTLIER])
                output << it << endl;
        }
        output.close();
    }

    void getNeighbors(int idx, int flag) {
        vector<int> temp;

        int val;
        struct kdres *result_set = kd_nearest_rangef(kd, points[idx], epsilon);
        float* pos = new float[dimension];
        while (!kd_res_end(result_set)) {
            /* get the data and position of the current result item */
            void *f = kd_res_itemf(result_set, pos);
            val = (int)((long)f);
            temp.push_back(val);
            /* go to the next entry */
            kd_res_next(result_set);
        }
        if (flag == 0)
            neighbors = temp;
        else
            currentNeighbors = temp;

        kd_res_free(result_set);
    }

    void expandCluster(int idx, int C) {
        
        assigned[idx] = C;
        final_assign[C].insert(idx);

        int index = 0;
        while (index < neighbors.size()) {
            if (!visited[neighbors[index]]) {
                visited[neighbors[index]] = true;
                getNeighbors(neighbors[index], 1);
                if (currentNeighbors.size() >= minPts)
                    // merge();
                    neighbors.insert(neighbors.end(), currentNeighbors.begin(), currentNeighbors.end());        
            }
            if (assigned[neighbors[index]] == -1) {
                assigned[neighbors[index]] = C;
                final_assign[C].insert(neighbors[index]);
            }
            index++;
        }
    }

    void merge() {
        unordered_set<int> m(neighbors.begin(), neighbors.end());
        for (int i = 0; i < currentNeighbors.size(); i++)
            if (m.find(currentNeighbors[i]) == m.end()) {
                neighbors.push_back(currentNeighbors[i]);
                m.insert(currentNeighbors[i]);
            }
                
    }
};

int main(int argc, char** argv) {

    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int pts = atoi(argv[1]);
    double eps = atof(argv[2]);
    string inputFileName(argv[3]);

    DBScan dbscan(pts, eps, inputFileName);
    dbscan.cluster();
    return 0;
}
