#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;

lint gcd(lint x, lint y){
	return y ? gcd(y, x%y) : x;
}

int n;
lint a[MAXN], b[MAXN];
int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%lld",&a[i]);
	for(int i=0; i<n; i++) scanf("%lld",&b[i]);
	lint g = 0;
	for(int i=0; i<n; i++) g = gcd(g, a[i] - b[i]);
	printf("%lld\n", g);
}
