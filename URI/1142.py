# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1142
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
i = 1
count = 0
while count < ordem:
	print "%d %d %d PUM" % (i,i+1,i+2)
	i += 4
	count += 1
