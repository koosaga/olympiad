n, k = tuple(map(int, input().split()))

b = []

for i in range(0, n):
    a = list(map(int, input().split()))[1::]
    b.append(a)

sum = 0

while k > 0:
    found = 0
    for j in range(0, n):
        if(len(b[j]) > 0):
            found = 1
            if sum <= b[j][0] and k > 0:
                sum += b[j][0]
                k -= 1
            b[j] = b[j][1::]
        elif sum <= 50 and k > 0:
            sum += 50
            k -= 1
            found = 1
    if found == 0:
        sum += 50 * k
        k = 0

print(sum)
