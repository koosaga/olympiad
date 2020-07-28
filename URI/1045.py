# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1045
#!/usr/bin/env python2.7
# encoding : utf-8
a,b,c = sorted([float(k) for k in raw_input().split(" ")])
def istriangle(x,y,z):
    return x+y>z and x+z>y and y+z>x
def tipo(x,y,z):
    if x**2 + y**2 == z**2:
        return "RETANGULO"
    elif x**2+ y **2 >= z**2:
        return "ACUTANGULO"
    else:
        return "OBTUSANGULO"
if istriangle(a,b,c):
    print "TRIANGULO %s" % tipo(a,b,c)
    if len(set([a,b,c]))==1:
        print "TRIANGULO EQUILATERO"
    elif len(set([a,b,c]))==2:
        print "TRIANGULO ISOSCELES"
else:
    print "NAO FORMA TRIANGULO"

