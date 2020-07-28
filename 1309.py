# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1309
#!/usr/bin/env python2.7
# encoding : utf-8
def metodo(texto):
	if texto in [str(i) for i in xrange(10)]:
		return "0%s" % texto
	else:
		return texto
while True:
	try:
		entrada1 = [k for k in raw_input()]
		entrada2 = raw_input()
		tamanho = len(entrada1)
		if tamanho <= 3:
			print "$%s.%s" % ("".join(entrada1),metodo(entrada2))
		else:
			if tamanho % 3 == 1:
				entrada1.insert(0,"*")
				entrada1.insert(0,"*")
			elif tamanho % 3 == 2:
				entrada1.insert(0,"*")
			count = 0
			for i in xrange(3,tamanho,3):
				entrada1.insert(i+count,",")
				count += 1
			print "$%s.%s" % ("".join(entrada1).replace("*",""),metodo(entrada2))
	except EOFError:
		break
