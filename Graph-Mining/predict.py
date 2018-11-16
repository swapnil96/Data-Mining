
# coding: utf-8

# In[ ]:

import sys
import networkx.algorithms.isomorphism as iso
import networkx as nx
import numpy as np
import time


# In[323]:



# In[324]:


def read_frequent(filepointer):
    freq=[]
    glist=[]
    for line in filepointer.readlines():
        data=line.split()
        if data:
            if (data[0]=='#'):
                continue
            elif (data[0]=='t'):
                g=nx.Graph()
                glist.append(g)
            elif (data[0]=='v'):
                g.add_node(data[1],elem=data[2])
            elif (data[0]=='e'):
                g.add_edge(data[1],data[2],weight=int(data[3]))
            # elif (data[0]=='e'):
            #     g.add_edge(data[1],data[2],weight=int(data[3]))
            elif (data[0]=='x'):
                freq.append(data[1:])
    return glist,freq


def read_graph(filepointer):
    molid=[]
    glist=[]
    # alist=[]
    for line in filepointer.readlines():
        data=line.split()
        if data:
            if (data[0]=='#'):
                continue
            elif (data[0]=='t'):
                g=nx.Graph()
                glist.append(g)
                molid.append(int(data[2]))
            elif (data[0]=='v'):
                g.add_node(data[1],elem=data[2])
            elif (data[0]=='e'):
                g.add_edge(data[1],data[2],weight=int(data[3]))
        # elif (data[0]=='e'):
        #     g.add_edge(data[1],data[2],weight=int(data[3]))
    return glist,molid
# In[325]:


def create_fvl(glist,flist):
    fva=np.zeros((len(glist),len(flist)))
    i=0
    nm=iso.categorical_node_match('elem','C')
    em=iso.numerical_edge_match('weight',1)
            
    for mol in glist:
        # print(i)
        j=0
        for feature in flist:
            GM = iso.GraphMatcher(mol,feature,node_match=nm,edge_match=em)
            if GM.subgraph_is_isomorphic():
                fva[i][j]=1
            j+=1
        i+=1
    return fva

def uniquelist(l1,l2,fva):
    l=[]
    temp=[]
    # li=[]
    nm=iso.categorical_node_match('elem','C')
    em=iso.numerical_edge_match('weight',1)
      
    for i,k in zip(l1,fva):
        flag=1
        # c=0
        for j in l2:
            # c+=1
#             GM = nx.algorithms.isomorphism.GraphMatcher(i,j)
            if iso.is_isomorphic(i,j,edge_match=em,node_match=nm):
#                 print "1"
                flag=0
                # li.append(c)
                break
        if flag==1:
            l.append(i)
            temp.append(k)
    # print len(l)
    # print len(li)
    # print li
    # c=0
    # for i in range(0,len(l2)):
#         c=0
        # if i+1 not in li:
            # l.append(l2[c])
            # print "hola"
        # else:
            # c+=1
    return l,temp 

def print_fv(l,i,filep):
    filep.write(str(i))
    ite=0
    for k in l:
        filep.write(" "+str(ite)+":"+str(int(k)))
        ite+=1
    filep.write("\n")
    
def printfv(l,filep):
#     fp.write("str(i)")
    ite=0
    for k in l:
        if(ite!=0):
            filep.write(" ")
        filep.write(str(ite)+":"+str(int(k)))
        ite+=1
    filep.write("\n")


# In[326]:



filefa=open("ga.fp",'r+')
# filefi=open("gi.fp",'r+')

filegspan=open("datafile.fp",'r+')
filetest=open("testfile",'r+')

filea=open("ga")
filei=open("gi")
file=open("datafile")
fca=open(sys.argv[1])
fci=open(sys.argv[2])
writea=open("train.txt",'w+')
writeb=open("test.txt",'w+')

x={}
# In[30]:
for line in fca.readlines():
    x[int(line)]=1
# for line in fi.readlines():
#     x[int(line)]=-1



freqa,fva=read_frequent(filefa)
freqgspan,fvgspan=read_frequent(filegspan)
fre_a,fvlista=uniquelist(freqa,freqgspan,fva)
if(len(fre_a)>25):
    fre_a=fre_a[:23]
    fvlista=fvlista[:23]


# fvlist=np.ones((len()))
# read_graph(freqa,fr_a)
# read_graph(freqi,fr_i)
# print (len(freqgspan))
# print (len(freqa))
# print (len(fre_a))
# In[330]:


# In[331]:


# mola=[]
# moli=[]
# read_graph(filegspan,mola)
# read_graph(f2i,moli)
molecules,molid=read_graph(file)
testmol,m2id=read_graph(filetest)


# In[332]:


# print (len(molecules))
# print len(moli)


# print fvgspan
features=np.ones((len(molecules),len(freqgspan)+len(fre_a)))*-1
# print (np.shape(features))
for i in range(0,len(fvgspan)):
    for k in fvgspan[i]:
        features[int(k)][i]=1


s=len(fvgspan)


c=0
ca=0
ct=0
# mid=0
nm=iso.categorical_node_match('elem','C')
em=iso.numerical_edge_match('weight',1)
alist=[]
for mol,mid in zip(molecules,molid):
    # print (mid)
    if mid in x:
        alist.append(1)
        for i in range(s,s+len(fvlista)):
            for k in fvlista[i-s]:
                features[int(k)][i]=1

        # features[c][fvlista[ca]]=1
        # ca+=1
    else:
        alist.append(-1)
        j=s
        for f in fre_a:
            GM = iso.GraphMatcher(mol,f,node_match=nm,edge_match=em)
            if GM.subgraph_is_isomorphic():
                features[c][j]=1
            j+=1
    
    c+=1

for f,a in zip(features,alist):
    print_fv(f,a,writea)

testfeature=np.ones((len(testmol),len(freqgspan)+len(fre_a)))*-1
c=0
# print(len(freqgspan), len(fre_a))
for mol in testmol:
    j=0
    for f in freqgspan:
        # print ("dsf")
        GM = iso.GraphMatcher(mol,f,node_match=nm,edge_match=em)
            # print("fdfd")
        if GM.subgraph_is_isomorphic():
            print ("dfdsf")
            testfeature[c][j] = 1

        j+=1
    for f in fre_a:
        GM = iso.GraphMatcher(mol,f,node_match=nm,edge_match=em)
        if GM.subgraph_is_isomorphic():
            testfeature[c][j]=1
            print ("dfdsf")
        j += 1
    c+=1

for f in testfeature:
    printfv(f,writeb)


# i=0
#     nm=iso.categorical_node_match('elem','C')
#     em=iso.numerical_edge_match('weight',1)
            
#     for mol in glist:
#         print i
#         j=0

#         for feature in flist:
#             GM = iso.GraphMatcher(mol,feature,node_match=nm,edge_match=em)
#             if GM.subgraph_is_isomorphic():
#                 fva[i][j]=1
#             j+=1
#         i+=1
#     return fva
# In[333]:


# print len(mola)


# In[334]:


# fva=np.zeros((len(mola),len(frequent)))
# fvi=np.zeros((len(moli),len(frequent)))
# fg=frequent


# # In[335]:


# start=time.time()
# fa=create_fvl(mola,fg)
# end=time.time()
# # fi=create_fvl(moli,fg)
        
# print end-start
# start=time.time()
# fi=create_fvl(moli,fg)
# end=time.time()
# # fi=create_fvl(moli,fg)
        
# print end-start
# #       


# # In[338]:

