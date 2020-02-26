#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 305;
const int dx[4] = {-1, -1, 1, 1};
const int dy[4] = {-1, 1, 1, -1};

int n;
char str[MAXN][MAXN];
int pos[3 * MAXN][3 * MAXN];

int solve(){
	auto ok = [&](int x, int y){
		return x>=0&&x<n&&y>=0&&y<n&&str[x][y] == '*';;
	};
	memset(pos, 0, sizeof(pos));
	for(int i=2*n-1; i>=0; i--){
		for(int j=2*n-1; j>=0; j--){
			pos[i][j] = pos[i + 1][j + 1];
			if(ok(i - n, j - n)) pos[i][j]++;
		}
	}
	int ret = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=1; k<n; k++){
				if(i + k >= n || j + k >= n) break;
				if(ok(i, j) && ok(i + k, j + k)){
					ret += pos[i + k + n][j - k + n] - pos[i + k + n + k + 1][j - k + n + k + 1];
					ret += pos[i - k + n][j + k + n] - pos[i - k + n + k + 1][j + k + n + k + 1];
				}
			}
		}
	}
	return ret;
}

int main(){
	freopen("triangles.in", "r", stdin);
	freopen("triangles.out", "w", stdout);
	cin >> n;
	for(int i=0; i<n; i++) cin >> str[i];
	int ret = solve();
	for(int i=0; i<n; i++){
		reverse(str[i], str[i] + n);
	}
	ret += solve();
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(str[i][j] == '.') continue;
			bitset<MAXN> bs[4];
			for(int k=0; k<4; k++){
				int cx = i, cy = j;
				for(int l=0; l<MAXN; l++){
					cx += dx[k];
					cy += dy[k];
					if(cx >= 0 && cy >= 0 && cx < n && cy < n && str[cx][cy] == '*') bs[k][l] = 1;
				}
			}
			ret -= (bs[0] & bs[1]).count();
			ret -= (bs[1] & bs[2]).count();
			ret -= (bs[2] & bs[3]).count();
			ret -= (bs[3] & bs[0]).count();
		}
	}
	cout << ret << endl;
}
