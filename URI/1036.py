# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1036
# encoding : utf-8
a,b,c = [float(i) for i in raw_input().split(" ")]
delta = b**2 - 4*a*c
if delta >=0 and a != 0:
        print "R1 = %.5f" % ((-1*b+(delta**0.5))/(2*a))
        print "R2 = %.5f" % ((-1*b-(delta**0.5))/(2*a))
else:
    print "Impossivel calcular"
