#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, int>;
const int MAXN = 30005;
const int mod = 1e9 + 7;

int n, k;
int cost1[MAXN][7];
int cost2[MAXN][7];
pi d1[2][7][203];
pi d2[2][7][203];
int match[100000];
vector<vector<int>> enums;

int getNum(vector<int> &v){
	int ans = 0;
	for(auto &i : v) ans = ans * k + i;
	assert(match[ans] != -1);
	return match[ans];
}

void bktk(int x, vector<int> v){
	if(x == k){
		enums.push_back(v);
		return;
	}
	int maxv = -1;
	for(auto &i : v) maxv = max(maxv, i);
	v.push_back(0);
	for(v[x] = 0; v[x] <= maxv + 1; v[x]++){
		bktk(x + 1, v);
	}
}

int nxtF[6][203];
int nxtG[6][203];

pi merge(pi x, pi y){
	if(x > y) swap(x, y);
	if(x.first == y.first) x.second = (x.second + y.second) % mod;
	return x;
}

vector<int> uniV(vector<int> x, int l){
	int minV = min(x[l], x[l+1]);
	int maxV = max(x[l], x[l+1]);
	for(auto &i : x){
		if(i == maxV) i = minV;
		if(i > maxV) i = i-1;
	}
	return x;
}

void getTransF(int y, vector<int> comp){
	int gn = getNum(comp);
	if(comp[y] != comp[y+1]){
		comp = uniV(comp, y);
		nxtF[y][gn] = getNum(comp);
	}
	else nxtF[y][gn] = -1;
}

void getTransG(int y, vector<int> comp){
	int gn = getNum(comp);
	if(count(comp.begin(), comp.end(), comp[y]) != 1){
		comp[y] = *max_element(comp.begin(), comp.end()) + 1;
		int ren[7] = {};
		int cnt = 0;
		for(int j=0; j<comp.size(); j++){
			if(!ren[comp[j]]){
				ren[comp[j]] = ++cnt;
			}
		}
		for(int j=0; j<comp.size(); j++){
			comp[j] = ren[comp[j]] - 1;
		}
		nxtG[y][gn] = getNum(comp);
	}
	else nxtG[y][gn] = -1;
}

int main(){
	freopen("escape.in", "r", stdin);
	freopen("escape.out", "w", stdout);
	for(int i=0; i<2; i++){
		for(int j=0; j<6; j++){
			fill(d1[i][j], d1[i][j] + 203, pi(1e18, 1));
			fill(d2[i][j], d2[i][j] + 203, pi(1e18, 1));
		}
	}
	scanf("%d %d",&n,&k);
	for(int i=0; i<n; i++){
		for(int j=0; j+1<k; j++){
			scanf("%d",&cost1[i][j]);
		}
	}
	for(int i=0; i<k; i++){
		for(int j=0; j+1<n; j++){
			scanf("%d",&cost2[j][i]);
		}
	}
	{
		memset(match, -1, sizeof(match));
		vector<int> v;
		bktk(0, v);
		for(int i=0; i<enums.size(); i++){
			int ans = 0;
			for(int j=0; j<k; j++){
				ans = ans * k + enums[i][j];
			}
			match[ans] = i;
		}
		for(int i=0; i<k; i++) for(auto &j : enums){
			getTransF(i, j);
			getTransG(i, j);
		}
	}
	for(int i=n-1; i>=0; i--){
		if(i == n - 1){
			d1[i%2][k-1][0] = pi(0, 1);
			for(int j=k-2; j>=0; j--){
				for(int l=0; l<enums.size(); l++){
					d1[i%2][j][l] = d1[i%2][j+1][l];
					if(~nxtF[j][l]){
						auto nxt = d1[i%2][j+1][nxtF[j][l]];
						nxt.first += cost1[i][j];
						d1[i%2][j][l] = merge(d1[i%2][j][l], nxt);
					}
				}
			}
			continue;
		}
		for(int j=0; j<enums.size(); j++){
			d2[i%2][k][j] = d1[(i+1)%2][0][j];
		}
		for(int j=k-1; j>=0; j--){
			for(int l=0; l<enums.size(); l++){
				d2[i%2][j][l] = d2[i%2][j+1][l];
				d2[i%2][j][l].first += cost2[i][j];
				if(~nxtG[j][l]){
					auto rety = d2[i%2][j+1][nxtG[j][l]];
					d2[i%2][j][l] = merge(d2[i%2][j][l], rety);
				}
			}
		}
		for(int j=0; j<enums.size(); j++){
			d1[i%2][k-1][j] = d2[i%2][0][j];
		}
		for(int j=k-2; j>=0; j--){
			for(int k=0; k<enums.size(); k++){
				d1[i%2][j][k] = d1[i%2][j+1][k];
				if(~nxtF[j][k]){
					auto nxt = d1[i%2][j+1][nxtF[j][k]];
					nxt.first += cost1[i][j];
					d1[i%2][j][k] = merge(d1[i%2][j][k], nxt);
				}
			}
		}
	}
	auto ans = d1[0][0][enums.size() - 1];
	//cout << ans.first << endl;
	cout << ans.second << endl;
}

