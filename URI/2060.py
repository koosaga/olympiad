# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2060
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
array = [int(i) for i in raw_input().split(" ")]
for j in [2,3,4,5]:
	print "%d Multiplo(s) de %d" % (len([i for i in array if i % j==0]),j)
