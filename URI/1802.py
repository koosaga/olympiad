# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1802
#!/usr/bin/env python2.7
# encoding : utf-8
entrada = []
for i in xrange(5):
	entrada.append(sorted([int(j) for j in raw_input().split(" ")[1:]]))
ordem = int(raw_input())
grupos = []
for a1 in entrada[0]:
	for a2 in entrada[1]:
		for a3 in entrada[2]:
			for a4 in entrada[3]:
				for a5 in entrada[4]:
					grupos.append(a1+a2+a3+a4+a5)
print sum(sorted(grupos)[::-1][:ordem])
