# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1048
# encoding : utf-8
e = float(raw_input())
coeficiente = 0
novo = 0
if e <= 400:
    novo = e * 1.15
    coeficiente = 15
elif e <= 800:
    novo = e * 1.12
    coeficiente = 12
elif e <= 1200:
    novo = e * 1.1
    coeficiente = 10
elif e <= 2000:
    novo = e * 1.07
    coeficiente = 7
else:
    novo = e * 1.04
    coeficiente = 4
print 'Novo salario: %.2f' % novo
print 'Reajuste ganho: %.2f' % (novo - e)
print 'Em percentual: %d %%' % coeficiente
