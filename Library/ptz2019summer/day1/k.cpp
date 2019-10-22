#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())

vector<int> ord;
vector<int> gph[MAXN];

void dfs(int x){
	ord.push_back(x);
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
}

struct node{
	int mode;
	lint first, second;
	bool operator<(const node &n)const{
		if(mode != n.mode) return mode > n.mode; // node increasing
		if(mode == 0) return first > n.first; // first increasing
		if(mode == 1) return second < n.second; // second decreasing
		assert(0);
	}
}a[MAXN];

bool useless(node a, node b){
	if(a.mode == 1 && b.mode == 0) return 1;
	if(a.mode == 0 && b.mode == 1) return 0;
	if(a.mode == 0) return a.second >= b.first;
	if(a.mode == 1) return b.first >= a.second;
}

node merge(node a, node b){
	if(a.mode == 1 && b.mode == 0){
		if(a.second > b.first){
			a.second += b.second - b.first;
			if(a.first > a.second) a.mode = 1;
			else a.mode = 0;
			return a;
		}
		else{
			b.first += a.first - a.second;
			if(b.first > b.second) b.mode = 1;
			else b.mode = 0;
			return b;
		}
	}
	if(a.mode == 0) return (node){a.mode, a.first, a.second - b.first + b.second}; 
	else return (node){b.mode, a.first + b.first - a.second, b.second};
}

int main(){
	int t; cin >> t;
	while(t--){
		int n; scanf("%d",&n);
		ord.clear();
		for(int i=1; i<n; i++){
			scanf("%lld %lld",&a[i].first,&a[i].second);
			a[i].mode = (a[i].first > a[i].second);
		}
		for(int i=1; i<n; i++){
			int s, e; scanf("%d %d",&s,&e);
			s--, e--;
			gph[s].push_back(e);
			gph[e].push_back(s);
		}
		dfs(0);
		reverse(ord.begin(), ord.end());
		vector<int> idx(n);
		iota(idx.begin(), idx.end(), 0);
		vector<priority_queue<node>> pq(n);
		for(auto &i : ord){
			pi nxt = pi(-1, -1);
			for(auto &j : gph[i]){
				auto enq = a[j];
				while(sz(pq[idx[j]]) && useless(enq, pq[idx[j]].top())){
					enq = merge(enq, pq[idx[j]].top());
					pq[idx[j]].pop();
				}
				pq[idx[j]].push(enq);
				nxt = max(nxt, pi(sz(pq[idx[j]]), idx[j]));
			}
			if(nxt.second != -1) idx[i] = nxt.second;
			for(auto &j : gph[i]){
				if(idx[j] != idx[i]){
					while(sz(pq[idx[j]])){
						pq[idx[i]].push(pq[idx[j]].top());
						pq[idx[j]].pop();
					}
				}
			}
		}
		lint ret = 0, sum = 0;
		while(sz(pq[idx[0]])){
			auto t = pq[idx[0]].top();
			pq[idx[0]].pop();
			sum += t.first;
			ret = max(ret, sum);
			sum -= t.second;
			ret = max(ret, sum);
		}
		printf("%lld\n", ret);
		for(int i=0; i<n; i++) gph[i].clear();
	}
}
