# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1553
# encoding : utf-8
def frequente(conjunto,numero):
    return len([j for j in [conjunto.count(i) for i in set(conjunto)] if j>= numero])
while True:
    a,b = [int(i) for i in raw_input().split(" ")]
    if a != 0 and b != 0 :
        print frequente([int(j) for j in raw_input().split(" ")],b)
    else:
        break
