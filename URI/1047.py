# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1047
# encoding : utf-8
a,b,c,d = [int(i) for i in raw_input().split(" ")]
minutos1= 60*a+b
minutos2 = 60*c+d
if minutos2<=minutos1:
    minutos2 += 1440
minutos = minutos2 - minutos1
print "O JOGO DUROU %d HORA(S) E %d MINUTO(S)" % (int(minutos/60),minutos%60)
