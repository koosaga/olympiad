# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci06c2p2
dicio = dict(zip(["A","B","C"],sorted([int(i) for i in 
input().split()])))
lista = [str(dicio[i]) for i in input()]
print(" ".join(lista))
