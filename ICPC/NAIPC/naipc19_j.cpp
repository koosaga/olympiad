#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;

char s[MAXN], t[MAXN];
int nxt[MAXN][26];

int main(){
	scanf("%s %s", s, t);
	int n = strlen(s);
	fill(nxt[n], nxt[n] + 26, n);
	for(int i=n-1; i>=0; i--){
		for(int j=0; j<26; j++){
			nxt[i][j] = nxt[i+1][j];
		}
		nxt[i][s[i] - 'a'] = i;
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		int pos = i;
		for(int j=0; t[j]; j++){
			if(pos == n + 1) break;
			pos = nxt[pos][t[j] - 'a'] + 1;
		}
		ret += n + 1 - pos;
	}
	cout << ret << endl;
}
