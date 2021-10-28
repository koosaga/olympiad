#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

int n, q, a[MAXN];
int whomax[800][800];
int cnt[MAXN];

vector<int> w[MAXN];

pi count(int l, int r, int x){
	return pi(upper_bound(all(w[x]), r) - lower_bound(all(w[x]), l), x);
}

int query(int l, int r){
	int ll = l, rr = r;
	pi ret(-1, -1);
	while((l&127) != 0 && l <= r){
		ret = max(ret, count(ll, rr, a[l++]));
	}
	while((r&127) != 127 && l <= r){
		ret = max(ret, count(ll, rr, a[r--]));
	}
	if(l <= r) ret = max(ret, count(ll, rr, whomax[l >> 7][r >> 7]));
	return ret.second;
}

int main(){
	vector<int> v;
	scanf("%d %d",&n,&q);
	for(int i = 0; i < n; i++){
		scanf("%d",&a[i]);
		v.push_back(a[i]);
	}
	{
		sort(all(v)); v.resize(unique(all(v)) - v.begin());
		for(int i = 0; i < n; i++){
			a[i] = lower_bound(all(v), a[i]) - v.begin();
			w[a[i]].push_back(i);
		}
	}
	for(int i = 0; i < n; i += 128){
		memset(cnt, 0, sizeof(cnt)); 
		pi mx(-1, -1);
		for(int j = i; j < n; j++){
			cnt[a[j]]++;
			mx = max(mx, pi(cnt[a[j]], a[j]));
			if((j&127) == 127) whomax[i >> 7][j >> 7] = mx.second;
		}
	}
	while(q--){
		int l, r; scanf("%d %d",&l,&r);
		l--; r--;
		printf("%d\n", v[query(l, r)]);
	}
}
