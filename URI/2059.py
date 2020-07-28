# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/2059
#!/usr/bin/env python2.7
# encoding : utf-8
p,j1,j2,r,a = [int(i) for i in raw_input().split(" ")]
if r ^ a:
	print "Jogador 1 ganha!"
else:
	if r==1 and a==1:
		print "Jogador 2 ganha!"
	else:
		if p == 1:
			if (j1+j2) % 2 == 0:
				print "Jogador 1 ganha!"
			else:
				print "Jogador 2 ganha!"
		else:
			if (j1+j2)%2==0:
				print "Jogador 2 ganha!"
			else:
				print "Jogador 1 ganha!"
