#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 2000005;

int nxt[MAXN][26];
char s[MAXN], t[MAXN];
int n, m;

int main(){
	scanf("%s %s", s, t);
	n = strlen(s);
	m = strlen(t);
	for(int i=0; i<m; i++) t[i + m] = t[i];
	for(int i=0; i<26; i++) nxt[2*m][i] = 2*m;
	for(int i=2*m-1; i>=0; i--){
		for(int j=0; j<26; j++){
			nxt[i][j] = nxt[i+1][j];
		}
		nxt[i][t[i] - 'a'] = i;
	}
	lint len = 0;
	for(int i=0; i<n; i++){
		int fn = nxt[len % m][s[i] - 'a'];
		if(fn == 2 * m){
			puts("-1");
			return 0;
		}
		len += fn - len % m + 1;
	}
	cout << (len + m - 1) / m << endl;
}