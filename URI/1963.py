# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1963
#!/usr/bin/env python2.7
# encoding : utf-8
a,b = [float(i) for i in raw_input().split(" ")]
print "%.2f%%" % (100*((b/a)-1.00))
