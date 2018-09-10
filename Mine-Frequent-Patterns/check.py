import sys
file1=open(sys.argv[1],"r")
file2=open(sys.argv[2],"r")
array1=[]
array2=[]
for line in file1:
	 array1.append(sorted([int(x) for x in line.split()]))
for line in file2:
	 array2.append(sorted([int(x) for x in line.split()]))

if len(array1)!=len(array2):
	print "false"
else:
	array1=sorted(array1)
	array2=sorted(array2)
	flag=0
	for i in range (0,len(array1)):
		if array1[i]!=array2[i]:
			print "false"
			flag=1
			break

	if flag!=1:
		print "true"
