#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100005;
const int mod = 1e9 + 7;

int n, p[MAXN];
int pfx[MAXN], sfx[MAXN];
int L[MAXN], R[MAXN];
lint sqs[MAXN], rs[MAXN];

lint SQS(int s, int e){
	return (sqs[e + 1] - sqs[s] + mod) % mod;
}

lint RS(int s, int e){
	return (rs[e+1] - rs[s] + mod) % mod;
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x, y; scanf("%d %d",&x,&y);
		p[x] = pfx[x] = sfx[x] = y;
	}
	for(int i=1; i<n; i++) pfx[i] = min(pfx[i], pfx[i-1]);
	for(int i=n-2; i>=0; i--) sfx[i] = max(sfx[i], sfx[i+1]);
	n--;
	for(int i=0; i<n; i++){
		L[i] = pfx[i];
		R[i] = sfx[i + 1];
		sqs[i+1] = sqs[i] + 1ll * R[i] * R[i];
		rs[i+1] = rs[i] + R[i];
		sqs[i+1] %= mod;
		rs[i+1] %= mod;
	}
	lint ret = 0;
	int ptr = 0;
	for(int i=0; i<n; i++){
		while(ptr < n && L[i] < R[ptr]) ptr++;
		ret += SQS(i, ptr - 1) - (2ll * L[i] - 1) * RS(i, ptr - 1) + 1ll * L[i] * (L[i] - 1) * (ptr - i);
		ret %= mod;
		ret += mod;
		ret %= mod;
	}
	ret *= (mod + 1) / 2;
	ret %= mod;
	cout << ret << endl;
}
