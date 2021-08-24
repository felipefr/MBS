import numpy as np

def readFile(nom):
	fichier=open(nom,'r')
			
	x=[]
	line=fichier.readline()
					
	while line!='':		
		valeurs=line.split(' ')
		xi=[]
		for s in valeurs:
			xi.append(eval(s))
		
		x.append(np.array(xi))
		
		line=fichier.readline()

	x=np.matrix(x)
	return x
