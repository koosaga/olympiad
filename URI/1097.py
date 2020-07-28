# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1097
# -*- coding: utf-8 -*-
i = 1
j = 7
while i <= 9:
    print "I=%d J=%d" % (i,j)
    print "I=%d J=%d" % (i,j-1)
    print "I=%d J=%d" % (i,j-2)
    i += 2
    j += 2
