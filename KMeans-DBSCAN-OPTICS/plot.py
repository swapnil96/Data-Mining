import matplotlib.pyplot as plt
import sys
import numpy as np


def plotReach(fname):
    l = []
    with open(fname,'r') as f:
        for line in f:
            line = line.replace("\n", "")
            l.append(float(line))
    plt.plot(l)
    plt.show()

def plotCluster(clusterfile,pointsfile):
    xpts = []
    ypts = []
    size=0
    with open(pointsfile,'r') as f:
        for line in f:
            x, y = map(float, line.split())
            xpts.append(x)
            ypts.append(y)
            size+=1
    clu  = [-1 for i in range(size)]
    with open(clusterfile,'r') as f:
        cid = -1
        for line in f:
            if(line[0]=='#'):
                # print (line[1:])
                if(line[1:] == "outlier\n"):
                    cid+=1
                else:
                    cid=int(line[1:])
            else :
                ind = int(line)
                clu[ind] = cid
    x = np.array(xpts)
    y = np.array(ypts)
    Cluster = np.array(clu)
    # print(clu)
    scatter = plt.scatter(x,y,c=Cluster,s=0.7)
    plt.colorbar(scatter)
    plt.show()

    

    
            


numargument = len(sys.argv)
if numargument==1:
    plotReach(sys.argv[1])
else: 
    plotCluster(sys.argv[1],sys.argv[2])