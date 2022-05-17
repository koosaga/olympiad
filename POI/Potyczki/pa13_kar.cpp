#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2505;

int n, m;
char str[MAXN][MAXN];
char chk[MAXN][MAXN];

vector<pi> solve(){
	vector<int> up(m + 2);
	vector<pi> ans;
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			if(str[i][j] == '#') up[j] = 0;
			else up[j]++;
		}
		vector<int> stk = {0};
		for(int j = 1; j <= m + 1; j++){
			while(sz(stk) && up[stk.back()] >= up[j]){
				int h = up[stk.back()]; stk.pop_back(); 
				int l = (sz(stk) ? stk.back() : 0) + 1;
				int r = j - 1;
				if(up[j] < h){
					ans.emplace_back(h, r - l + 1);
				}
			}
			stk.push_back(j);
		}
	}
	return ans;
}

char t[MAXN][MAXN];

void rotate(char s[MAXN][MAXN], int n, int m){
	for(int i = 0; i < MAXN; i++){
		for(int j = 0; j < MAXN; j++){
			t[i][j] = s[i][j];
			s[i][j] = 0;
		}
	}
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			s[m + 1 - j][i] = t[i][j];
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i = 1; i <= n; i++){
		scanf("%s", str[i] + 1);
		for(int j = 1; j <= m; j++){
			if(str[i][j] == 'X') str[i][j] = '.';
			else str[i][j] = '#';
		}
	}
	for(int it = 0; it < 4; it++){
		auto qq = solve();
		for(auto &[x, y] : qq){
			chk[x][y + 1] = 1;
		}
		{
			int val = 1e9;
			for(int i = 1; i <= n; i++){
				int cur = 0;
				for(int j = 1; j <= m + 1; j++){
					if(str[i][j] == '#' || j == m + 1){
						if(cur) val = min(val, cur);
						cur = 0;
					}
					else cur++;
				}
			}
			chk[1][val + 1] = 1;
		}
		rotate(str, n, m);
		for(int i = 1; i <= max(n, m); i++){
			for(int j = 1; j < i; j++) swap(chk[i][j], chk[j][i]);
		}
		swap(n, m);
	}
	pi ans(0, 0);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= m; j++){
			chk[i][j] |= chk[i][j - 1];
			chk[i][j] |= chk[i - 1][j];
			if(!chk[i][j]) ans = max(ans, pi(i*j, j));
		}
	}
	cout << ans.first/ans.second << " " << ans.second << endl;
}

