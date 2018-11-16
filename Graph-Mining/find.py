import sys

f=open(sys.argv[1])
f2a=open("ga",'w+')
f2i=open("gi",'w+')
f3=open("datafile",'w+')
f4=open("testfile",'w+')
fa=open(sys.argv[2],'r+')
fi=open(sys.argv[3],'r+')
ftest=open(sys.argv[4],'r+')



# In[29]:


x={}


# In[30]:


for line in fa.readlines():
    x[int(line)]=1
for line in fi.readlines():
    x[int(line)]=-1


# In[31]:


lines=f.readlines()
towritea=[]
towritei=[]
towrite=[]
testwrite=[]
lines2=ftest.readlines()

# In[32]:

elem={}
c=0
c1=0
c2=0
c3=0
c4=0
size=len(lines)
#print size
node={}
while (c<size):
#     #print c
#     c2=0
    # node={}
    a=lines[c].split('#')
#     #print a
    subgraph=int(a[1])
    c+=1
    if subgraph in x:
        #print "yey"
        if(x[subgraph]==1):
            towritea.append("t # "+str(subgraph)+"\n")
            towrite.append("t # "+str(subgraph)+"\n")
            c1+=1
            numv=int(lines[c])
            c+=1
            v=[]
            e=[]
            for i in range(0,numv):
                a=lines[c]
        #         #print ("e" +str(a))
                if a in node:
                    towritea.append("v "+str(i)+" "+node[a])
                    towrite.append("v "+str(i)+" "+node[a])
                    c+=1
                else:
                    node[a]=str(c4)+"\n"
                    towritea.append("v "+str(i)+" "+node[a])
                    towrite.append("v "+str(i)+" "+node[a])
                    c4+=1
                    c+=1
            a=lines[c].split('#')
            nume=int(lines[c])
            c+=1
            for i in range(0,nume):
                a=lines[c]
        #         #print ("e" +str(a))
                towritea.append("e "+str(a))
                towrite.append("e "+str(a))
                c+=1
            
        elif(x[subgraph]==-1):
            towritei.append("t # "+str(subgraph)+"\n")
            towrite.append("t # "+str(subgraph)+"\n")
            
            c2+=1
            numv=int(lines[c])
            c+=1
            v=[]
            e=[]
            for i in range(0,numv):
                a=lines[c]
        #         #print ("e" +str(a))
                if a in node:
                    towritei.append("v "+str(i)+" "+node[a])
                    towrite.append("v "+str(i)+" "+node[a])
                    c+=1
                else:
                    node[a]=str(c4)+"\n"
                    towritei.append("v "+str(i)+" "+node[a])
                    towrite.append("v "+str(i)+" "+node[a])
                    c4+=1
                    c+=1
            a=lines[c].split('#')
            nume=int(lines[c])
            c+=1
            for i in range(0,nume):
                a=lines[c]
        #         #print ("e" +str(a))
                towritei.append("e "+str(a))                
                towrite.append("e "+str(a))
                c+=1
            
    
    
    
    else:
        
#     c1+=1
        a=lines[c].split('#')
        numv=int(lines[c])
        c+=1+numv
        a=lines[c].split('#')
        nume=int(lines[c])
        c+=1+nume
        






c=0
size=len(lines2)
#print size
node={}
while (c<size):
#     #print c
#     c2=0
    # node={}
    a=lines2[c].split('#')
#     #print a
    subgraph=int(a[1])
    c+=1
            # towritea.append("t # "+str(subgraph)+"\n")
    testwrite.append("t # "+str(subgraph)+"\n")
    c1+=1
    numv=int(lines2[c])
    c+=1
    v=[]
    e=[]
    for i in range(0,numv):
        a=lines2[c]
#         #print ("e" +str(a))
        if a in node:
            testwrite.append("v "+str(i)+" "+node[a])
            c+=1
        else:
            node[a]=str(c4)+"\n"
            testwrite.append("v "+str(i)+" "+node[a])
            c4+=1
            c+=1
    a=lines2[c].split('#')
    nume=int(lines2[c])
    c+=1
    for i in range(0,nume):
        a=lines2[c]
#         #print ("e" +str(a))
        testwrite.append("e "+str(a))
        c+=1
    
        





# #print towrite

# #print e
for l in towritea:
    f2a.write(l)
for l in towritei:
    f2i.write(l)
for l in towrite:
    f3.write(l)
for l in testwrite:
    f4.write(l) 


# In[ ]:
#print len(towritea)
#print len(towritei)
#print len(towrite)

