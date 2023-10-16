a, b = map(int, input().split(" "))
dap = []

def AA():
	global a, b
	dap.append("A+=A")
	b = b // 2

def AB():
	global a, b
	dap.append("A+=B")
	a = a + b

def BA():
	global a, b
	dap.append("B+=A")
	b = b + a

def BB():
	global a, b
	dap.append("B+=B")
	a = a // 2

while a != b:
	if a % 2 == 0:
		BB()
	elif b % 2 == 0:
		AA()
	else:
		if a < b:
			BA()
			AA()
		else:
			AB()
			BB()

print(len(dap))
print("\n".join(dap))
