#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

const int MAXN = 200005;

struct manacher{
	int aux[2 * MAXN - 1];
	void solve(int n, char *str, int *ret){
		for(int i=0; i<n; i++){
			aux[2*i] = str[i];
			if(i != n-1) aux[2*i+1] = -1;
		}
		int p = 0, c = 0;
		for(int i=0; i<2*n-1; i++){
			int cur = 0;
			if(i <= p) cur = min(ret[2 * c - i], p - i);
			while(i - cur - 1 >= 0 && i + cur + 1 < 2*n-1 && aux[i-cur-1] == aux[i+cur+1]){
				cur++;
			}
			if(i + cur > p){
				p = i + cur;
				c = i;
			}
			ret[i] = cur;
		}
	}
}manacher;

struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, char *str, int *sfx, int *rev, int *lcp){
		int p = 1;
		memset(ord, 0, sizeof(ord));
		for(int i=0; i<n; i++){
			sfx[i] = i;
			ord[i] = str[i];
		}
		int pnt = 1;
		while(1){
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[min(i+p, n)]]++;
			}
			for(int i=1; i<=n || i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i+p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[i]]++;
			}
			for(int i=1; i<=n || i<=255; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				sfx[--cnt[ord[aux[i]]]] = aux[i];
			}
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
		for(int i=0; i<n; i++){
			rev[sfx[i]] = i;
		}
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
}sfxarray;

struct rmq{
	int tree[530000], lim;
	void init(int n, int *a){
		memset(tree, 0x3f, sizeof(tree));
		for(lim = 1; lim <= n; lim <<= 1);
		for(int i=1; i<=n; i++){
			tree[i+lim] = a[i];
		}
		for(int i=lim; i; i--){
			tree[i] = min(tree[2*i], tree[2*i+1]);
		}
	}
	int query(int s, int e){
		s += lim;
		e += lim;
		int ret = 1e9;
		while(s < e){
			if(s%2 == 1) ret = min(ret, tree[s++]);
			if(e%2 == 0) ret = min(ret, tree[e--]);
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret = min(ret, tree[s]);
		return ret;
	}
}rmq;

int n;
char str[100005], con[200005];
int dp[200005], sfx[200005], rev[200005], lcp[200005];
lint kill[100005];

struct qry{
	int p1, p2, v;
	bool operator<(const qry &q)const{
		return pi(p1, p2) < pi(q.p1, q.p2);
	}
};

vector<qry> v;

int query(int s, int e){
	if(s < 0 || e < 0 || s >= n || e >= n) return 0;
	e = 2 * n - e;
	s = rev[s], e = rev[e];
	if(s > e) swap(s, e);
	return rmq.query(s+1, e);
}

lint solve(int s, int e){
	int pos = v[s].p1;
	lint ret = -kill[pos] + 1 + dp[pos * 2] / 2;
	for(int j=s; j<=e; j++){
		if(v[j].v < 2*pos){
			ret += 1 + query(pos + 1, v[j].v - pos - 1);
		}
		else{
			ret += 1 + query(v[j].v - pos + 1, pos - 1);
		}
	}
	return ret;
}

lint dx1[100005], dx2[100005];

int main(){
	cin >> str;
	n = strlen(str);
	con[n] = '#';
	for(int i=0; i<n; i++){
		con[i] = con[2*n-i] = str[i];
	}
	manacher.solve(n, str, dp);
	sfxarray.solve(2*n+1, con, sfx, rev, lcp);
	rmq.init(2*n+1, lcp);
	lint ret = 0;
	for(int i=0; i<n; i++){
		int d = dp[2*i] / 2;
		ret += d + 1;
		dx1[i-d] += d + 1 - i;
		dx1[i+1] -= d + 1 - i;
		dx1[i+1] += d + 1 + i;
		dx1[i+d+1] -= d + 1 + i;
		dx2[i-d] += 1;
		dx2[i+1] -= 1;
		dx2[i+1] -= 1;
		dx2[i+d+1] += 1;
		/*for(int j=i-d; j<=i; j++){
			kill[j] += d + 1 - (i - j);
		}
		for(int j=i+1; j<=i+d; j++){
			kill[j] += d + 1 - (j - i);
		}*/
		if(i+d+1 < n && i-d-1 >= 0){
			v.push_back({i+d+1, str[i-d-1] - 'a', 2*i});
			v.push_back({i-d-1, str[i+d+1] - 'a', 2*i});
		}
	}
	for(int i=1; i<n; i++){
		int d = (1 + dp[2*i-1]) / 2;
		ret += d;
		dx1[i-d] += d+1-i;
		dx1[i] -= d+1-i;
		dx1[i] += d+i;
		dx1[i+d] -= d+i;
		dx2[i-d] += 1;
		dx2[i] -= 1;
		dx2[i] -= 1;
		dx2[i+d] += 1;
		/*for(int j=i-d; j<i; j++){
			kill[j] += d + 1 - (i - j);
		}
		for(int j=i; j<i+d; j++){
			kill[j] += d - (j - i);
		}*/
		if(i - d - 1 >= 0 && i + d < n){
			v.push_back({i+d, str[i-d-1] - 'a', 2*i-1});
			v.push_back({i-d-1, str[i+d] - 'a', 2*i-1});
		}
	}
	for(int i=1; i<n; i++){
		dx1[i] += dx1[i-1];
		dx2[i] += dx2[i-1];
	}
	for(int i=0; i<n; i++){
		kill[i] = dx1[i] + i * dx2[i];
	}
	sort(v.begin(), v.end());
	lint add = 0;
	for(int i=0; i<v.size(); ){
		int e = i;
		while(e < v.size() && pi(v[i].p1, v[i].p2) == pi(v[e].p1, v[e].p2)) e++;
		if(str[v[i].p1] != v[i].p2 + 'a') add = max(add, solve(i, e-1));
		i = e;
	}
	cout << ret + add;
}
