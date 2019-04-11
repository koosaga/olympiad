#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 2050;

int m, n, k, l, r;
char str[MAXN], prv[MAXN], cur[MAXN];
char pan[33][MAXN];
pi dp[33][MAXN];
int fuck[MAXN];

vector<string> fonts[256];
string ord;

int zeroCnt(int l, int r){
	return fuck[r] - fuck[l];
}

int fuck2[256][MAXN];

int compare(char c, int st){
	if(c == ' '){
		return zeroCnt(st, st + k);
	}
	if(~fuck2[c][st]) return fuck2[c][st];
	int ret = 0;
	for(int i=0; i<m; i++){
		for(int j=0; j<k; j++){
			if(pan[i][j + st] != fonts[c][i][j]) ret++;
		}
	}
 	return fuck2[c][st] = ret;
}

int main(){
	memset(fuck2, -1, sizeof(fuck2));
	scanf("%d %d %d %d %d\n",&m,&n,&k,&l,&r);
	for(int i=0; i<m; i++){
		fgets(str, MAXN, stdin);
		vector<string> tok; string cur;
		for(int j=0; str[j]; j++){
			if(isspace(str[j])){
				if(cur.size()) tok.push_back(cur);
				cur = "";
			}
			else{
				cur.push_back(str[j]);
			}
		}
		if(i == 0){
			for(int j=0; j<tok.size(); j+=2){
				ord.push_back(tok[j][0]);
			}
			for(int j=1; j<tok.size(); j+=2){
				fonts[ord[j / 2]].push_back(tok[j]);
			}
		}
		else{
			for(int j=0; j<tok.size(); j++){
				fonts[ord[j]].push_back(tok[j]);
			}
		}
	}
	fgets(prv, MAXN, stdin);
	int ptr = 0;
	for(int i=0; prv[i]; i++){
		if(prv[i] == '\n') break;
		int x; scanf("%d",&x);
		getchar();
		ptr += x;
		if(prv[i] == ' '){
			ptr += k;
			continue;
		}
		for(int j=ptr; j<ptr + k; j++){
			for(int l=0; l<m; l++){
				pan[l][j] = fonts[prv[i]][l][j - ptr];
			}
		}
		ptr += k;
	}
	for(int i=0; i<m; i++){
		for(int j=0; j<n; j++){
			if(!pan[i][j]) pan[i][j] = '.';
			if(pan[i][j] != '.') fuck[j + 1]++;
		}
	}
	for(int i=1; i<=n; i++) fuck[i] += fuck[i-1];
	fgets(cur, MAXN, stdin);
	int len = strlen(cur);
	if(cur[len - 1] == '\n') len--;
	assert(!isspace(cur[0]) && !isspace(cur[len - 1]));
	cur[len] = 0;
	for(int i=0; i<=len; i++){
		for(int j=0; j<=n; j++){
			dp[i][j] = pi(1e9, 1e9);
		}
	}
	dp[0][0] = pi(0, 0);
	for(int i=1; i<=len; i++){
		for(int j=0; j<=n; j++){
			int st = l, ed = r;
			if(i == 1) st = 0, ed = n;
			for(int m=st; m<=ed; m++){
				if(j - m - k < 0) continue;
				int nxt = dp[i-1][j - m - k].first + zeroCnt(j - m - k, j - k) + compare(cur[i - 1], j - k);
				dp[i][j] = min(dp[i][j], pi(nxt, m));
			}
		}
	}
	for(int i=0; i<=n; i++){
		dp[len][i].first += zeroCnt(i, n);
	}
	int min_ptr = min_element(dp[len], dp[len] + n + 1) - dp[len];
//	cout << dp[len][min_ptr].first << endl;
	vector<int> v;
	for(int i=len; i; i--){
		v.push_back(dp[i][min_ptr].second);
		min_ptr -= k + v.back();
	}
	reverse(v.begin(), v.end());
	for(auto &i : v) cout << i << " ";
}
