# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1050
# -*- coding: utf-8 -*-
ddd = {11:"Sao Paulo",
71:"Salvador",
61:"Brasilia",
21:"Rio de Janeiro",
32:"Juiz de Fora",
19:"Campinas",
27:"Vitoria",
31:"Belo Horizonte"}
print ddd.get(int(raw_input()),"DDD nao cadastrado")
