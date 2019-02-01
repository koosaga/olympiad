#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 305;
const int mod = 100000;
using pi = pair<int, int>;
#define sz(v) int((v).size())

int n, m, k;
char str[MAXN][MAXN];
int a[MAXN][MAXN];

void CW(int p, int q){
	tie(a[p][q], a[p][q+1], a[p+1][q], a[p+1][q+1]) = make_tuple(a[p+1][q], a[p][q], a[p+1][q+1], a[p][q+1]);
}

void CCW(int p, int q){
	tie(a[p][q], a[p][q+1], a[p+1][q], a[p+1][q+1]) = make_tuple(a[p][q+1], a[p+1][q+1], a[p][q], a[p+1][q]);
}

int nxt[2][MAXN * MAXN], cost[2][MAXN * MAXN];
int mcost[MAXN * MAXN];

char buf[MAXN];

vector<int> get_div(char *str, int m){
	vector<int> nota(strlen(str));
	for(int i=0; str[i]; i++){
		nota[i] = str[i] - '0';
	}
	for(int i=0; i<nota.size(); i++){
		if(i + 1 < nota.size()) nota[i+1] += 10 * (nota[i] % m);
		nota[i] /= m;
	}
	reverse(nota.begin(), nota.end());
	while(nota.size() && nota.back() == 0) nota.pop_back();
	return nota;
}

int get_mod(char *str, int m){
	int ret = 0;
	for(int i=0; str[i]; i++){
		ret *= 10;
		ret += str[i] - '0';
		ret %= m;
	}
	return ret;
}

int main(){
	scanf("%d %d %s",&n,&m,buf);
	int mcnt = get_mod(buf, (n - 1) * (m - 1));
	auto cnt = get_div(buf, (n - 1) * (m - 1));
	for(int i=0; i<n-1; i++){
		scanf("%s", str[i]);
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] = i * m + j + 1;
		}
	}
	for(int i=0; i<n-1; i++){
		for(int j=0; j<m-1; j++){
			cost[0][a[i][j]]++;
			if(str[i][j] == 'R') CW(i, j);
			if(str[i][j] == 'L') CCW(i, j);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			nxt[0][a[i][j]] = i * m + j + 1;
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			a[i][j] = i * m + j + 1;
		}
	}
	for(int i=0; i<n-1; i++){
		if(mcnt == 0) break;
		for(int j=0; j<m-1; j++){
			mcost[a[i][j]]++;
			mcnt--;
			if(mcnt == 0) break;
			if(str[i][j] == 'R') CW(i, j);
			if(str[i][j] == 'L') CCW(i, j);
		}
		if(mcnt ==  0) break;
	}
	vector<int> p(n * m + 1);
	vector<int> ret(n * m + 1);
	iota(p.begin(), p.end(), 0);
	for(int i=0; i<cnt.size(); i++){
		for(int j=1; j<=n*m; j++){
			for(int k=0; k<cnt[i]; k++){
				ret[j] += cost[i%2][p[j]];
				p[j] = nxt[i%2][p[j]];
			}
			ret[j] %= mod;
		}
		for(int j=1; j<=n*m; j++){
			int cur = j;
			int cst = 0;
			for(int k=0; k<10; k++){
				cst += cost[i%2][cur];
				cur = nxt[i%2][cur];
			}
			nxt[(i+1)%2][j] = cur;
			cost[(i+1)%2][j] = cst % mod;
		}
	}
	for(int i=1; i<=n*m; i++){
		ret[i] += mcost[p[i]];
		ret[i] %= mod;
		printf("%d\n", ret[i]);
	}
}
