#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;
const int MAXS = 2500005;
const int MAXC = 26;

struct bit{
	int tree[MAXN];
	void add(int x, int v){
		while(x < MAXN){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

int n, q;
int trie[MAXS][MAXC], piv, piv2;
char buf[MAXS];
string str[MAXN], pfx[MAXN], sfx[MAXN];
int ans[MAXN];

struct sweep{ int s, e, idx, buho; };
vector<sweep> swp[MAXN];
int a[MAXN];

int idx[MAXS], din[MAXS], dout[MAXS];

void dfs(int x){
	din[x] = piv2;
	if(idx[x]) piv2++;
	for(int i=0; i<26; i++){
		if(trie[x][i]){
			dfs(trie[x][i]);
		}
	}
	dout[x] = piv2;
}

vector<pi> get_range_and_labeling(vector<int> &v){
	piv = piv2 = 0;
	memset(trie, 0, sizeof(trie));
	memset(idx, 0, sizeof(idx));
	for(int i=0; i<n; i++){
		int p = 0;
		for(auto &j : str[i]){
			if(!trie[p][j - 'a']){
				trie[p][j - 'a'] = ++piv;
			}
			p = trie[p][j - 'a'];
		}
		idx[p] = i + 1;
	}
	dfs(0);
	for(int i=0; i<=piv; i++){
		if(idx[i]){
			v[idx[i] - 1] = din[i] + 1;
		}
	}
	vector<pi> dap;
	for(int i=0; i<q; i++){
		int p = 0;
		for(auto &j : pfx[i]){
			p = trie[p][j - 'a'];
			if(p == 0) break;
		}
		if(p != 0) dap.emplace_back(din[p], dout[p]);
		else dap.emplace_back(1, 1);
	}
	return dap;
}

int main(){
	scanf("%d %d",&n,&q);
	for(int i=0; i<n; i++){
		scanf("%s", buf);
		str[i] = buf;
	}
	for(int i=0; i<q; i++){
		scanf("%s", buf);
		pfx[i] = buf;
		scanf("%s", buf);
		sfx[i] = buf;
	}
	vector<int> xc(n), yc(n);
	auto rng1 = get_range_and_labeling(xc);
	for(int i=0; i<n; i++){
		reverse(str[i].begin(), str[i].end());
	}
	for(int i=0; i<q; i++){
		pfx[i] = sfx[i];
		reverse(pfx[i].begin(), pfx[i].end());
	}
	auto rng2 = get_range_and_labeling(yc);
	for(int i=0; i<n; i++){
		a[xc[i]] = yc[i];
	}
	for(int i=0; i<q; i++){
		swp[rng1[i].first].push_back({rng2[i].first, rng2[i].second, i, -1});
		swp[rng1[i].second].push_back({rng2[i].first, rng2[i].second, i, +1});
	}
	for(int j=1; j<=n; j++){
		bit.add(a[j], 1);
		for(auto &i : swp[j]){
			ans[i.idx] += i.buho * (bit.query(i.e) - bit.query(i.s));
		}
	}
	for(int i=0; i<q; i++){
		printf("%d\n", ans[i]);
	}
}
