#include <cstdio>
#include <cmath>
#include <iostream>
using namespace std;
#define N 300000
#define pi acos(-1)
typedef long long int64;
struct Num
{
    double x, y;
    inline Num() {}
    inline Num(const double &_x, const double &_y) : x(_x), y(_y) {}
}a[N], b[N], x[N], w[N];
int n, m, i, q[N];
int64 Ans[N];

void read(int &x){
	char k;
	for (k = getchar(); k <= 32; k = getchar());
	x = k - '0';
}
Num operator + (Num x, Num y){
	return Num(x.x + y.x, x.y + y.y);
}
Num operator * (Num x, Num y){
	return Num(x.x * y.x - x.y * y.y, x.y * y.x + x.x * y.y);
}
void DFT(Num *a, int n){
	int m, p, s1, s2, d, i;
	for (m = 1; n >= (1 << m); m++){
		for (p = 0; p < (n >> m); p++){
			s1 = p;
			s2 = p + (n >> m);
			d = p;
			for (i = 0; d < (n >> 1); i++, d += (n >> m), s1 += (n >> (m - 1)), s2 += (n >> (m - 1))){
				x[d] = (a[s1] + a[s2] * w[(n >> m) * i]);
				x[d + n / 2] = (a[s1] + a[s2] * w[(n >> m) * i + n / 2]);
			}
		}
		for (p = 0; p < n; p++)	a[p] = x[p];
	}
}
void fft(Num *a, Num *b, int n){
	for (int i = 0; i < n; i++)	w[i] = Num(cos(pi * 2 * i / n), sin(pi * 2 * i / n));
	DFT(a, n); DFT(b, n);
	for (int i = 0; i < n; i++)	a[i] = a[i] * b[i], w[i].y = -w[i].y;
	DFT(a, n);
	for (int i = 0; i < n; i++)	a[i].x /= n, a[i].y /= n;
}
int main(){
	freopen("plus.in", "r", stdin);
	freopen("plus.out", "w", stdout);
	scanf("%d%d", &n, &m);
	// scanf("%d", &n);
	// m = n;
	for (i = 1; i <= n; i++)	read(q[n - i]);
	for (i = n - 1; i >= 0; i--)	a[i / 5].x = a[i / 5].x * 10 + q[i];
	for (i = 1; i <= m; i++)	read(q[m - i]);
	for (i = m - 1; i >= 0; i--)	b[i / 5].x = b[i / 5].x * 10 + q[i];
	n = (n - 1) / 5 + 1; m = (m - 1) / 5 + 1;
	for (i = 1; i < 2 * n || i < 2 * m; i *= 2);
	n = i;
	fft(a, b, n);
	for (i = 0; i < n; i++)	Ans[i] = int64(a[i].x + 0.5);
	for (i = 0; i < n; i++){
		Ans[i + 1] += Ans[i] / 100000;
		Ans[i] %= 100000;
	}
	for (i = n - 1; !Ans[i]; i--);
	for (printf("%lld", Ans[i--]); i >= 0; i--)	printf("%05lld", Ans[i]);
	printf("\n");
}