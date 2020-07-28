# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1214
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
for i in xrange(ordem) :
	array = [int(i) for i in raw_input().split(" ")]
	media = sum(array[1:])/float(array[0])
	print "%.3f%%" % (100.0*len([k for k in array[1:] if k > media])/float(array[0]))
