#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using vect = bitset<100>;
using pi = pair<int, int>;
const int MAXN = 500005;

namespace sfxarray{
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
			for(int i=0; i<n; i++) cnt[ord[min(i+p, n)]]++;
			for(int i=1; i<=n || i<=255; i++) cnt[i] += cnt[i-1];
			for(int i=n-1; i>=0; i--)
				aux[--cnt[ord[min(i+p, n)]]] = i;
			memset(cnt, 0, sizeof(cnt));
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

int n, lg[MAXN];
int che[MAXN];
char str[MAXN];
int sfx[MAXN], rev[MAXN], lcp[20][MAXN];

int getlcp(int s, int e){
	s = rev[s]; e = rev[e];
	if(s > e) swap(s, e);
	int l = lg[e - s];
	return min(lcp[l][s + (1<<l)], lcp[l][e]);
}

vector<int> factorize(int x){
	vector<int> v;
	while(x > 1){
		v.push_back(che[x]);
		x /= che[x];
	}
	return v;
}


static char buf[1 << 19]; // size : any number geq than 1024
static int idx = 0;
static int bytes = 0;
static inline int _read() {
	if (!bytes || idx == bytes) {
		bytes = (int)fread(buf, sizeof(buf[0]), sizeof(buf), stdin);
		idx = 0;
	}
	return buf[idx++];
}
static inline int _readInt() {
	int x = 0, s = 1;
	int c = _read();
	while (c <= 32) c = _read();
	if (c == '-') s = -1, c = _read();
	while (c > 32) x = 10 * x + (c - '0'), c = _read();
	if (s < 0) x = -x;
	return x;
}

void haja(char *s){
	int p = 0;
	char c;
	while(isalpha(c = _read())){
		s[p++] = c;
	}
}

int main(){
	int p = 0;
	for(int i=2; i<MAXN; i++){
		while((2 << p) <= i) p++;
		lg[i] = p;
		for(int j=i; j<MAXN; j+=i){
			if(!che[j]) che[j] = i;
		}
	}
	int q;
	n = _readInt();
	haja(str);
	q = _readInt();
	sfxarray::solve(n, str, sfx, rev, lcp[0]);
	for(int i=1; i<20; i++){
		for(int j=1; j<n; j++){
			lcp[i][j] = lcp[i-1][j];
			if(j > (1<<(i-1))) lcp[i][j] = min(lcp[i][j], lcp[i-1][j - (1<<(i-1))]);
		}
	}
	while(q--){
		int l = _readInt() - 1;
		int r = _readInt() - 1;
		auto up = factorize(r - l + 1);
		int ans = r - l + 1;
		for(auto &i : up){
			ans /= i;
			if(getlcp(l, l + ans) + l + ans < r + 1){
				ans *= i;
			}
		}
		printf("%d\n", ans);
	}
}
