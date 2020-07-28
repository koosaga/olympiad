# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1131
#!/usr/bin/env python2.7
# encoding :utf-8
counti = 0
countg = 0
empate = 0
while True:
	inter,gremio = [int(i) for i in raw_input().split(" ")]
	if inter == gremio:
		empate += 1
	elif inter > gremio:
		counti += 1
	else:
		countg += 1
	print "Novo grenal (1-sim 2-nao)"
	ordem = int(raw_input())
	if ordem==1:
		pass
	else:
		break
print "%d grenais" % (counti+countg+empate)
print "Inter:%d" % (counti)
print "Gremio:%d" % (countg)
print "Empates:%d" % (empate)
if counti == countg:
	print "Nao houve vencedor"
elif counti > countg:
	print "Inter venceu mais"
else:
	print "Gremio venceu mais"
