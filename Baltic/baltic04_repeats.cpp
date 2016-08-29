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

const int MAXN = 50005;
struct sfxarray{
	int ord[MAXN], nord[MAXN], cnt[MAXN], aux[MAXN];
	void init(int n, char *str, int *sfx, int *rev, int *lcp){
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

int n;
char str[50005], rstr[50005];
int sfx[50005], rev[50005], lcp[50005];
int rsfx[50005], rrev[50005], rlcp[50005];

int lg[50005], rmq1[16][50005], rmq2[16][50005];

int queryl(int s, int e){
	if(s > e) swap(s, e);
	int l = lg[e-s];
	return min(rmq1[l][e], rmq1[l][s+(1<<l)]);
}

int queryr(int s, int e){
	if(s > e) swap(s, e);
	int l = lg[e-s];
	return min(rmq2[l][e], rmq2[l][s+(1<<l)]);
}

int solve(int x){
	int ret = 0;
	for(int i=0; i+x-1<n; ){
		int e = i+x, clen = 1;
		while(e+x-1 < n && queryl(rev[i], rev[e]) >= x){
			e += x;
			clen++;
		}
		int resi = 0;
		if(e < n) resi += queryl(rev[i], rev[e]);
		if(i > 0) resi += queryr(rrev[n-i], rrev[n-x-i]);
		if(resi >= x) clen++;
		ret = max(ret, clen);
		i = e;
	}
//	fprintf(stderr,"%d %d\n", x, ret);
	return ret;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		memset(sfx, 0, sizeof(sfx)); memset(rsfx, 0, sizeof(rsfx));
		memset(rev, 0, sizeof(rev)); memset(rrev, 0, sizeof(rrev));
		memset(lcp, 0, sizeof(lcp)); memset(rlcp, 0, sizeof(rlcp));
		scanf("%d",&n);
		char buf[3];
		for(int i=0; i<n; i++){
			scanf("%s",buf);
			str[i] = *buf;
			rstr[n-1-i] = *buf;
		}
		sfxarray.init(n, str, sfx, rev, lcp);
		sfxarray.init(n, rstr, rsfx, rrev, rlcp);
		int p = 0;
		for(int i=1; i<=n; i++){
			while((2<<p) <= i) p++;
			lg[i] = p;
		}
		for(int i=1; i<n; i++){
			rmq1[0][i] = lcp[i];
			rmq2[0][i] = rlcp[i];
		}
		for(int i=1; i<16; i++){
			for(int j=1; j<n; j++){
				rmq1[i][j] = rmq1[i-1][j];
				rmq2[i][j] = rmq2[i-1][j];
				if(j > (1<<(i-1))){
					rmq1[i][j] = min(rmq1[i][j], rmq1[i-1][j - (1<<(i-1))]);
					rmq2[i][j] = min(rmq2[i][j], rmq2[i-1][j - (1<<(i-1))]);
				}
			}
		}
		int ret = 0;
		for(int i=1; i<=n; i++){
			ret = max(ret, solve(i));
		}
		printf("%d\n", ret);
	}
}

	
