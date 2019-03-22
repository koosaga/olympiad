#include <bits/stdc++.h>
using namespace std;
using lint = long long;
const int MAXN = 100005;

int cnt[MAXN];

int main(){
	int n; cin >> n;
	for(int i=1; i<=n; i++){
		int sum = 0;
		for(int j=i; ; j++){
			sum += j;
			if(sum > n) break;
			cnt[sum]++;
		}
	}
	lint ret = 0;
	for(int i=1; i<=n; i++){
		if(n % i == 0) ret += 1ll * cnt[i] * cnt[n / i];
	}
	cout << ret << endl;
}
