#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<lint, lint>;

int N;
const int MAX_N = 2000010;
const lint INF = (lint)(1e18);

lint F[MAX_N], C[MAX_N], L[MAX_N];
lint dp[MAX_N];

void input(){
    scanf("%d",&N);
    for(int i=1;i<=N;i++){
        scanf("%lld",&F[i]);
    }
    for(int i=1;i<=N;i++){
        scanf("%lld",&C[i]);
    }
    for(int i=1;i<=N;i++){
        scanf("%lld",&L[i]);
    }
}

struct cht{
	vector<pi> line;
	bool bad(pi x, pi y, pi z){
		return (double)(x.second - y.second) * (z.first - y.first) <
			(double)(y.second - z.second) * (y.first - x.first);
	}
	void add(pi v){
		if(!line.empty() && line.back().first == v.first){
			if(line.back().second < v.second) line.pop_back();
			else return;
		}
		while(line.size() >= 2 && bad(line[line.size()-2], line.back(), v)){
			line.pop_back();
		}
		line.push_back(v);
	}
	void clear(){ line.clear(); }
	lint query(lint x){
		if(line.empty()) return -INF;
		int s = 0, e = line.size()-1;
		while(s != e){
			int m = (s+e)/2;
			if(line[m].first * x + line[m].second < line[m+1].first * x + line[m+1].second){
				s = m+1;
			}
			else e = m;
		}
		return line[s].first * x + line[s].second;
	}
}cht;

void solve(int s, int e){
	if(s == e) return;
	int m = (s+e)/2;
	solve(s, m);
	vector<pi> v, w;
	for(int i=s; i<=m; i++) v.push_back(pi(F[i + 1] + i + 1, i));
	for(int i=m+1; i<=e; i++) w.push_back(pi(L[i] + i, i));
	sort(v.begin(), v.end());
	sort(w.begin(), w.end());
	vector<pi> cand;
	int ptr = v.size();
	for(int i=w.size()-1; i>=0; i--){
		while(ptr > 0 && v[ptr-1].first >= w[i].first){
			lint x = v[ptr-1].first;
			lint y = dp[v[ptr-1].second];
			cht.add(pi(x, y));
			ptr--;
		}
		lint qres = cht.query(C[w[i].second]) - C[w[i].second] * w[i].second;
		dp[w[i].second] = max(dp[w[i].second], qres);
	}
	cht.clear();
	solve(m+1, e);
}

void solve(){
	fill(dp + 1, dp + N + 1, -INF);
	solve(0, N);
    if(dp[N] < -1e17){
        puts("Impossible");
    }else{
        printf("%lld\n",dp[N]);
    }
}

int main(){
    input();
    solve();
    return 0;
}


