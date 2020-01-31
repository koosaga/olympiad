#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 3005;

int n, m;
char str[MAXN][MAXN];
bool UP[MAXN][MAXN], DN[MAXN][MAXN], mark[MAXN][MAXN];
int tot_unblock;

vector<pi> trace1(int x, int y){
	int p = y;
	vector<pi> lo_path;
	for(int i=x; i>=0; i--){
		while(p && UP[i][p - 1]){
			lo_path.emplace_back(i, p--);
		}
		lo_path.emplace_back(i, p);
	}
	reverse(all(lo_path));
	return lo_path;
}

vector<pi> trace2(int x, int y){
	vector<pi> lo_path;
	int p = x;
	for(int i=y; i<m; i++){
		while(DN[p + 1][i]){
			lo_path.emplace_back(p++, i);
		}
		lo_path.emplace_back(p, i);
	}
	return lo_path;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s", str[i]);
		tot_unblock += count(str[i], str[i] + m, '.');
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(i && UP[i-1][j]) UP[i][j] = 1;
			if(j && UP[i][j-1]) UP[i][j] = 1;
			if(i == 0 && j == 0) UP[i][j] = 1;
			if(str[i][j] == '*') UP[i][j] = 0;
		}
	}
	for(int i=n-1; i>=0; i--){
		for(int j=m-1; j>=0; j--){
			if(i+1 < n && DN[i+1][j]) DN[i][j] = 1;
			if(j+1 < m && DN[i][j+1]) DN[i][j] = 1;
			if(i == n-1 && j == m-1) DN[i][j] = 1;
			if(str[i][j] == '*') DN[i][j] = 0;
		}
	}
	if(!UP[n-1][m-1]){
		cout << 1ll * tot_unblock * (tot_unblock - 1) / 2 << endl;
		return 0;
	}
	vector<pi> lo_path, hi_path;
	int p = 0;
	for(int i=0; i<n; i++){
		while(DN[i][p+1]){
			hi_path.emplace_back(i, p++);
		}
		hi_path.emplace_back(i, p);
	}
	for(auto &[x, y] : hi_path) mark[x][y] = 1;
	lo_path = trace1(n - 1, m - 1);
	lint ans = 0;
	int onecut = 0;
	for(auto &[x, y] : lo_path){
		if(mark[x][y]){
			onecut++;
			ans += tot_unblock - 1;
		}
		else{
			assert(y < m - 1);
			for(int j=x-1; j>=0; j--){
				if(UP[j][y] && DN[j][y + 1]){
					auto vect1 = trace1(j, y);
					auto vect2 = trace2(j, y + 1);
					for(auto &[x, y] : vect1){
						if(mark[x][y]) ans++;
					}
					for(auto &[x, y] : vect2){
						if(mark[x][y]) ans++;
					}
					break;
				}
			}
		}
	}
	ans -= 1ll * (sz(lo_path) - onecut) * onecut;
	ans -= 1ll * onecut * (onecut - 1) / 2;
	cout << ans << endl;
}

