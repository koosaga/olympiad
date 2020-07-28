# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1043
# encoding : utf-8
a,b,c = [float(i) for i in raw_input().split(" ")]
x,y,z = sorted([a,b,c])
if z < x + y:
    print 'Perimetro = %.1f' % (x+y+z)
else:
    area = (a + b) * c / 2.0
    print 'Area = %.1f' % area
