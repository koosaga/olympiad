#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<lint, lint> pi;

const int MAXN = 500005;
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

char str[500005];
int n, s[3][500005], t[4], ans[500005];
int sfx[500005], rev[500005], lcp[500005];

int ok(int st, int ed){
	if(ed - st + 1 < t[0]) return 0;
	for(int i=0; i<3; i++){
		int w = s[i][ed] - (st ? s[i][st-1] : 0);
		if(w < t[i+1]) return 0;
	}
	return 1;
}

int main(){
	cin >> n;
	for(int i=0; i<4; i++) cin >> t[i];
	cin >> str;
	for(int i=0; i<n; i++){
		if(isdigit(str[i])){
			s[0][i]++;
		}
		if(isupper(str[i])){
			s[2][i]++;
		}
		if(!isalpha(str[i]) && !isdigit(str[i])){
			s[1][i]++;
		}
		if(i){
			s[0][i] += s[0][i-1];
			s[1][i] += s[1][i-1];
			s[2][i] += s[2][i-1];
		}
	}
	int e = 0;
	for(int i=0; i<n; i++){
		while(e < n && !ok(i, e)) e++;
		ans[i] = e;
	}
	sfxarray.solve(n, str, sfx, rev, lcp);
	lint ret = 0;
	for(int i=0; i<n; i++){
		ret += n - max(sfx[i] + lcp[i], ans[sfx[i]]);
	}
	ret = (ret + 1) / 2;
	for(int i=0; i<n; i++){
		int nw = n - max(sfx[i] + lcp[i], ans[sfx[i]]);
		if(ret > nw){
			ret -= nw;
		}
		else{
			int p = max(sfx[i] + lcp[i], ans[sfx[i]]) + ret;
			for(int j=sfx[i]; j<p; j++){
				putchar(str[j]);
			}
			return 0;
		}
	}
}
