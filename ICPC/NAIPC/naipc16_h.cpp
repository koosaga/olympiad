#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

vector<lint> v[305];
int n, m;
lint dp[100005];

void dnc(int s, int e, int ps, int pe, vector<lint> &prv, vector<lint> &cur, vector<lint> &cst){
	if(s > e) return;
	int m = (s+e)/2;
	int opt = -1;
	for(int i=ps; i<=pe; i++){
		if(m - i < 0 || m - i > cst.size()) continue;
		if(cur[m] < prv[i] + (m == i ? 0 : cst[m-i-1])){
			cur[m] = prv[i] + (m == i ? 0 : cst[m-i-1]);
			opt = i;
		}
	}
	dnc(s, m-1, ps, opt, prv, cur, cst);
	dnc(m+1, e, opt, pe, prv, cur, cst);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		int x, c;
		scanf("%d %d",&x,&c);
		v[x].push_back(c);
	}
	for(int i=1; i<=300; i++){
		sort(v[i].begin(), v[i].end());
		reverse(v[i].begin(), v[i].end());
		for(int j=1; j<v[i].size(); j++) v[i][j] += v[i][j-1];
		for(int j=0; j<i; j++){
			vector<lint> v1, v2;
			for(int k=j; k<=m; k+=i){
				v1.push_back(dp[k]);
			}
			v2.resize(v1.size(), -1e18);
			dnc(0, v1.size() - 1, 0, v1.size() - 1, v1, v2, v[i]);
			int p = 0;
			for(int k=j; k<=m; k+=i){
				dp[k] = v2[p++];
			}
		}
	}
	for(int i=1; i<=m; i++) printf("%lld ", dp[i]);
}
