#include <bits/stdc++.h>
using namespace std;
const int MAXN = 400005;

struct sfx{
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
}sfxarray;

int sfx[MAXN], lcp[MAXN], rev[MAXN], lg[MAXN], spt[19][MAXN];
char str[MAXN];
int n, L[18][MAXN], R[18][MAXN];

bool trial(int x){
	for(int i=x; i<=n-x; i++){
		if(R[17][i - x] < i || L[17][i + x] > i) continue;
		int posl = i - x, posr = i + x;
		for(int j=17; j>=0; j--){
			if(R[j][posl] < i) posl -= (1 << j);
			if(L[j][posr] > i) posr += (1 << j);
		}
		if(posr - posl <= min(i, n - i)) return true;
	}
	return false;
}

int main(){
	scanf("%s",str);
	n = strlen(str);
	str[n] = '#';
	for(int i=0; i<n; i++){
		str[n + i + 1] = str[n - 1 - i];
	}
	sfxarray.solve(2*n+1, str, sfx, rev, lcp);
	for(int i=1; i<=2*n; i++){
		spt[0][i] = lcp[i];
		lg[i] = lg[i-1];
		while((2 << lg[i]) <= i) lg[i]++;
	}
	for(int i=1; i<=18; i++){
		for(int j=1; j<=2*n; j++){
			spt[i][j] = spt[i-1][j];
			if(j > (1<<(i-1))){
				spt[i][j] = min(spt[i][j], spt[i-1][j - (1<<(i-1))]);
			}
		}
	}
	auto query = [&](int s, int e){
		s = rev[s]; e = rev[e];
		if(s > e) swap(s, e);
		int l = lg[e - s];
		return min(spt[l][s + (1<<l)], spt[l][e]);
	};
	auto reversal_same = [&](int s, int e, int rs, int re){
		return query(s, 2 * n + 1 - re) >= e - s;
	};
	for(int i=0; i<=n; i++){
		int s = 0, e = n - i;
		while(s != e){
			int m = (s+e+1)/2;
			if(reversal_same(n - m, n, i, i + m)){
				s = m;
			}
			else e = m - 1;
		}
		R[0][i] = i + s;
		s = 0, e = i;
		while(s != e){
			int m = (s+e+1)/2;
			if(reversal_same(i - m, i, 0, m)){
				s = m;
			}
			else e = m - 1;
		}
		L[0][i] = i - s;
	}
	for(int i=1; i<=17; i++){
		for(int j=0; j<=n; j++){
			R[i][j] = R[i-1][j];
			if(j - (1<<(i-1)) >= 0) R[i][j] = max(R[i][j], R[i-1][j - (1<<(i-1))]);
			L[i][j] = L[i-1][j];
			if(j + (1<<(i-1)) <= n) L[i][j] = min(L[i][j], L[i-1][j + (1<<(i-1))]);
		}
	}
	int s = 0, e = n;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	if(s == 0) s = -1;
	cout << s << endl;
}
