#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 200005;

void color(vector<int> v, vector<int> &w, int d = 1){
	if(!sz(v)) return;
	vector<pi> rev;
	for(int i = 0; i < sz(v); i++){
		rev.emplace_back(v[i], i);
	}
	sort(all(rev));
	vector<int> l(sz(rev)), r(sz(rev));
	{
		vector<int> stk;
		for(int i = 0; i < sz(v); i++){
			int x = rev[i].first, y = rev[i].second;
			while(sz(stk) && rev[stk.back()].second > y) stk.pop_back();
			if(!sz(stk)) l[y] = -1;
			else l[y] = rev[stk.back()].second;
			stk.push_back(i);
		}
		stk.clear();
		for(int i = sz(v) - 1; i >= 0; i--){
			int x = rev[i].first, y = rev[i].second;
			while(sz(stk) && rev[stk.back()].second > y) stk.pop_back();
			if(!sz(stk)) r[y] = -1;
			else r[y] = rev[stk.back()].second;
			stk.push_back(i);
		}
	}
	vector<int> rec;
	vector<int> skip(sz(rev));
	for(int i = sz(v) - 1; i >= 0; i--){
		if(!skip[i]){
			w[v[i]] = d;
			if(~l[i]) skip[l[i]] = 1;
			if(~r[i]) skip[r[i]] = 1;
		}
		else rec.push_back(v[i]);
	}
	reverse(all(rec));
	color(rec, w, d + 1);
}

void solve(){
	int n; scanf("%d",&n);
	vector<int> p(n), ret(n);
	for(auto &i : p) scanf("%d",&i), i--;
	color(p, ret);
	for(auto &i : ret) printf("%d ", i);
	puts("");
}

int main(){
	int tc; scanf("%d",&tc);
	for(int i=1; i<=tc; i++){
		solve();
	}
}


