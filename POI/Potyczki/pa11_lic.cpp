#include <bits/stdc++.h>
const int MAXN = 3000005;
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, cnt[MAXN], moe[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){ 
		int x;
		scanf("%d",&x);
		cnt[x]++;
	}
	moe[1] = 1;
	for(int i=1; i<=3000000; i++){
		for(int j=2*i; j<=3000000; j+=i) moe[j] -= moe[i];
	}
	lint ret = 0;
	for(int i=1; i<=3000000; i++){
		int ans = 0;
		for(int j=i; j<=3000000; j+=i) ans += cnt[j];
		ret += 1ll * ans * ans * moe[i];
	}
    ret -= cnt[1];
	ret /= 2;
	cout << ret <<endl;
}

