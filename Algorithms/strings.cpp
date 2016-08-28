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

const int MAXN = 500005;
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

const int MAXN = 100005, MAXC = 26;
struct aho_corasick{
	int trie[MAXN][MAXC], fail[MAXN], term[MAXN], piv;
	void init(vector<string> &v){
		memset(trie, 0, sizeof(trie));
		memset(fail, 0, sizeof(fail));
		memset(term, 0, sizeof(term));
		piv = 0;
		for(auto &i : v){
			int p = 0;
			for(auto &j : i){
				if(!trie[p][j]) trie[p][j] = ++piv;
				p = trie[p][j];
			}
			term[p] = 1;
		}
		queue<int> que;
		for(int i=0; i<MAXC; i++){
			if(trie[0][i]) que.push(trie[0][i]);
		}
		while(!que.empty()){
			int x = que.front();
			que.pop();
			for(int i=0; i<MAXC; i++){
				if(trie[x][i]){
					int p = fail[x];
					while(p && !trie[p][i]) p = fail[p];
					p = trie[p][i];
					fail[trie[x][i]] = p;
					if(term[p]) term[trie[x][i]] = 1;
					que.push(trie[x][i]);
				}
			}
		}
	}
	bool query(string &s){
		int p = 0;
		for(auto &i : s){
			while(p && !trie[p][i]) p = fail[p];
			p = trie[p][i];
			if(term[p]) return 1;
		}
		return 0;
	}
}aho_corasick;

const int MAXN = 1000005;
struct manacher{
	int aux[2 * MAXN - 1];
	void solve(int n, int *str, int *ret){
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
			ret[i] = cur;
		}
	}
}manacher;
