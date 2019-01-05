#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1000005;
using lint = long long;

int n;
lint cnt[MAXN];

int main(){
	for(int i=1; i<=1000000; i++){
		for(lint j=i+1; i*j<=1000000; j++){
			for(lint k=j+1; i*j*k<=1000000; k++){
				cnt[i*j*k]++;
			}
		}
	}
	for(int i=1; i<=1000000; i++) cnt[i] += cnt[i-1];
	int q; scanf("%d",&q);
	while(q--){
		int x; scanf("%d",&x);
		printf("%lld\n", cnt[x]);
	}
}
