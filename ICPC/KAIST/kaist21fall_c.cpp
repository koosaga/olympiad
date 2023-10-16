#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
const int MAXN = 500005;
const lint mod[2] = {int(1e9) + 7, int(1e9) + 9};

struct edg{
	int s, e, x;
	bool operator<(const edg &e)const{
		return x > e.x;
	}
};

struct disj{
	lint hsh[MAXN];
	int pa[MAXN];
	void init(int n, lint *h){
		iota(pa, pa + n + 1, 0);
		for(int i = 1; i <= n; i++) hsh[i] = h[i];
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	lint uni(int p, int q, int v){
		p = find(p);
		q = find(q);
		if(p == q) return 0;
		lint hshv = hsh[p] * hsh[q] % mod[v];
		pa[q] = p;
		hsh[p] = (hsh[p] + hsh[q]) % mod[v];
		return hshv;
	}
}disj;

lint hv[2][MAXN];

mt19937 rng(0x14004);
int randint(int lb, int ub){ return uniform_int_distribution<int>(lb, ub)(rng); }


vector<int> solve(vector<edg> e, int m){
	disj.init(sz(e) + 1, hv[m]);
	vector<int> v;
	for(int i = 0; i < sz(e); ){
		int j = i;
		while(j < sz(e) && e[j].x == e[i].x) j++;
		lint ret = 0;
		for(int k = i; k < j; k++){
			ret += disj.uni(e[k].s, e[k].e, m);
			if(ret >= mod[m]) ret -= mod[m];
		}
		v.push_back(e[i].x);
		v.push_back(ret);
		i = j;
	}
	return v;
}

int main(){
	int d, n;
	scanf("%d %d",&d,&n);
	for(int i = 1; i <= n; i++){
		hv[0][i] = randint(1, mod[0] - 1);
		hv[1][i] = randint(1, mod[1] - 1);
	}

	map<vector<int>, int> mp;
	for(int i = 0; i < d; i++){
		vector<edg> ed(n - 1);
		for(auto &i : ed) scanf("%d %d %d",&i.s,&i.e,&i.x);
		sort(all(ed));
		vector<int> hsh1 = solve(ed, 0);
		vector<int> hsh2 = solve(ed, 1);
		for(auto &i : hsh2) hsh1.push_back(i);
		if(mp.find(hsh1) == mp.end()) mp[hsh1] = i + 1;
		printf("%d ", mp[hsh1]);
	}
}
