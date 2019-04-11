#include <bits/stdc++.h>
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 100005;

struct program{
	bool isEmpty;
	int start, end;
	lint adj[13][13];
	void init(){
		isEmpty = start = end = 0;
		memset(adj, 0, sizeof(adj));
	}
}prog;

char buf[20];

program Empty(){
	program p; p.isEmpty = 1; return p;
}

program Single(int n){
	program p; 
	p.init();
	p.start = p.end = n;
	p.adj[n][n] = 1;
	return p;
}

program Multiply(program x, int n){
	for(int i=0; i<13; i++){
		for(int j=0; j<13; j++){
			x.adj[i][j] *= n;
		}
	}
	if(x.start != x.end) x.adj[x.end][x.start] += n - 1;
	return x;
}

program merge(program x, program y){
	if(x.isEmpty) return y;
	if(y.isEmpty) return x;
	program p;
	p.isEmpty = 0, p.start = x.start, p.end = y.end;
	for(int i=0; i<13; i++){
		for(int j=0; j<13; j++){
			p.adj[i][j] = x.adj[i][j] + y.adj[i][j];
		}
	}
	if(y.start != x.end) p.adj[x.end][y.start]++;
	return p;
}

int n;

vector<program> read_prog(){
	if(scanf("%s", buf) == -1){
		vector<program> v(1<<n);
		program empt = Empty();
		fill(v.begin(), v.end(), empt);
		return v;
	}
	if(buf[0] == 'E'){
		vector<program> v(1<<n);
		program empt = Empty();
		fill(v.begin(), v.end(), empt);
		return v;
	}
	if(buf[0] == 'V'){
		int m; sscanf(buf + 1, "%d", &m);
		m--;
		auto ans = read_prog();
		for(int i=0; i<(1<<n); i++){
			if((i >> m) % 2 == 0) ans[i] = merge(Single(m), ans[i]);
		}
		return ans;
	}
	if(buf[0] == 'R'){
		int m; sscanf(buf + 1, "%d", &m);
		auto ans = read_prog();
		for(auto &i : ans) i = Multiply(i, m);
		auto ans2 = read_prog();
		for(int i=0; i<ans.size(); i++) ans[i] = merge(ans[i], ans2[i]);
		return ans;
	}
}

int b, s, popcnt[1<<13];
lint cliqued[1<<13], mskReceive[1<<13];
lint dap = 1e18;

void bktk(int k, int msk, vector<int> &v){
	if(msk == 0){
		lint ret = 0;
		int mskSum = 0;
		for(int i=0; i<v.size(); i++){
			ret -= cliqued[v[i]];
			mskSum |= v[i];
		}
		ret += cliqued[mskSum];
		dap = min(dap, ret);
		return;
	}
	if(k == 0) return;
	int maxbit = 0;
	for(int i=n-1; i>=0; i--){
		if(msk >> i){
			maxbit = i;
			break;
		}
	}
	for(int j=msk; j>=(1<<maxbit); j=(j-1)&msk){
		if(popcnt[j] > s) continue;
		v.push_back(j);
		bktk(k - 1, msk & (~j), v);
		v.pop_back();
	}
}

int main(){
	cin >> b >> s;
	n = min(b * s, 13);
	auto buf = read_prog();
	for(int i=1; i<(1<<n); i++){
		popcnt[i] = popcnt[i - (i & -i)] + 1;
	}
	s = min(s, n);
	for(int i=1; i<(1<<n); i++){
		if(popcnt[i] != s) continue;
		prog = buf[i];
		if(prog.isEmpty){
			dap = -1;
			break;
		}
		memset(cliqued, 0, sizeof(cliqued));
		int w = (1<<n) - 1 - i;
		for(int msk = w; msk > 0; msk = (msk - 1) & w){
			for(int j=0; j<n; j++){
				for(int k=0; k<n; k++){
					if((msk >> j) % 2 == 1 && (msk >> k) % 2 == 1){
						cliqued[msk] += prog.adj[j][k];
					}
				}
			}
		}
		vector<int> maskes;
		bktk(b - 1, w, maskes);
	}
	dap++;
	for(int i=0; i<n; i++) dap += buf[0].adj[i][i];
	cout << dap << endl;
}
