#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int mod = 998244353;
const int MAXN = 100005;

int n, vis[MAXN];
lint dp[MAXN][2];
vector<pi> gph[MAXN];
lint a[MAXN], b[MAXN], ta[MAXN];
int pa[MAXN];
vector<int> proc, rt;

void dfs(int x){
	vis[x] = 1;
	for(auto fuck : gph[x]){
		int j = fuck.first;
		int i = fuck.second;
		pa[i] = x;
		gph[i].erase(find(all(gph[i]), pi(j, x)));
		dfs(i);
	}
	proc.push_back(x);
}

void fetch(int x){
	dp[x][0] = -a[x];
	dp[x][1] = ta[x];
	for(auto fuck : gph[x]){
		int j = fuck.first;
		int i = fuck.second;
		dp[x][0] += max(dp[i][0], dp[i][1]);
		dp[x][1] += max(dp[i][0], dp[i][1] + j);
	}
}

int main(){
	int n = 100000; 
	scanf("%d",&n);
	for(int i=1; i<=n; i++) scanf("%lld",&a[i]);
	for(int i=1; i<=n; i++) scanf("%lld",&b[i]);
	vector<pi> edg;
	vector<int> ord;
	for(int i=2; i<=n&&i<=500; i++){
		for(int j=i*i; j<=n; j*=i){
			if(i >= 18){
				gph[i].emplace_back(-b[j], j);
				gph[j].emplace_back(-b[j], i);
				ord.push_back(i);
				ord.push_back(j);
			}
			else{
				edg.emplace_back(i - 2, j - 2);
				if(j >= 18) ord.push_back(j);
			}
		}
	}
	for(auto &i : ord){
		if(!vis[i]){
			rt.push_back(i);
			dfs(i);
		}
	}
	for(auto &i : proc) fetch(i);
	lint ret = -1e18;
	for(int i=0; i<(1<<16); i++){
		lint tmp = 0;
		int chk[16] = {};
		for(int j=0; j<16; j++){
			if((i >> j) & 1){
				chk[j] = 1;
			}
			else tmp -= a[j + 2];
		}
		for(auto &j : edg){
			if(j.second < 16){
				if(chk[j.first] && chk[j.second]) tmp -= b[j.second + 2];
			}
			else if(j.first < 16){
				if(chk[j.first]){
					ta[j.second + 2] -= b[j.second + 2];
					for(int x = j.second + 2; x; x = pa[x]) fetch(x);
				}
			}
		}
		for(auto &i : rt) tmp += max(dp[i][0], dp[i][1]);
		ret = max(ret, tmp);
		for(auto &j : edg){
			if(j.first < 16 && j.second >= 16){
				if(chk[j.first]){
					ta[j.second + 2] += b[j.second + 2];
					for(int x = j.second + 2; x; x = pa[x]) fetch(x);
				}
			}
		}
	}
	cout << accumulate(a, a + n + 1, ret) << endl;
}
