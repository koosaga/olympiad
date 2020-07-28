// Ivan Carvalho
// Solution to https://dmoj.ca/problem/year2018p1
h,m,s = [int(i) for i in raw_input().split()]
conv1 = 3600
conv2  = 60
dia = 24*conv1
total = conv1*h + conv2*m + s
total = total % dia
horario = dia - total
exibe1 = horario/conv1
horario = horario % conv1
exibe2 = horario/conv2
horario = horario % conv2
if exibe1 >= 12:
	exibe1 -= 12
davez1 = str(exibe1)
if exibe1 < 10:
	davez1 = "0" + davez1
davez2 = str(exibe2)
if exibe2 < 10:
	davez2 = "0" + davez2
davez3 = str(horario)
if horario < 10:
	davez3 = "0" + davez3
print "%s:%s:%s" % (davez1,davez2,davez3)