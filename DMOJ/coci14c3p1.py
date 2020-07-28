# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci14c3p1

tipo = ["1QAZ","2WSX","3EDC","4RFV5TGB","6YHN7UJM","8IK,","9OL.","0P;//-=[]'"]
qtd = [0 for i in range(len(tipo))]
a = input()

for i in a:
	for j in range(len(tipo)):
		if i in tipo[j]:
			qtd[j]+=1
			break
	else:
		print("Invalid Input")

for i in qtd:
	print(i)