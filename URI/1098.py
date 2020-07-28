# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1098
# -*- coding: utf-8 -*-
def b(numero):
    if numero % 1 == 0:
        return str(int(numero))
    else:
        return str(numero)
i = 0
j = 10
while i <= 20:
    print "I=%s J=%s" % (b(i/10.0),b(j/10.0))
    print "I=%s J=%s" % (b(i/10.0),b((j+10)/10.0))
    print "I=%s J=%s" % (b(i/10.0),b((j+20)/10.0))
    i += 2
    j += 2
