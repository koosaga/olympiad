#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

struct disj{
	int pa[1000005];
	void init(int n){
		for(int i=0; i<=n; i++) pa[i] = i;
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
}disj;

vector<pi> edg;
int n, dp[2000005], deg[1000005];
char inp[1000005], str[2000005];

int main(){
	scanf("%s", inp);
	n = strlen(inp);
	disj.init(n);
	for(int i=0; i<n; i++){
		str[2*i+1] = '$';
		str[2*i] = inp[i];
	}
	int c = 0, p = 0;
	for(int i=0; i<2*n; i++){
		if(i <= p) dp[i] = min(dp[2*c-i], p - i);
		while(i - dp[i] - 1 >= 0 && i + dp[i] + 1 < 2 * n && str[i - dp[i] - 1] == str[i + dp[i] + 1]){
			if((i - dp[i] - 1) % 2 == 0) disj.uni((i - dp[i] - 1) / 2, (i + dp[i] + 1) / 2);
			dp[i]++;
		}
		if(i - dp[i] - 1 >= 0 && i + dp[i] + 1 < 2 * n && (i - dp[i] - 1) % 2 == 0){
			edg.push_back(pi((i - dp[i] - 1) / 2, (i + dp[i] + 1) / 2));
		}
		if(i + dp[i] > p){
			c = i;
			p = i + dp[i];
		}
	}
	for(auto &i : edg){
		i.first = disj.find(i.first);
		i.second = disj.find(i.second);
		if(i.first > i.second) swap(i.first, i.second);
	}
	sort(edg.begin(), edg.end());
	edg.resize(unique(edg.begin(), edg.end()) - edg.begin());
	for(auto &i : edg) deg[i.second]++;
	lint ret = 1;
	for(int i=0; i<n; i++){
		if(disj.find(i) == i){
			ret *= 26 - deg[i];
			ret %= mod;
		}
	}
	cout << ret;
}
