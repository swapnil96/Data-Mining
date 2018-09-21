import numpy as np
import random as random
import sys
import math
def createDict(k):
	clusters={}
	for i in range(k):
		clusters[i]=[]
	return clusters


def initialCentroid(k,data):
	sam=random.sample(range(0, len(data)-1), k)
	centroids=[]
	for i in range(k):
		centroids.append(data[sam[i]])
	return centroids


def distance(a,b):
	dist=0
	for i in range(len(a)):
		dist=dist+math.pow(a[i]-b[i],2)
	return dist

def findCentroids(clusters,data):
	centroids=[]
	for i in clusters:
		mean=np.array(data).mean(axis=0)
		c=data[0]
		dist=sys.maxint
		for d in clusters[i]:
			temp=distance(data[d],mean)
			if(temp<dist):
				dist=temp
				c=data[d]
		centroids.append(c)
	return centroids

def createClusters(k,centroids,data):
	clusters=createDict(k)
	for j in range(len(data)):
		index=0
		dist=sys.maxint
		for i,centroid in enumerate(centroids):
			temp=distance(data[j],centroid)
			if(temp<dist):
				dist=temp
				index=i
		clusters[index].append(j)
	return clusters

k=int(sys.argv[1])

fp=open(str(sys.argv[2]))
data=[]
for line in fp.readlines():
	point=[]
	for val in line.split():
		point.append(float(val))
	data.append(point)

centroids=initialCentroid(k,data)
clusters=createClusters(k,centroids,data)
newCentroids=findCentroids(clusters,data)
while(sorted(centroids)!=sorted(newCentroids)):
	centroids=newCentroids
	clusters=createClusters(k,newCentroids,data)
	newCentroids=findCentroids(clusters,data)


f =open("kmeans.txt","w")
l=len(data[0])
for i in range(k):
	f.write("#"+str(i)+"\n")
	for j in clusters[i]:
		f.write(str(j)+"\n")

f.close()