#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 1005;

pi a[MAXN];
double dp[11][MAXN][MAXN];
double aux[MAXN][MAXN];
pi trk[11][MAXN][MAXN];
double dist[MAXN][MAXN];
int trka[MAXN][MAXN];

void trace(int s, int e, int depth){
	if(s == e){
		cout << s + 1 << " ";
		return;
	}
	trace(s, trk[depth][s][e].first, depth + 1);
	trace(trk[depth][s][e].second, e, depth + 1);
}

void solve(vector<int> v, bool sord, int depth){
	if(sz(v) == 1){
		dp[depth][v[0]][v[0]] = 0;
		return;
	}
	sort(all(v), [&](const int &p, const int &q){
		if(sord == 0) return a[p] < a[q];
		return pi(a[p].second, a[p].first) < pi(a[q].second, a[q].first);
	});
	vector<int> L(v.begin(), v.begin() + sz(v) / 2);
	vector<int> R(v.begin() + sz(v) / 2, v.end());
	solve(L, sord ^ 1, depth + 1);
	solve(R, sord ^ 1, depth + 1);
	for(auto &i : v){
		for(auto &j : v){
			aux[i][j] = 1e18;
		}
	}
	for(auto &i : L){
		for(auto &j : L){
			for(auto &k : R){
				if(aux[i][k] > dp[depth + 1][i][j] + dist[j][k]){
					aux[i][k] = dp[depth + 1][i][j] + dist[j][k];
					trka[i][k] = j;
				}
			}
		}
	}
	for(auto &k : L){
		for(auto &i : R){
			for(auto &j : R){
				if(dp[depth][k][j] > aux[k][i] + dp[depth + 1][i][j]){
					dp[depth][k][j] = aux[k][i] + dp[depth + 1][i][j];
					trk[depth][k][j] = pi(trka[k][i], i);
				}
			}
		}
	}
	for(auto &i : R){
		for(auto &j : R){
			for(auto &k : L){
				if(aux[i][k] > dp[depth + 1][i][j] + dist[j][k]){
					aux[i][k] = dp[depth + 1][i][j] + dist[j][k];
					trka[i][k] = j;
				}
			}
		}
	}
	for(auto &k : R){
		for(auto &i : L){
			for(auto &j : L){
				if(dp[depth][k][j] > aux[k][i] + dp[depth + 1][i][j]){
					dp[depth][k][j] = aux[k][i] + dp[depth + 1][i][j];
					trk[depth][k][j] = pi(trka[k][i], i);
				}
			}
		}
	}
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i].first >> a[i].second;
	}
	for(int j = 0; j < n; j++){
		for(int k = 0; k < n; k++){
			dist[j][k] = hypot(a[j].first - a[k].first, a[j].second - a[k].second);
		}
	}
	for(int i = 0; i < 11; i++){
		for(int j = 0; j < n; j++){
			for(int k = 0; k < n; k++){
				dp[i][j][k] = 1e12;
			}
		}
	}
	vector<int> ord(n);
	iota(all(ord), 0);
	solve(ord, 0, 0);
	double cur = 1e18;
	int st = -1, ed = -1;
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			if(dp[0][i][j] < cur){
				cur = dp[0][i][j];
				st = i;
				ed = j;
			}
		}
	}
	cout << setprecision(69) <<  cur << endl;
	trace(st, ed, 0);
}
