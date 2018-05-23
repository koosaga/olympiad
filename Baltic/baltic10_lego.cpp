#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
using pi = pair<int, int>;
const int mod = 1e9 + 9;
const int MAXN = 505;

void bktk(int x, int y, vector<vector<pi>> &ret, vector<pi> &cur){
	if(x == 5){
		ret.push_back(cur);
		return;
	}
	if(y == 5){
		bktk(x+1, 0, ret, cur);
		return;
	}
	bktk(x, y+1, ret, cur);
	bool ok = true;
	for(auto &i : cur){
		if(i == pi(x-1, y) || i == pi(x, y-1) || i == pi(x-1, y-1) || i == pi(x-1, y+1)){
			ok = false;
		}
	}
	if(ok){
		cur.push_back(pi(x, y));
		bktk(x, y+1, ret, cur);
		cur.pop_back();
	}
}

struct blk{
	vector<pi> v;
	int possib;
};

int n;
vector<blk> v[6];
vector<lint> dp[6];
char str[2][7][7];

int verify(vector<pi> x, string l, string r){
	vector<pi> skyl(6, pi(-1, -1)), skyr(6, pi(-1, -1));
	for(int i=0; i<x.size(); i++){
		skyl[x[i].first] = max(skyl[x[i].first], pi(10-x[i].second+1, i));
		skyl[x[i].first+1] = max(skyl[x[i].first+1], pi(10-x[i].second+1, i));
		skyr[x[i].second] = max(skyr[x[i].second], pi(x[i].first+1, i));
		skyr[x[i].second+1] = max(skyr[x[i].second+1], pi(x[i].first+1, i));
	}
	set<int> idx[10];
	for(int i=0; i<6; i++){
		if(l[i] == '.' && skyl[i] != pi(-1, -1)) return -1;
		if(r[i] == '.' && skyr[i] != pi(-1, -1)) return -2;
		if(l[i] != '.'){
			if(skyl[i] == pi(-1, -1)) return -3;
			idx[skyl[i].second].insert(l[i]);
		}
		if(r[i] != '.'){
			if(skyr[i] == pi(-1, -1)) return -4;
			idx[skyr[i].second].insert(r[i]);
		}
	}
	int cnt = 1;
	for(int i=0; i<x.size(); i++){
		if(idx[i].size() == 0) cnt *= 3;
		if(idx[i].size() >= 2) return -5;
	}
	return cnt;
}

bool stab(lint val, vector<pi> &b){
	for(auto &i : b){
		lint tmp = (195ll << (i.first * 6 + i.second));
		if((tmp & val) == 0) return false;
	}
	return true;

}

int main(){
	cin >> n;
	for(int i=0; i<n; i++) cin >> str[0][n-i-1];
	for(int i=0; i<n; i++) cin >> str[1][n-i-1];
	vector<vector<pi> > gen;
	vector<pi> mt;
	bktk(0, 0, gen, mt);
	for(int i=0; i<n; i++){
		string l = str[0][i];
		string r = str[1][i];
		for(auto &x : gen){
			int ret = verify(x, l, r);
			if(ret <= -1) continue;
			v[i].push_back({x, ret});
		}
		dp[i].resize(v[i].size());
		if(i == 0){
			for(int j=0; j<v[i].size(); j++) dp[i][j] = v[i][j].possib;
		}
	}
	for(int i=1; i<n; i++){
		for(int k=0; k<v[i-1].size(); k++){
			if(dp[i-1][k] == 0) continue;
			lint msk = 0;
			for(auto &x : v[i-1][k].v){
				msk |= 195ll << (x.first * 6 + x.second);
			}
			for(int j=0; j<v[i].size(); j++){
				if(stab(msk, v[i][j].v)) dp[i][j] += dp[i-1][k];
			}
		}
		for(int j=0; j<v[i].size(); j++) dp[i][j] *= v[i][j].possib;
	}
	cout << accumulate(dp[n-1].begin(), dp[n-1].end(), 0ll) << endl;
}
