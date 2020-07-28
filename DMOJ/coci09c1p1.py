# Ivan Carvalho
# Solution to https://dmoj.ca/problem/coci09c1p1

tones = [int(i) for i in input().split()]

if tones == list(range(1,9)):
	print("ascending")
elif tones == list(range(1,9))[::-1]:
	print("descending")
else:
	print("mixed")