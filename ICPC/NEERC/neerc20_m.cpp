#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 100005;
 
int n;
int dp[MAXN], slack[MAXN];
 
int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int m; scanf("%d",&m);
		vector<int> v(m);
		for(auto &j : v){
			scanf("%d",&j);
			dp[i] = max(dp[i], slack[j]);
		}
		dp[i]++;
		for(auto &j : v){
			slack[j] = max(slack[j], dp[i]);
		}
	}
	cout << *max_element(dp, dp + MAXN) << endl;
}
