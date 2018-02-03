import sys
sys.stdin = open('jumper.in', 'r')

n = int(input());
ans = 1
if n % 2 == 0:
    ans += 2
    n -= 1

while n >= 1:
    ans += 2;
    n //= 2;

print(ans)
sys.stdin = sys.__stdin__
