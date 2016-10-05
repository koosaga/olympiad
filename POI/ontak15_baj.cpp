#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod1 = 1e9 + 409;
const int mod2 = 1e9 + 433;

int col[5005][205];
int n, m, d;

unordered_map<lint, int> mp;
int ret;

lint pw1[205], hs1[5005];
lint pw2[205], hs2[5005];

void update(int x, int d, int g){
	lint dx = g - col[x][d];
	col[x][d] = g;
	lint v = hs1[x] * mod2 + hs2[x];
	ret -= mp[v] * 2;
	mp[v]--;
	hs1[x] += dx * pw1[d-1];
	hs2[x] += dx * pw2[d-1];
	hs1[x] %= mod1;
	hs2[x] %= mod2;
	hs1[x] += mod1;
	hs2[x] += mod2;
	hs1[x] %= mod1;
	hs2[x] %= mod2;
	lint w = hs1[x] * mod2 + hs2[x];
	mp[w]++;
	ret += mp[w] * 2;
}

struct disj{
	int pa[5005], d;
	vector<int> elem[5005];
	void init(int n, int _d){
		d = _d;
		for(int i=1; i<=n; i++){
			elem[i].push_back(i);
			pa[i] = i;
			col[i][d] = i;
		}
	}
	void uni(int p, int q){
		p = pa[p];
		q = pa[q];
		if(p == q) return;
		if(elem[p].size() > elem[q].size()) swap(p, q);
		for(auto &i : elem[p]){
			pa[i] = q;
			update(i, d, q);
			elem[q].push_back(i);
		}
	}
}disj[205];

int main(){
	cin >> d >> n >> m;
	pw1[0] = pw2[0] = 1;
	for(int i=1; i<=d; i++){
		disj[i].init(n, i);
		pw1[i] = pw1[i-1] * 10007 % mod1;
		pw2[i] = pw2[i-1] * 10007 % mod2;
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=d; j++){
			hs1[i] = hs1[i] * 10007 + col[i][j];
			hs1[i] %= mod1;
			hs2[i] = hs2[i] * 10007 + col[i][j];
			hs2[i] %= mod2;
		}
		lint v = hs1[i] * mod2 + hs2[i];
		mp[v]++;
		ret++;
	}
	for(int i=1; i<=m; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		disj[x].uni(s, e);
		printf("%d\n", ret);
	}
}
