#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 2505;

int n, k;

struct edge{
	int s, e, x;
};

lint dp[MAXN];
vector<pi> gph[MAXN];

int main(){
	scanf("%d %d",&n,&k);
	vector<edge> a(n);
	vector<int> v;
	lint tot = 0;
	for(auto &i : a){
		scanf("%d %d %d",&i.s,&i.e,&i.x);
		v.push_back(i.s);
		tot += i.x;
	}
	sort(all(v));
	v.resize(unique(all(v)) - v.begin());
	for(auto &i : a){
		i.s = lower_bound(all(v), i.s) - v.begin();
		i.e = upper_bound(all(v), i.e) - v.begin() - 1;
		gph[i.s].emplace_back(i.e, i.x);
	}
	for(int i = 0; i < sz(v); i++) sort(all(gph[i]));
	for(int i = 1; i <= sz(v); i++){
		lint sum = 0;
		priority_queue<lint, vector<lint>, greater<lint>> pq;
		for(int j = i-1; j >= 0; j--){
			for(auto &[e, x] : gph[j]){
				if(e >= i) continue;
				pq.push(x);
				sum += x;
			}
			while(sz(pq) > k){
				sum -= pq.top(); pq.pop();
			}
			dp[i] = max(dp[i], dp[j] + sum);
		}
	}
	cout << tot - dp[sz(v)] << endl;
}
