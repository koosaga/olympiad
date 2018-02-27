#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
const int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

struct disj{
	int pa[100005];
	void init(int n){ iota(pa, pa + n, 0); }
	int find(int x){ return pa[x] = (pa[x] == x ? x : find(pa[x])); }
	void uni(int p, int q){ pa[find(q)] = find(p);}
}disj;

struct ed{
	int s, e, x;
};

vector<string> v;

int L(int x, int y){ return 50000 + x * 205 + y; }
int R(int x, int y){ return L(x, y+1); }
int U(int x, int y){ return x * 205 + y; }
int D(int x, int y){ return U(x+1, y); }

bool ok(int x, int y){
	return x >= 0 && x < v.size() && y >= 0 && y < v[x].size() && v[x][y] == '#';
}

int cmp[205][205];
int mp[205];
int type[100005];
int minx, maxx, miny, maxy;

int dp[100005];
vector<pi> gph[100005];

int f(int x){
	if(~dp[x]) return dp[x];
	vector<int> go;
	for(auto &i : gph[x]){
		go.push_back(f(i.first) ^ i.second);
	}
	if(type[x] == 0){
		assert(go.size() == 1);
		return dp[x] = go[0];
	}
	if(type[x] == 1){
		for(auto &i : go) if(i == 1) return dp[x] = 1;
		return dp[x] = 0;
	}
	if(type[x] == 2){
		for(auto &i : go) if(i == 0) return dp[x] = 0;
		return dp[x] = 1;
	}
	if(type[x] == 3){
		dp[x] = 0;
		for(auto &i : go) dp[x] ^= i;
		return dp[x];
	}
	assert(0);
}

void dfs(int x, int y, int c){
	if(cmp[x][y]) return;
	minx = min(minx, x);
	maxx = max(maxx, x);
	miny = min(miny, y);
	maxy = max(maxy, y);
	cmp[x][y] = c;
	for(int i=0; i<4; i++){
		if(ok(x + dx[i], y + dy[i])){
			dfs(x + dx[i], y + dy[i], c);
		}
	}
}

void solve(){
	int piv = 0;
	vector<ed> edg;
	vector<pi> gates;
	vector<pi> digits;
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<v[i].size(); j++){
			if(v[i][j] == '#' && !cmp[i][j]){
				minx = miny = 1e9;
				maxx = maxy = -1e9;
				dfs(i, j, ++piv);
				int flg = 0;
				for(int x = minx; x <= maxx; x++){
					for(int y = miny; y <= maxy; y++){
						if(v[x][y] == '1'){
							flg = 1;
						}
						if(v[x][y] == '&'){
							flg = 2;
						}
						if(v[x][y] == '='){
							flg = 3;
						}
						cmp[x][y] = piv;
						disj.uni(L(x, y), R(x, y));
						disj.uni(U(x, y), D(x, y));
						disj.uni(L(x, y), U(x, y));
					}
				}
				gates.push_back(pi(L(minx, miny), flg));
			}
		}
	}
	for(int i=0; i<v.size(); i++){
		for(int j=0; j<v[i].size(); j++){
			if(v[i][j] == '-'){
				disj.uni(L(i, j), R(i, j));
			}
			if(v[i][j] == '|'){
				disj.uni(U(i, j), D(i, j));
			}
			if(v[i][j] == '+'){
				disj.uni(L(i, j), R(i, j));
				disj.uni(U(i, j), D(i, j));
				disj.uni(L(i, j), D(i, j));
			}
			if(v[i][j] == 'x'){
				disj.uni(L(i, j), R(i, j));
				disj.uni(U(i, j), D(i, j));
			}
			if(!cmp[i][j] && v[i][j] == '='){
				edg.push_back({L(i, j), R(i, j), 0});
			}
			if(v[i][j] == 'o'){
				edg.push_back({L(i, j), R(i, j), 1});
			}
			if(!cmp[i][j]){
				if(isupper(v[i][j])){
					mp[v[i][j]] = L(i, j);
				}
				if(isdigit(v[i][j])){
					digits.push_back(pi(R(i, j),v[i][j] & 1));
				}
			}
		}
	}
	vector<int> vcmp;
	for(auto &i : edg){
		vcmp.push_back(disj.find(i.s));
		vcmp.push_back(disj.find(i.e));
	}
	sort(vcmp.begin(), vcmp.end());
	vcmp.resize(unique(vcmp.begin(), vcmp.end()) - vcmp.begin());
	auto NORM = [&](int x){
		int rn = lower_bound(vcmp.begin(), vcmp.end(), disj.find(x)) - vcmp.begin();
		return rn;
	};
	for(auto &i : edg){
		i.s = NORM(i.s);
		i.e = NORM(i.e);
		gph[i.e].push_back(pi(i.s, i.x));
	}
	memset(dp, -1, sizeof(dp));
	for(auto &i : digits){
		i.first = NORM(i.first);
		dp[i.first] = i.second;
	}
	for(auto &i : gates){
		type[NORM(i.first)] = i.second;
	}
	for(int i='A'; i<='Z'; i++){
		if(mp[i] == 0) continue;
		mp[i] = NORM(mp[i]);
		printf("%c=%d\n",i,f(mp[i]));
	}
}

int main(){
	auto getl = [&]{
		char buf[205] = {};
		fgets(buf, 205, stdin);
		int l = strlen(buf) - 1;
		while(l >= 0 && isspace(buf[l])) buf[l--] = 0;
		string s = buf;
		return s;
	};
	while(true){
		v.clear();
		disj.init(100005);
		memset(mp, 0, sizeof(mp));
		memset(cmp, 0, sizeof(cmp));
		memset(type, 0, sizeof(type));
		for(int i=0; i<100005; i++) gph[i].clear();
		string s = getl();
		if(s == "*") break;
		while(true){
			v.push_back(s);
			s = getl();
			if(s[0] == '*') break;
		}
		solve();
		puts("");
	}
}

