#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<double, int> pi;

vector<int> gph[200005];
multiset<int> s[200005];
int n, v[200005];
int dp[200005];

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int p;
		scanf("%d %d",&v[i],&p);
		if(p) gph[p].push_back(i);
	}
	for(int i=n; i; i--){
		if(gph[i].empty()){
			dp[i] = i;
			s[i].insert(v[i]);
			continue;
		}
		else{
			int x = i;
			dp[x] = dp[gph[x][0]];
			for(auto &i : gph[x]){
				if(s[dp[i]].size() > s[dp[x]].size()){
					dp[x] = dp[i];
				}
			}
			for(auto &i : gph[x]){
				if(dp[i] != dp[x]){
					for(auto &j : s[dp[i]]){
						s[dp[x]].insert(j);
					}
				}
			}
			auto l = s[dp[x]].lower_bound(v[i]);
			if(l != s[dp[x]].end()){
				s[dp[x]].erase(l);
			}
			s[dp[x]].insert(v[i]);
		}
	}
	cout << s[dp[1]].size();
}

