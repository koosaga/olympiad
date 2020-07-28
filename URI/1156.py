# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1156
#!/usr/bin/env python2.7
# encoding : utf-8
print "%.2f" % (sum([float(i)/float(2**j) for i,j in zip(range(1,40,2),range(20))]))
