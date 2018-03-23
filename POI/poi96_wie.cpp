#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 3005;

int n;
pi a[MAXN], b[MAXN];
int ans1[MAXN], ans2[MAXN];

void solve(int *ans, pi *c){
	vector<int> cnt[MAXN];
	for(int i=0; i<n; i++) cnt[c[i].first].push_back(i);
	priority_queue<pi, vector<pi>, greater<pi> > pq;
	for(int i=1; i<=n; i++){
		for(auto &j : cnt[i]){
			pq.push(pi(c[j].second, j));
		}
		if(pq.empty() || pq.top().first < i){
			puts("NIE");
			exit(0);
		}
		ans[pq.top().second] = i;
		pq.pop();
	}
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].first >> b[i].first >> a[i].second >> b[i].second;
	}
	solve(ans1, a);
	solve(ans2, b);
	for(int i=0; i<n; i++) printf("%d %d\n", ans1[i], ans2[i]);
}

