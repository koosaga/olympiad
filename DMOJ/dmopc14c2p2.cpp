// Ivan Carvalho
// Solution to https://dmoj.ca/problem/dmopc14c2p2
a = int(raw_input())
entrada = [i for i in raw_input().split("X") if i != ""]
print len(entrada)
for i in entrada:
	print i