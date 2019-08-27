#include <cstdio>
#include <algorithm>
#include <cstdlib>
#include <ctime>
using namespace std;
typedef long long int64;
int64 x, z[100];
int q, h;

int64 Bow(int64 x, int64 y, int64 z){
	return (x * y - int64(x / (long double) z * y + 1e-3) * z + z) % z;
}
bool St(int64 a, int64 b){
	if (a == b)	return false;
	int64 i, ans1, ans;
	for (i = 64, ans1 = ans = 1; i >= 0; i --){
		ans = Bow(ans1, ans1, b);
		if (ans == 1 && ans1 != 1 && ans1 != b - 1)	return true;
		if ((b - 1) & (1LL << i))	ans = Bow(ans, a, b);
		ans1 = ans;
	}
	return (ans != 1);
}
bool prime(int64 x){
	return !(St(2, x) || St(3, x) || St(5, x) || St(7, x) || St(11, x) || St(13, x) || St(17, x) || St(19, x) || St(23, x));
}
int64 gcd(int64 a, int64 b){
	if (!a)	return abs(b);
	return gcd(b % a, a);
}
int64 ra(int64 x){
	return (rand() * 2147483647LL + rand() * 32767LL + rand()) % x;
}
int64 pro(int64 x){
	int64 x1 = ra(x), x2 = (Bow(x1, x1, x) + 1) % x, p = gcd(x1 - x2, x);
	while (p == 1){
		x1 = (Bow(x1, x1, x) + 1) % x;
		x2 = (Bow(x2, x2, x) + 1) % x;
		x2 = (Bow(x2, x2, x) + 1) % x;
		p = gcd(x1 - x2, x);
	}
	if (p)	return p;
	return x;
}
void divide(int64 x){
	if (x == 1)	return ;
	if (!(x & 1))	z[++z[0]] = 2, divide(x / 2); // 注意对偶数的特判
	else	if (prime(x))	z[++z[0]] = x;
	else{
		int64 y = pro(x);
		divide(x / y);
		divide(y);
	}
}
int main(){
	scanf("%lld", &x);
	divide(x);
	sort(z + 1, z + z[0] + 1);
	for (q = 1; q <= z[0]; q = h + 1){
		for (h = q; h < z[0] && z[h + 1] == z[h]; h++);
		if (q != h)	printf("%lld^%d", z[q], h - q + 1);	else	printf("%lld", z[q]);
		if (h < z[0])	printf("*");
	}
}