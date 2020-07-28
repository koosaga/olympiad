# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1873
#!/usr/bin/env python2.7
# encoding : utf-8
ordem = int(raw_input())
def exibir(texto):
	if texto in ["tesoura papel","papel pedra","pedra lagarto","lagarto spock","spock tesoura","tesoura lagarto","lagarto papel","papel spock","spock pedra","pedra tesoura"]:
		print "rajesh"
	elif texto in ["tesoura tesoura","papel papel","lagarto lagarto","spock spock","pedra pedra"]:
		print "empate"
	else:
		print "sheldon"
for i in xrange(ordem):
	exibir(raw_input())
