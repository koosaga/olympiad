# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1071
#!/usr/bin/env python2.7
# encoding : utf-8
a = int(raw_input())
b = int(raw_input())
x,y = sorted([a,b])
if x % 2 == 1:
	x += 2
else :
	x += 1
print sum(range(x,y,2))
