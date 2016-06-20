#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;
const int mod = 1e9 + 9;

int n, m;

int pfx_trie[2000005][4], pp;
int sfx_trie[2000005][4], sp;
int ordp[2000005], ords[2000005], szp[2000005], szs[2000005];

string s[100005];
int gt[256];
int dfn1[100005], dfn2[100005];

int piv;

void dfs1(int x){
	ordp[x] = ++piv;
	szp[x] = 1;
	for(int i=0; i<4; i++){
		if(pfx_trie[x][i]){
			dfs1(pfx_trie[x][i]);
			szp[x] += szp[pfx_trie[x][i]];
		}
	}
}

void dfs2(int x){
	ords[x] = ++piv;
	szs[x] = 1;
	for(int i=0; i<4; i++){
		if(sfx_trie[x][i]){
			dfs2(sfx_trie[x][i]);
			szs[x] += szs[sfx_trie[x][i]];
		}
	}
}

string pfx, sfx;

int getp(int x, int y){
	if(pfx.size() == x) return y;
	if(x != 0 && y == 0) return 0;
	getp(x+1, pfx_trie[y][gt[pfx[x]]]);
}

int gets(int x, int y){
	if(sfx.size() == x) return y;
	if(x != 0 && y == 0) return 0;
	gets(x+1, sfx_trie[y][gt[sfx[x]]]);
}

struct seg{
	int lim;
	vector<int> vx;
	vector<int> tree[270000];
	void init(int n, pi *a){
		sort(a, a+n, [&](const pi &a, const pi &b){
			return a.second < b.second;
		});
		for(int i=0; i<n; i++){
			vx.push_back(a[i].first);
		}
		sort(vx.begin(), vx.end());
		vx.erase(unique(vx.begin(), vx.end()), vx.end());
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=0; i<n; i++){
			int p = lower_bound(vx.begin(), vx.end(), a[i].first) - vx.begin();
			p += lim;
			while(p >= 1){
				tree[p].push_back(a[i].second);
				p >>= 1;
			}
		}
	}
	int query(int sx, int ex, int sy, int ey){
		int lw = lower_bound(vx.begin(), vx.end(), sx) - vx.begin();
		int hw = upper_bound(vx.begin(), vx.end(), ex) - vx.begin() - 1;
		lw += lim;
		hw += lim;
		auto func = [&](int x, int s, int e){
			return upper_bound(tree[x].begin(), tree[x].end(), e) -
			lower_bound(tree[x].begin(), tree[x].end(), s);
		};
		int ret = 0;
		while(lw < hw){
			if(lw%2 == 1){
				ret += func(lw++, sy, ey);
			}
			if(hw%2 == 0){
				ret += func(hw--, sy, ey);
			}
			lw >>= 1;
			hw >>= 1;
		}
		if(lw == hw) ret += func(lw, sy, ey);
		return ret;
	}
}seg;

vector<int> vx;


int main(){
	gt['A'] = 0; gt['C'] = 1, gt['G'] = 2, gt['U'] = 3;
	cin >> n >> m;
	for(int i=0; i<n; i++){
		cin >> s[i];
		int pt = 0;
		for(auto &j : s[i]){
			if(!pfx_trie[pt][gt[j]]){
				pfx_trie[pt][gt[j]] = ++pp;
			}
			pt = pfx_trie[pt][gt[j]];
		}
		dfn1[i] = pt;
		pt = 0;
		reverse(s[i].begin(), s[i].end());
		for(auto &j : s[i]){
			if(!sfx_trie[pt][gt[j]]){
				sfx_trie[pt][gt[j]] = ++sp;
			}
			pt = sfx_trie[pt][gt[j]];
		}
		dfn2[i] = pt;
	}
	dfs1(0);
	piv = 0;
	dfs2(0);
	piv = 0;
	pi a[100005];
	for(int i=0; i<n; i++){
		a[i] = pi(ordp[dfn1[i]], ords[dfn2[i]]);
	}
	seg.init(n, a);
	for(int i=0; i<m; i++){
		cin >> pfx >> sfx;
		reverse(sfx.begin(), sfx.end());
		int p = getp(0,0), q = gets(0,0);
		if(p == 0 || q == 0){
			puts("0");
			continue;
		}
		printf("%d\n",seg.query(ordp[p], ordp[p] + szp[p] - 1,
		ords[q], ords[q] + szs[q] - 1));
	}
}

