#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2000005;
using lint = long long;

int n, d, t, a[MAXN];
vector<int> gph[MAXN];
int cnt[MAXN];

int dfs(int x){
	vector<int> ans;
	for(auto &y : gph[x]){
		ans.push_back(dfs(y));
	}
	if(sz(ans) == 0) return 1;
	swap(ans[0], *max_element(all(ans)));
	for(int i = 1; i < sz(ans); i++) cnt[ans[i]]++;
	return ans[0] + 1;
}

int main(){
	scanf("%d %d %d",&n,&d,&t);
	int ans = 0;
	priority_queue<pi> pq;
	vector<pi> v;
	for(int i = 1; i <= n; i++){
		scanf("%d",&a[i]);
		if(t >= a[i]){
			pq.emplace(i, t - a[i] + i + 1);
		}
		else{
			while(sz(pq) && pq.top().second <= i) pq.pop();
			if(sz(pq)) v.emplace_back(pq.top().first, i - 1);
			else ans++;
		}
	}
	vector<int> stk;
	for(int i = sz(v) - 1; i >= 0; i--){
		while(sz(stk) && v[stk.back()].first > v[i].second) stk.pop_back();
		if(sz(stk)) gph[stk.back()].push_back(i);
		else gph[sz(v)].push_back(i);
		stk.push_back(i);
	}
	ans += dfs(sz(v)) - 1;d--;
	for(int i = n; i; i--){
		int e = min(cnt[i], d);
		d -= e;
		ans += e * i;
	}
	cout << n - ans << endl;
}
