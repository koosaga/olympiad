#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pi;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

vector<pi> s[256];
vector<int> v[7];
int adj[7][7];

int R[320], M[256];
bool vis[256];
int ITER;
int mp[256 * 7];

int get(int x){
	cout << x << endl;
	int y; cin >> y; return y;
}
int mapfind(int x){
	int t = x * 7 + ITER % 7;
	return t;
}

int newget(int x){
	int t = mapfind(x);
	if(mp[t] >= 0) return mp[t];
	ITER++;
	return mp[t] = get(x);
}

bool bad(){
	for(int i=0; i<7; i++){
		for(int j=0; j<7; j++){
			for(int k=0; k<7; k++){
				if(adj[j][i] == -1 || adj[i][k] == -1) continue;
				if(adj[j][k] != -1){
					assert(adj[j][k] == (adj[j][i] ^ adj[i][k]));
				}
				adj[j][k] = adj[j][i] ^ adj[i][k];
			}
		}
	}
	R[0] = adj[4][5], R[1] = adj[5][6], R[2] = adj[6][0];
	return (R[0] < 0 || R[1] < 0 || R[2] < 0);
}

int main(){
	memset(vis, 0, sizeof(vis));
	memset(adj,-1,sizeof(adj));
	memset(mp,-1,sizeof(mp));
	for(int i=0; i<7; i++) adj[i][i] = 0;
	for(int i=0; i<7; i++){
		v[i].resize(256);
		iota(all(v[i]), 0);
		shuffle(all(v[i]), rng);
	}
	for(int i = 0; i< 256; i++) s[i].clear();
	while(bad()){
		int t = ITER % 7;
		if(sz(v[t]) == 0) assert(0);
		int x = v[t].back(); v[t].pop_back();
		int y = newget(x);
		for(auto &j : s[y]){
			adj[j.first][t] = adj[t][j.first] = x ^ j.second;
		}
		s[y].push_back(pi(t, x));
	}
	for(int i=3; i<320; i++){
		R[i] = R[i-2] ^ R[i-3];
	}
	for(int i=0; i<256; i++){
		int bad = 0;
		for(int j=0; j<256; j++){
			if(!vis[j] && mp[mapfind(j ^ R[ITER])] >= 0){
				M[j] = newget(j ^ R[ITER]);
				vis[j] = 1;
				bad = 1;
				break;
			}
		}
		if(bad) continue;
		for(int j=0; j<256; j++){
			if(!vis[j]){
				M[j] = newget(j ^ R[ITER]);
				vis[j] = 1;
				break;
			}
		}
	}
	cout << "SOLUTION" << endl;
	for(int i=0; i<3; i++){
		cout << R[i] << endl;
	}
	for(int i=0; i<256; i++){
		cout << M[i] << endl;
	}
}

