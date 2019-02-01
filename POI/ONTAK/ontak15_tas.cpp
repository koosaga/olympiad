#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

const int MAXN = 400005;
struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void solve(int n, int *str, int *sfx, int *rev, int *lcp){
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
			for(int i=1; i<=n || i<=1001; i++){
				cnt[i] += cnt[i-1];
			}
			for(int i=n-1; i>=0; i--){
				aux[--cnt[ord[min(i+p, n)]]] = i;
			}
			memset(cnt, 0, sizeof(cnt));
			for(int i=0; i<n; i++){
				cnt[ord[i]]++;
			}
			for(int i=1; i<=n || i<=1001; i++){
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


int n, m, v[400005];
int sfx[400005], rev[400005], lcp[400005];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		scanf("%d",&v[i]);
	}
	v[n] = 1001;
	cin >> m;
	for(int i=0; i<m; i++){
		scanf("%d",&v[n+1+i]);
	}
	v[n+m+1] = 1001;
	sfxarray.solve(n+m+2, v, sfx, rev, lcp);
	int p1 = 0, p2 = 0;
	while(p1 < n && p2 < m){
		if(rev[p1] < rev[p2+n+1]) printf("%d ", v[p1++]);
		else printf("%d ", v[n + 1 + (p2++)]);
	}
	while(p1 < n) printf("%d ", v[p1++]);
	while(p2 < m) printf("%d ", v[n + 1 +  (p2++)]);
}
