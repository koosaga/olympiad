# Ivan Carvalho
# Solution to https://www.urionlinejudge.com.br/judge/problems/view/1197
# -*- coding: utf-8 -*-
while True:
    try:
        a,b = [int(i) for i in raw_input().split(" ")]
        print 2*a*b
    except EOFError:
        break
