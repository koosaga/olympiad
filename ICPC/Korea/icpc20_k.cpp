#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 1005;
const int MAXV = 500005;

int n;
char str[MAXN][MAXN];
char ans[MAXN][MAXN];

int idxh[MAXN][MAXN], pivh, lenh[MAXV];
int idxv[MAXN][MAXN], pivv, lenv[MAXV];
pi reph[MAXV];
pi repv[MAXV];
vector<int> gph[MAXV];
vector<int> gpv[MAXV];

void dfsH(int x, int p);
void dfsV(int x, int p);

int f(int a[MAXN][MAXN], int x, int y){
	if(x < 0 || x >= n || y < 0 || y >= n) return 1e9;
	if(!a[x][y]) return 1e9;
	return a[x][y];
}

void FILL(vector<pi> pos){
	/*
	printf("filling ");
	for(auto &[x, y] : pos) printf("(%d, %d) ", x, y);
	cout << endl;
	*/
	assert(sz(pos) > 1);
	if(pos[0].first == pos.back().first){
		for(auto &[x, y] : pos) ans[x][y] = '2';
		if(sz(pos) % 2){
			pos.resize(3);
			for(auto &[x, y] : pos) ans[x][y] = '4';
		}
	}
	else{
		for(auto &[x, y] : pos) ans[x][y] = '3';
		if(sz(pos) % 2){
			pos.resize(3);
			for(auto &[x, y] : pos) ans[x][y] = '5';
		}
	}
}

void dfsV(int x, int p = -1){
	if(lenv[x] == 1){
		pi pos = repv[x];
		pi par = repv[p];
		vector<int> horis;
		vector<pi> vrow;
		if(par.second < pos.second){
			for(int j = pos.second; j < n; j++){
				if(str[pos.first][j] == '1'){
					vrow.emplace_back(pos.first, j);
					horis.emplace_back(f(idxh, pos.first - 1, j));
					horis.emplace_back(f(idxh, pos.first + 1, j));
				}
				else break;
			}
		}
		else{
			for(int j = pos.second; j >= 0; j--){
				if(str[pos.first][j] == '1'){
					vrow.emplace_back(pos.first, j);
					horis.emplace_back(f(idxh, pos.first - 1, j));
					horis.emplace_back(f(idxh, pos.first + 1, j));
				}
				else break;
			}
		}
		FILL(vrow);
		// do stuff
		sort(all(horis));
		horis.resize(unique(all(horis)) - horis.begin());
		while(sz(horis) && horis.back() > 1e7) horis.pop_back();
		for(auto &son : horis){
			dfsH(son, idxh[pos.first][pos.second]);
		}
		return;
	}
	for(int y = repv[x].first; y < repv[x].first + lenv[x]; ){
		if(ans[y][repv[x].second] != '1'){
			y++;
			continue;
		}
		int e = y;
		vector<pi> vrow;
		while(e < n && ans[e][repv[x].second] == '1'){
			vrow.emplace_back(e++, repv[x].second);
		}
		y = e;
		FILL(vrow);
	}
	for(auto &i : gpv[x]){
		if(i == p) continue;
		dfsV(i, x);
	}
}

void dfsH(int x, int p = -1){
	if(lenh[x] == 1){
		pi pos = reph[x];
		pi par = reph[p];
		vector<int> verts;
		vector<pi> hrow;
		if(par.first < pos.first){
			for(int j = pos.first; j < n; j++){
				if(str[j][pos.second] == '1'){
					hrow.emplace_back(j, pos.second);
					verts.emplace_back(f(idxv, j, pos.second - 1));
					verts.emplace_back(f(idxv, j, pos.second + 1));
				}
				else break;
			}
		}
		else{
			for(int j = pos.first; j >= 0; j--){
				if(str[j][pos.second] == '1'){
					hrow.emplace_back(j, pos.second);
					verts.emplace_back(f(idxv, j, pos.second - 1));
					verts.emplace_back(f(idxv, j, pos.second + 1));
				}
				else break;
			}
		}
		FILL(hrow);
		// do stuff
		sort(all(verts));
		verts.resize(unique(all(verts)) - verts.begin());
		while(sz(verts) && verts.back() > 1e7) verts.pop_back();
		for(auto &son : verts){
			dfsV(son, idxv[pos.first][pos.second]);
		}
		return;
	}
	for(int y = reph[x].second; y < reph[x].second + lenh[x]; ){
		if(ans[reph[x].first][y] != '1'){
			y++;
			continue;
		}
		int e = y;
		vector<pi> hrow;
		while(e < n && ans[reph[x].first][e] == '1'){
			hrow.emplace_back(reph[x].first, e++);
		}
		y = e;
		FILL(hrow);
	}
	for(auto &i : gph[x]){
		if(i == p) continue;
		dfsH(i, x);
	}
}

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++) scanf("%s", str[i]);
	memcpy(ans, str, sizeof(str));
	// do h
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(str[i][j] == '0') continue;
			int e = j;
			while(e < n && str[i][e] == '1') e++;
			pivh++;
			reph[pivh] = pi(i, j);
			for(int k=j; k<e; k++){
				idxh[i][k] = pivh;
				lenh[pivh]++;
			}
			j = e;
		}
	}
	// do v
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(str[j][i] == '0') continue;
			int e = j;
			while(e < n && str[e][i] == '1') e++;
			pivv++;
			repv[pivv] = pi(j, i);
			for(int k=j; k<e; k++){
				idxv[k][i] = pivv;
				lenv[pivv]++;
			}
			j = e;
		}
	}
	for(int i=0; i<n-1; i++){
		for(int j=0; j<n; j++){
			if(idxh[i][j] && idxh[i+1][j]){
				gph[idxh[i][j]].push_back(idxh[i+1][j]);
				gph[idxh[i+1][j]].push_back(idxh[i][j]);
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n-1; j++){
			if(idxv[i][j] && idxv[i][j+1]){
				gpv[idxv[i][j]].push_back(idxv[i][j+1]);
				gpv[idxv[i][j+1]].push_back(idxv[i][j]);
			}
		}
	}
	for(int i=1; i<=pivh; i++){
		sort(all(gph[i]));
		gph[i].resize(unique(all(gph[i])) - gph[i].begin());
	}
	for(int i=1; i<=pivv; i++){
		sort(all(gpv[i]));
		gpv[i].resize(unique(all(gpv[i])) - gpv[i].begin());
	}
	dfsH(1);
	for(int i=0; i<n; i++) puts(ans[i]);
}
