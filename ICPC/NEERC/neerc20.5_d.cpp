#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 105;
using lint = long long;

int n, k;
vector<int> v[10];
lint dp[10][10];
pi trk[10][10];
vector<int> ans;

void report(vector<int> ans){
	int m = 1;
	for(auto &i : ans){
		m = m * i % 10;
	}
	if(m != k || sz(ans) == 0){
		puts("-1");
	}
	else{
		printf("%d\n", sz(ans));
		for(auto &i : ans) printf("%d ", i);
	}
	exit(0);
}

lint fuck = 1e18;
vector<int> cnd, opt;

void dfs(int m, vector<int> trk, int cnt, int pos = 0, int curdap = 1){
	if(pos == sz(cnd)){
		if(m == k && fuck > curdap){
			fuck = curdap;
			opt = trk;
		}
		return;
	}
	trk.push_back(cnd[pos]);
	dfs(m * cnd[pos] % 10, trk, cnt, pos + 1, curdap);
	trk.pop_back();
	if(cnt < 3){
		dfs(m, trk, cnt + 1, pos + 1, curdap * cnd[pos]);
	}
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i = 0; i < n; i++){
		int x; scanf("%d",&x);
		v[x % 10].push_back(x);
	}
	if(k == 0){
		for(int y = 0; y < 10; y += 1){
			for(auto &qq : v[y]) ans.push_back(qq);
		}
		report(ans);
	}
	if(k == 5){
		for(int y = 1; y < 10; y += 2){
			for(auto &qq : v[y]) ans.push_back(qq);
		}
		report(ans);
	}
	if(k % 2 == 1){
		for(int y = 0; y < 10; y += 2) v[y].clear();
	}
	v[5].clear();
	v[0].clear();
	for(auto &y : v[1]){
		ans.push_back(y);
	}
	v[1].clear();
	vector<int> tomult;
	int cur_mult = 1;
	for(int y = 2; y < 10; y++){
		sort(all(v[y]));
		for(int j = 0; j < sz(v[y]) && j < 3; j++){
			cnd.push_back(v[y][j]);
		}
		for(int j = 3; j < sz(v[y]); j++){
			cur_mult *= y;
			cur_mult %= 10;
			ans.push_back(v[y][j]);
		}
	}
	dfs(cur_mult, tomult, 0);
	for(auto &i : opt) ans.push_back(i);
	report(ans);
}
