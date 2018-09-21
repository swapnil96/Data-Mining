#include<iostream>
#include<vector>
#include<bits/stdc++.h>

using namespace std;

#define Point vector<float>
#define PDI pair<double,int>
#define PQ priority_queue<PDI,vector<PDI>,greater<PDI>>
#define Undef 0

class OPTICS{
    private:
    //Set of points
    vector<Point> Pts;

    //Dimension
    int Dim;

    //MinPts
    int MinPts;

    //N
    int N;

    //Eps
    double Eps;

    //T
    double T;

    //Reach Dist
    vector<double> ReachDist;

    //Processed
    vector<bool> Processed;

    //OrderedList
    vector<int> OrderedList;

    
    public:
    
    OPTICS(vector<Point> &pts,int minPts,double eps,double t){
        Pts = pts;
        MinPts = minPts;
        Eps = eps;
        T = t;
        Dim = Pts[0].size();
        N = Pts.size();
        ReachDist.resize(N,Undef);
        Processed.resize(N,false);   
    }

    double getCoreDist(vector<PDI> &N){
        return N[MinPts].first;
    }

    vector<PDI> getNeighbours(int ind){
        vector<PDI> neigh;
        for(int i=0;i<N;i++){
            double d = dist(ind,i);
            if(d<=Eps){
                neigh.push_back(make_pair(d,i));
            }
        }
        return neigh;
    }

    double dist(int i1,int i2){
        auto &pt1 = Pts[i1];
        auto &pt2 = Pts[i2];

        double dist=0;

        for(int i=0;i<Dim;i++)
            dist+= pow((pt1[i]-pt2[i]),2);

        return sqrt(dist);
    }
    

    void cluster() {
        for(int p=0;p<N;p++){
            if(Processed[p])
                continue;
            
            vector<PDI> Np = getNeighbours(p);
            Processed[p]=true;
            
            OrderedList.push_back(p);
            
            if(Np.size()<=MinPts)
                continue;
            
            sort(Np.begin(),Np.end());

            ReachDist[p] = getCoreDist(Np);
            set<PDI> seeds;

            update(p,Np,seeds);

            while(!seeds.empty()) {
                auto &qt = (*seeds.begin());
                seeds.erase(seeds.begin());
                int q = qt.second;
                vector<PDI> Nq = getNeighbours(q);
                Processed[q] = true;
                OrderedList.push_back(q);
                
                if(Nq.size()<=MinPts)
                    continue;
                
                sort(Nq.begin(),Nq.end());

                update(q,Nq,seeds);
            }            
        }

    }

    void update(int p, vector<PDI> &neigh, set<PDI> &seeds) {
        double coredist = getCoreDist(neigh);

        for(auto &qt:neigh){
            int q = qt.second;
            
            if(Processed[q])
                continue;
            
            double rdist = max(coredist,dist(p,q));

            if(ReachDist[q]==Undef){
                ReachDist[q] = rdist;
                seeds.insert(make_pair(rdist,q));
            } else {
                if(rdist<ReachDist[q]){
                    seeds.erase(make_pair(ReachDist[q],q));
                    ReachDist[q]=rdist;
                    seeds.insert(make_pair(rdist,q));
                }
            }
        }
    }

    void ReachDistPlot(){
        double undef = 0;
        for(int i=0;i<OrderedList.size();i++){
            undef = max(undef,ReachDist[OrderedList[i]]);
        }
        undef = 1.2*undef;
        for(int i=0;i<OrderedList.size();i++){
            if(ReachDist[OrderedList[i]]==Undef)
                cout<<undef<<endl;
            else
                cout<< ReachDist[OrderedList[i]] << endl;
        }

    }

    void ClusterPlot(){
        int cid=1;
        cout << "#0"<<endl;
        cout << OrderedList[0]<<endl;
        for(int i=1;i<OrderedList.size();i++){
            if(((ReachDist[i]-ReachDist[i-1])>0.01*T*ReachDist[i-1])
                && ((ReachDist[i]-ReachDist[i+1])>0.01*T*ReachDist[i+1])) {
                    cout << "#"<< cid<<endl;
                    cid++;

            }
            cout << OrderedList[i]<<endl;                    
        }
    }

};

int main(int argc,char* argv[]){
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int mpts= atoi(argv[1]);
    double eps= atof(argv[2]);
    string transactionFileName(argv[3]);
    double t=0;
    if(argc > 4)
        t= atof(argv[4]);

    string line;
    ifstream input(transactionFileName, ios::in);
    float number;

    vector<Point> Pts;
    
    if(input.is_open()) {
        while (getline(input, line)) {
            istringstream iss(line);
            vector<float> trans;
            while (iss >> number) {
                trans.push_back(number);
            }
            Pts.push_back(trans);
        }
    }
    
    OPTICS opt(Pts,mpts,eps,t);
    opt.cluster();
    if(argc <= 4)
        opt.ReachDistPlot();
    else
        opt.ClusterPlot();
}

