#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 100050;

int n, s, k;
lint room[MAXN][22];
lint nose[MAXN][22];
vector<int> gph[MAXN];

int solve(int x, int p){
	int ret = 0;
	for(auto &i : gph[x]){
		if(i != p){
			ret += solve(i, x);
			for(int j=0; j<k; j++){
				room[x][j + 1] += room[i][j];
				nose[x][j + 1] += nose[i][j];
			}
		}
	}
	lint up = (room[x][k] + s - 1) / s;
	nose[x][0] += up * s; 
	ret += up;
	for(int i=k; i>=0; i--){
		for(int j=0; j<2 && j<=k-i; j++){
			lint dx = min(nose[x][k - i - j], room[x][i]);
			nose[x][k - i - j] -= dx;
			room[x][i] -= dx;
		}
	}
	return ret;
}

int main(){
	scanf("%d %d %d",&n,&s,&k);
	for(int i=1; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		s += k + 2;
		e += k + 2;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=k+2; i++){
		gph[i].push_back(i + 1);
		gph[i + 1].push_back(i);
	}
	for(int i=1; i<=n; i++) room[i+k+2][0] = 1;
	cout << solve(1, 0) << endl;
}

