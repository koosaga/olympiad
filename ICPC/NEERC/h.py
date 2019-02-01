m, n = map(int, input().split())
s = [input() for i in range(n)]
indices = set(map(lambda x: int(x)-1, input().split()))

lengths = set([len(s[i]) for i in indices])
if len(lengths) != 1:
	print("No")
	exit(0)

non_indices = set(range(n)) - indices

l = lengths.pop()

ans = []

for j in range(l):
	ch = set()
	for i in indices:
		ch.add(s[i][j])
	if len(ch) == 1:
		ans.append(ch.pop())
	else:
		ans.append('?')

ans = "".join(ans)

for i in non_indices:
	good = True
	if len(s[i]) != l:
		continue
	for j in range(l):
		if ans[j] == '?':
			pass
		elif ans[j] != s[i][j]:
			good = False
			break
	if good:
		print("No")
		exit(0)

print("Yes")
print(ans)