#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define move fuck
using namespace std;
using lint = long long;
const int MAXN = 10;

int n;
int a[MAXN][MAXN];
int vis[MAXN], outdeg[MAXN];

char layer[30][101][101];

int main(){
	cin >> n;
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			cin >> a[i][j];
			if(i == j) a[i][j] = 1;
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			for(int k=1; k<=n; k++){
				a[j][k] |= (a[j][i] & a[i][k]);
			}
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(a[i][j]) outdeg[i]++;
		}
	}
	vector<vector<int>> scc;
	for(int i=1; i<=n; i++){
		if(vis[i]) continue;
		vector<int> nxt;
		for(int j=1; j<=n; j++){
			if(a[i][j] && a[j][i] && !vis[j]){
				vis[j] = 1;
				nxt.push_back(j);
			}
		}
		scc.push_back(nxt);
	}
	sort(scc.begin(), scc.end(), [&](const vector<int> &a, const vector<int> &b){
		return outdeg[a[0]] < outdeg[b[0]];
	});
	for(int i=0; i<20; i++){
		for(int j=0; j<40; j++){
			for(int k=0; k<40; k++){
				if(i & 1) layer[i][j][k] = '#';
				else layer[i][j][k] = '.';
			}
		}
	}
	for(int i=0; i<sz(scc); i++){
		for(int j=0; j<sz(scc[i]); j++){
			layer[2*i][39][39-j] = scc[i][j] + '0';
		}
	}
	for(int i=1; i<=n; i++){
		for(int j=1; j<=n; j++){
			if(i != j && a[i][j]){
				int stv = -1;
				int edv = -1;
				for(int k=0; k<sz(scc); k++){
					if(find(scc[k].begin(), scc[k].end(), i) != scc[k].end()) stv = k;
					if(find(scc[k].begin(), scc[k].end(), j) != scc[k].end()) edv = k;
				}
				if(stv == edv) continue;
				assert(stv > edv);
				int idx1 = 4 * stv + 2;
				int idx2 = 4 * edv + 2;
				for(int j=2*edv+2; j<=2*stv-2; j+=2){
					for(int k=-1; k<=1; k++){
						for(int l=-1; l<=1; l++){
							layer[j][idx1+k][idx2+l] = '#';
						}
					}
				}
				for(int j=2*edv; j<=2*stv; j++){
					// open tunnel
					layer[j][idx1][idx2] = '.';
				}
			}
		}
	}
	puts("40 40 20");
	for(int i=0; i<20; i++){
		for(int j=0; j<40; j++){
			puts(layer[19-i][j]);
		}
		puts("");
	}
}
