#include <bits/stdc++.h>
using namespace std;
const int MAXN = 500005;
using pi = pair<int, int>;
using lint = long long;
using pque = priority_queue<pi, vector<pi>, greater<pi> >;

int n;
int a[MAXN][2];

pque freeQ[2], revokeQ[2];

int used[MAXN];

int main(){
	scanf("%d",&n);
	for(int i=0; i<2*n; i++){
		scanf("%d %d",&a[i][0], &a[i][1]);
		freeQ[0].emplace(a[i][0], i);
		freeQ[1].emplace(a[i][1], i);
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		auto sanitize = [&](){
			while(!freeQ[0].empty() && used[freeQ[0].top().second]) freeQ[0].pop();
			while(!freeQ[1].empty() && used[freeQ[1].top().second]) freeQ[1].pop();
		};
		auto value = [&](int p){
			sanitize();
			int ret = freeQ[p].top().first;
			if(revokeQ[p ^ 1].size() && freeQ[p ^ 1].size()){
				ret = min(ret, revokeQ[p ^ 1].top().first + freeQ[p ^ 1].top().first);
			}
			return ret;
		};
		auto consume = [&](int p){
			sanitize();
			if(revokeQ[p ^ 1].size() && freeQ[p ^ 1].size() &&
				revokeQ[p ^ 1].top().first + freeQ[p ^ 1].top().first < freeQ[p].top().first){
				int idx = freeQ[p ^ 1].top().second;
				int idx2 = revokeQ[p ^ 1].top().second;
				ret += freeQ[p ^ 1].top().first;
				ret += revokeQ[p ^ 1].top().first;
				revokeQ[p ^ 1].pop();
				used[idx] = 1;
				revokeQ[p ^ 1].emplace(a[idx][p] - a[idx][p^1], idx);
				revokeQ[p].emplace(a[idx2][p^1] - a[idx2][p], idx2);
			}
			else{
				int idx = freeQ[p].top().second;
				ret += freeQ[p].top().first;
				used[idx] = 1;
				revokeQ[p].emplace(a[idx][p^1] - a[idx][p], idx);
			}
		};
		if(value(0) < value(1)) consume(0), consume(1);
		else consume(1), consume(0);
		printf("%lld\n", ret);
	}
}
