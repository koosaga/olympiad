#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int mod = 1e9 + 7;
const int MAXN = 1100000;

int nxt[MAXN][4];
char s[1111][1111];

pi Move(pi x){
	int nd = nxt[x.first][x.second];
	int pos = find(nxt[nd], nxt[nd] + 4, x.first) - nxt[nd];
	return pi(nd, pos ^ 2);
}

int main(){
	int n, q; cin >> n >> q;
	n += 2;
	auto f = [&](int x, int y){ return x * n + y;  };
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			nxt[f(i, j)][0] = f(i, j + 1);
			nxt[f(i, j)][1] = f(i - 1, j);
			nxt[f(i, j)][2] = f(i, j - 1);
			nxt[f(i, j)][3] = f(i + 1, j);
		}
	}
	for(int i=1; i<=n-2; i++) scanf("%s", s[i] + 1);
	while(q--){
		int x, y, c; scanf("%d %d %d",&x,&y,&c);
		pi mv(0, 0);
		for(int i=0; i<y-1; i++) mv = Move(mv);
		mv.second = (mv.second + 3) % 4;
		for(int i=0; i<x; i++) mv = Move(mv);
		vector<pi> SEQ[4];

		for(int it = 0; it < 4; it++){
			for(int i=0; i<c; i++){
				mv.second = (mv.second + 1) % 4;
				SEQ[it].push_back(mv);
				mv.second = (mv.second + 3) % 4;
				mv = Move(mv);
			}
			mv.second = (mv.second + 1) % 4;
			mv = Move(mv);
		}
		vector<pair<pi, pi>> ass;
		for(int i = 0; i < 4; i++){
			for(int j=0; j<c; j++){
				ass.emplace_back(SEQ[i][j], Move(SEQ[(i+3)%4][j]));
			}
		}
		for(int i=0; i<sz(ass); i++){
			pi p, q; tie(p, q) = ass[i];
			q.second ^= 2;
			nxt[p.first][p.second] = q.first;
			nxt[q.first][q.second] = p.first;
		}
	}
	pi p(0, 3);
	for(int i=0; i<n-2; i++){
		p = Move(p);
		auto q = p;
		q.second = (q.second + 1) % 4;
		for(int j=0; j<n-2; j++){
			q = Move(q);
			putchar(s[q.first / n][q.first % n]);
		}
		puts("");
	}
}
