#include <bits/stdc++.h>
using namespace std;
const int MAXN = 50005;
typedef long long lint;

int moe[MAXN];

int main(){
	moe[1] = 1;
	for(int i=1; i<=50000; i++){
		for(int j=2*i; j<=50000; j+=i) moe[j] -= moe[i];
	}
	for(int i=1; i<=50000; i++) moe[i] += moe[i-1];
	int q;
	scanf("%d",&q);
	while(q--){
		int a, b, c;
		scanf("%d %d %d",&a,&b,&c);
		a /= c;
		b /= c;
		lint ret = 0;
		int pos = 1;
		while(pos <= min(a, b)){
			int ma = a / pos;
			int mb = b / pos;
			int nxt = min(a / ma, b / mb) + 1;
			ret += 1ll * ma * mb * (moe[nxt - 1] - moe[pos - 1]);
			pos = nxt;
		}
		printf("%lld\n", ret);
	}
}
