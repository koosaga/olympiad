#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
const int MAXN = 1005;
const int MAXK = 55;
const lint inf = 2e18;
using pi = pair<lint, lint>;

int n, k;
lint l, r;

struct info{
	int subtree_size;
	pi val[MAXK][MAXK];
	lint min_sum[MAXK];
	void debug(){
		for(int i = 0; i <= k; i++){
			vector<lint> v;
			printf("size %d\n", i);
			for(int j = 0; j <= i + 1; j++){
				if(val[i][j].first <= val[i][j].second){
					v.push_back(min_sum[i] + val[i][j].first);
					v.push_back(min_sum[i] + val[i][j].second);
				}
			}
			sort(all(v));
			v.resize(unique(all(v)) - v.begin());
			for(auto &i : v) printf("%lld ", i);
			puts("");
		}
	}
	info(){
		subtree_size = 0;
		for(int i = 0; i < MAXK; i++){
			for(int j = 0; j < MAXK; j++){
				val[i][j] = pi(inf, -inf); 
			}
			min_sum[i] = 0;
		}
	}
	info operator+(const info &d){
		info ret;
		ret.subtree_size = subtree_size + d.subtree_size;
		vector<lint> candidates[MAXK];
		for(int i = 0; i <= min(k, subtree_size); i++){
			for(int j = 0; j <= min(k - i, d.subtree_size); j++){
				for(int k = 0; k <= i + 1; k++){
					for(int l = 0; l <= j + 1; l++){
						if(val[i][k].first <= val[i][k].second && d.val[j][l].first <= d.val[j][l].second){
							candidates[i + j].push_back(min_sum[i] + d.min_sum[j] + val[i][k].first + d.val[j][l].first);
							candidates[i + j].push_back(min_sum[i] + d.min_sum[j] + val[i][k].first + d.val[j][l].second);
							candidates[i + j].push_back(min_sum[i] + d.min_sum[j] + val[i][k].second + d.val[j][l].first);
							candidates[i + j].push_back(min_sum[i] + d.min_sum[j] + val[i][k].second + d.val[j][l].second);
						}
					}
				}
			}
		}
		for(int i = 0; i <= k; i++){
			if(!sz(candidates[i])) continue;
			ret.min_sum[i] = *min_element(all(candidates[i]));
			for(auto &j : candidates[i]){
				if(j > r) continue;
				lint delta = j - ret.min_sum[i];
				lint pos = delta / (r - l + 1);
				lint gap = delta;
				ret.val[i][pos].first = min(ret.val[i][pos].first, gap);
				ret.val[i][pos].second = max(ret.val[i][pos].second, gap);
			}
		}
		return ret;
	}
	void adjust(lint x){
		vector<lint> candidates[MAXK];
		for(int i = 0; i <= k; i++){
			for(int j = 0; j <= i + 1; j++){
				if(val[i][j].first <= val[i][j].second){
					candidates[i].push_back(min_sum[i] + val[i][j].first + x);
					candidates[i].push_back(min_sum[i] + val[i][j].second + x);
				}
			}
		}
		for(int i = k - 1; i >= 0; i--){
			bool escalate = 0;
			for(auto &j : candidates[i]){
				if(l <= j && j <= r){
					escalate = 1;
					break;
				}
			}
			if(escalate) candidates[i + 1].push_back(0);
		}
		for(int i = 0; i < MAXK; i++){
			for(int j = 0; j < MAXK; j++){
				val[i][j] = pi(inf, -inf); 
			}
			min_sum[i] = 0;
		}
		for(int i = 0; i <= k; i++){
			if(!sz(candidates[i])) continue;
			min_sum[i] = *min_element(all(candidates[i]));
			for(auto &j : candidates[i]){
				if(j > r) continue;
				lint delta = j - min_sum[i];
				lint pos = delta / (r - l + 1);
				lint gap = delta;
				val[i][pos].first = min(val[i][pos].first, gap);
				val[i][pos].second = max(val[i][pos].second, gap);
			}
		}
		subtree_size++;
	}
};

vector<int> gph[MAXN];
vector<int> dfn;

void dfs(int x){
	dfn.push_back(x);
	for(auto &i : gph[x]){
		gph[i].erase(find(all(gph[i]), x));
		dfs(i);
	}
}

int main(){
	int tc; cin >> tc; while(tc--){
		scanf("%d %d %lld %lld",&n,&k,&l,&r);
		k++;
		vector<lint> a(n);
		for(int i = 0; i < n; i++) scanf("%lld",&a[i]);
		for(int i = 1; i < n; i++){
			int x, y; scanf("%d %d",&x,&y);
			x--; y--;
			gph[x].push_back(y);
			gph[y].push_back(x);
		}
		dfs(0);
		reverse(all(dfn));
		vector<info> dp(n);
		for(auto &v : dfn){
			dp[v].val[0][0] = pi(0, 0);
			dp[v].min_sum[0] = 0;
			for(auto &w : gph[v]) dp[v] = dp[v] + dp[w];
			dp[v].adjust(a[v]);
	//		dp[v].debug();
		}
		for(int i = 1; i <= k; i++){
			if(dp[0].min_sum[i] == 0 && dp[0].val[i][0].first == 0) printf("1");
			else printf("0");
		}
		puts("");
		for(int i = 0; i < n; i++) gph[i].clear();
		dfn.clear();
	}
}