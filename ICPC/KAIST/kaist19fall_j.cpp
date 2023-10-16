#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
using namespace std;
const int MAXN = 250005;
using pi = pair<int, int>;
using lint = long long;

struct intv{
	int s, e, x;
	bool operator<(const intv &i)const{
		return pi(s, -e) < pi(i.s, -i.e);
	}
};

vector<int> gph[MAXN];
int n, a[MAXN];

priority_queue<lint> pq[MAXN];
int idx[MAXN];

void solve(){
	iota(idx, idx + n, 0);
	for(int i=n-1; i>=0; i--){
		if(sz(gph[i])){
			pi ret(-1, -1);
			for(auto &j : gph[i]){
				ret = max(ret, pi(sz(pq[idx[j]]), j));
			}
			idx[i] = idx[ret.second];
			for(auto &j : gph[i]){
				if(j == ret.second) continue;
				vector<lint> v;
				while(!pq[idx[j]].empty()){
					v.push_back(pq[idx[i]].top());
					pq[idx[i]].pop();
					v.back() += pq[idx[j]].top();
					pq[idx[j]].pop();
				}
				for(auto &j : v) pq[idx[i]].push(j);
			}
		}
		pq[idx[i]].push(a[i]);
	}
	lint dap = 0;
	for(int i=0; i<n-1; i++){
		if(sz(pq[idx[0]])){
			dap += pq[idx[0]].top();
			pq[idx[0]].pop();
		}
		printf("%lld ", dap);
	}
}

int main(){
	vector<intv> v;
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		int s, e, x; scanf("%d %d %d",&s,&e,&x);
		v.push_back({s, e, x});
	}
	n++;
	v.push_back({1, 1000001, 0});
	sort(v.begin(), v.end());
	vector<int> stk;
	for(int i=0; i<sz(v); i++){
		while(sz(stk) && v[stk.back()].e < v[i].e){
			stk.pop_back();
		}
		if(sz(stk)){
			gph[stk.back()].push_back(i);
		}
		stk.push_back(i);
		a[i] = v[i].x;
	}
	solve();
}
