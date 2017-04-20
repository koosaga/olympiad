#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, a[100005], d[1000005];
pi ans[100005];
vector<int> rv[1000005];
vector<int> mul[1000005];
bool isprime[1000005] = {};

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d",&a[i]);
		rv[a[i]].push_back(i);
	}
	fill(isprime + 2, isprime + 1000001, 1);
	fill(ans, ans + n, pi(1e9, -1));
	for(int i=2; i<=1000000; i++){
		for(int j=2*i; j<=1000000; j+=i){
			isprime[j] = 0;
		}
	}
	memset(d, 0x3f, sizeof(d));
	d[1] = 0;
	for(int i=1; i<=1000000; i++){
		for(int j=i; j<=1000000; j+=i){
			if(isprime[j / i]) d[j] = min(d[j], d[i] + 1);
			for(auto &k : rv[j]){
				mul[i].push_back(k);
			}
		}
	}
	for(int i=1; i<=1000000; i++){
		int pos = -1, cur = 1e9;
		sort(mul[i].begin(), mul[i].end());
		for(auto &j : mul[i]){
			if(d[a[j]] < cur){
				cur = d[a[j]];
				pos = j;
			}
		}
		for(auto &j : mul[i]){
			if(pos == j) continue;
			ans[j] = min(ans[j], pi(d[a[j]] + d[a[pos]] - 2 * d[i], pos + 1));
			ans[pos] = min(ans[pos], pi(d[a[j]] + d[a[pos]] - 2 * d[i], j + 1));
		}
	}
	for(int i=0; i<n; i++) printf("%d\n", ans[i].second);
}
