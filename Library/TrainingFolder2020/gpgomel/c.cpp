#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 200005;
const int MAXT = 270000;

namespace sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(int) * (n + 2));
		memset(nord, 0, sizeof(int) * (n + 2));
		memset(sfx, 0, sizeof(int) * (n + 2));
		memset(cnt, 0, sizeof(int) * max(n + 2, 256));

		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(1){
			memset(cnt, 0, sizeof(int) * max(n + 2, 256));
			for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				aux[--cnt[ord[min(i+p, n)]]] = i;
			memset(cnt, 0, sizeof(int) * max(n + 2, 256));
			for(int i=0; i<n; i++) cnt[ord[i]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			if(pnt == n) break;
			pnt = 1;
			nord[sfx[0]] = 1;
			for(int i=1; i<n; i++){
				if(ord[sfx[i-1]] != ord[sfx[i]] || ord[sfx[i-1] + p] != ord[sfx[i] + p]){
					pnt++;
				}
				nord[sfx[i]] = pnt;
			}
			memcpy(ord, nord, sizeof(int) * n);
			p *= 2;
		}
		for(int i=0; i<n; i++) rev[sfx[i]] = i;
		int h = 0;
		for(int i=0; i<n; i++){
			if(rev[i]){
				int prv = sfx[rev[i] - 1];
				while(str[prv + h] == str[i + h]) h++;
				lcp[rev[i]] = h;
			}
			h = max(h-1, 0);
		}
	}
}

struct seg{
	pi tree[MAXT];
	int lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, pi(1e9, 1e9));
	}
	void upd(int x, int v){
		tree[x + lim] = pi(v, x);
		x += lim;
		while(x > 1){
			x >>= 1;
			tree[x] = min(tree[2*x], tree[2*x+1]);
		}
	}
	pi query(int s, int e){
		s += lim;
		e += lim;
		pi ret(1e9,1e9);
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}seg;

int n, m;
char s[MAXN], t[MAXN];
char str[MAXN];
int sfx[MAXN], rev[MAXN], lcp[20][MAXN], lg[MAXN];
lint ret;

int getlcp(int s, int t){
	if(s > t) swap(s, t);
	int l = lg[t - s];
	return min(lcp[l][s + (1<<l)], lcp[l][t]);
}

int solve(int s, int e, int x, vector<int> &pos){
	if(s == e){
		int md = n + m - sfx[pos[s]];
		int up_len = m;
		int delta = min(up_len, md - x);
		ret += delta;
		return up_len - delta;
	}
	int mp, md;
	tie(md, mp) = seg.query(s + 1, e);
	int up_len = max({0, solve(s, mp - 1, md, pos), solve(mp, e, md, pos)});
	int delta = min(up_len, md - x);
	ret += delta;
	return up_len - delta;
}

int main(){
	int p = 0;
	for(int i=1; i<MAXN; i++){
		while((2 << p) <= i) p++;
		lg[i] = p;
	}
	int tc; scanf("%d",&tc);
	while(tc--){
		scanf("%s %s",s,t);
		n = strlen(s);
		m = strlen(t);
		for(int i=0; i<n; i++) str[i] = s[i];
		for(int i=0; i<m; i++) str[n+i] = t[i];
		str[n + m] = 0;
		sfxarray::solve(n+m, str, sfx, rev, lcp[0]);
		for(int i=1; i<20; i++){
			for(int j=1; j<=n+m-1; j++){
				lcp[i][j] = lcp[i-1][j];
				if(j > (1<<(i-1))) lcp[i][j] = min(lcp[i][j], lcp[i-1][j - (1<<(i-1))]);
			}
		}
		vector<int> pos;
		for(int i=0; i<n; i++) pos.push_back(rev[i]);
		sort(all(pos));
		seg.init(sz(pos));
		for(int i=1; i<sz(pos); i++){
			seg.upd(i, getlcp(pos[i-1], pos[i]));
		}
		ret = 0;
		solve(0, sz(pos) - 1, 0, pos);
		printf("%lld\n", ret);
	}
}
