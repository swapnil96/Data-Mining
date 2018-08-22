import matplotlib.pyplot as plt

file=open("logs.txt","r")
X=[1,5,10,25,50,90]
Y1=[]
Y2=[]
for line in file:
	x=line.split(" ")
	Y1.append(float(x[0]))
	Y2.append(float(x[1]))

plt.plot(X,Y1,'ro')
plt.plot(X,Y2,'go')
l1=plt.plot(X,Y1,'r')
l2=plt.plot(X,Y2,'g')
plt.xlabel('Minimum Support Values')
plt.ylabel('Running time')
plt.legend([l1,l2],['Apriori','FP-Tree'])
plt.show()	