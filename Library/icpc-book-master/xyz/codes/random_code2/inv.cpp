/*
 0 = 0
 0 = p
 0 = (p / i) * i + (p % i)
 -(p % i) = (p / i) * i
 -(p % i) * inv[i] = (p / i)
 inv[i] = -inv[p % i] * (p / i)
*/
#include <cstdio>
using namespace std;
#define p 1000000009
int n, i, inv[2000000];
int main(){
	scanf("%d", &n);
	for (inv[1] = 1, i = 2; i <= n; i++)	inv[i] = (-1LL * inv[p % i] * (p / i) % p + p) % p;
}