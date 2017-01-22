#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k, q;
int dx[1000005];
int mat[1000005];
int dp[1000005];
int nxt[1000005];

vector<pi> intv;
vector<int> s;

int solve(int x){
	int ret = 0;
	int pos = mat[x], plc;
	auto w = lower_bound(s.begin(), s.end(), x);
	if(w != s.begin()){
		w--;
		if(*w >= intv[pos].first){
			plc = *w;
			pos = nxt[plc];
			ret++;
		}
		else return 1e9;
	}
	else return 1e9;
	if(pos == intv.size()) return ret;
	w = upper_bound(s.begin(), s.end(), intv[pos].second) - 1;
	if(*w == x) return 1e9;
	else return ret + dp[pos];
}

int main(){
	scanf("%d %d %d",&n,&k,&q);
	k = n - k;
	while(q--){
		int s, e;
		char t[5];
		scanf("%d %d %s",&s,&e,t);
		if(*t == 'N') dx[s]++, dx[e+1]--;
		else intv.push_back(pi(s, e));
	}
	sort(intv.begin(), intv.end(), [&](const pi &a, const pi &b){
		return pi(a.first, -a.second) < pi(b.first, -b.second);
	});
	vector<pi> aux = intv;
	intv.clear();
	for(auto &i : aux){
		while(!intv.empty() && intv.back().second >= i.second){
			intv.pop_back();
		}
		intv.push_back(i);
	}
	for(int i=1; i<=n; i++){
		dx[i] += dx[i-1];
		if(!dx[i]) s.push_back(i);
	}
	int p1 = n+1, p2 = intv.size();
	for(int i=n; i; i--){
		while(p2 > 0 && intv[p2-1].first > i) p2--;
		nxt[i] = p2;
	}
	for(int i=(int)intv.size()-1; i>=0; i--){
		while(p1 > intv[i].second || dx[p1]) p1--;
		dp[i] = dp[nxt[p1]] + 1;
	}
	vector<int> v;
	int idx = 0, lst = -1;
	for(auto &i : intv){
		idx++;
		if(lst >= i.first){
			continue;
		}
		lst = *--upper_bound(s.begin(), s.end(), i.second);
		v.push_back(lst);
		mat[lst] = idx-1;
	}
	int pp = 1;
	for(int i=0; i<v.size(); i++){
		if(i + solve(v[i]) > k){
			printf("%d ", v[i]);
			pp = 0;
		}
	}
	if(pp) puts("0");
}
