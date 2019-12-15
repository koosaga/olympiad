#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 205;
const int mod = 1e9 + 7;

struct edge{
	int s, e;
	char x;
};

struct NFA{
	vector<edge> edg;
	int src, snk, vn;
	NFA(){ vn = 0; }
	NFA(char c){
		assert(isalpha(c));
		edg.push_back({0, 1, c});
		src = 0, snk = 1, vn = 2;
	}
	void kleene(){
		edg.push_back({snk, vn, -1});
		edg.push_back({vn, src, -1});
		snk = src = vn;
		vn++;
	}
	NFA operator|(const NFA &r){
		NFA nxt;
		nxt.vn = vn + r.vn + 2;
		nxt.src = 0;
		nxt.snk = 1;
		nxt.edg.push_back({0, src + 2, -1});
		nxt.edg.push_back({0, vn + r.src + 2, -1});
		nxt.edg.push_back({snk + 2, 1, -1});
		nxt.edg.push_back({vn + r.snk + 2, 1, -1});
		for(auto &i : edg) nxt.edg.push_back({i.s + 2, i.e + 2, i.x});
		for(auto &i : r.edg) nxt.edg.push_back({i.s + 2 + vn, i.e + 2 + vn, i.x});
		return nxt;
	}
	NFA operator+(const NFA &r){
		NFA nxt;
		nxt.vn = vn + r.vn;
		nxt.src = src;
		nxt.snk = vn + r.snk;
		nxt.edg.push_back({snk, r.src + vn, -1});
		for(auto &i : edg) nxt.edg.push_back({i.s, i.e, i.x});
		for(auto &i : r.edg) nxt.edg.push_back({i.s + vn, i.e + vn, i.x});
		return nxt;
	}
};

NFA parse(string S){
	if(sz(S) == 1){
		return NFA(S[0]);
	}
	vector<string> tok;
	int cnt = 0;
	string cur;
	for(int i=0; i<sz(S); i++){
		if(S[i] == '('){
			cnt++;
		}
		if(cnt > 0){
			cur.push_back(S[i]);
		}
		else{
			tok.push_back(S.substr(i, 1));
		}
		if(S[i] == ')'){
			cnt--;
			if(cnt == 0){
				tok.push_back(cur);
				cur.clear();
			}
		}
	}
	if(sz(tok) == 1){
		return parse(tok[0].substr(1, sz(tok[0]) - 2));
	}
	for(int i=0; i<sz(tok); i++){
		if(tok[i] == "|"){
			string L, R;
			for(int j=0; j<i; j++) L = L + tok[j];
			for(int j=i+1; j<sz(tok); j++) R = R + tok[j];
			return parse(L) | parse(R);
		}
	}
	vector<NFA> stk;
	for(auto &i : tok){
		if(i == "*"){
			assert(sz(stk));
			stk.back().kleene();
		}
		else{
			stk.push_back(parse(i));
		}
	}
	for(int i=1; i<sz(stk); i++) stk[0] = stk[0] + stk[i];
	return stk[0];
}

struct node{
	int x, y, dist;
};

int dist[MAXN][MAXN][2];
vector<pi> g1[MAXN];
vector<pi> g2[MAXN];
edge par[MAXN][MAXN][2];

void solve(){
	string s, t; 
	cin >> s >> t;
	NFA x = parse(s);
	NFA y = parse(t);
	for(auto &i : x.edg){
		g1[i.s].emplace_back(i.x, i.e);
	}
	for(auto &i : y.edg){
		g2[i.s].emplace_back(i.x, i.e);
	}
	deque<node> dq;
	auto enqb = [&](int x, int y, int d, edge parv){
		if(dist[x][y][d > 0] > d){
			dist[x][y][d > 0] = d;
			par[x][y][d > 0] = parv;
			dq.push_back({x, y, d});
		}
	};
	auto enqf = [&](int x, int y, int d, edge parv){
		if(dist[x][y][d > 0] > d){
			dist[x][y][d > 0] = d;
			par[x][y][d > 0] = parv;
			dq.push_front({x, y, d});
		}
	};
	memset(dist, 0x3f, sizeof(dist));
	enqf(x.src, y.src, 0, (edge){-1, -1, -1});
	while(sz(dq)){
		auto x = dq.front(); dq.pop_front();
		if(dist[x.x][x.y][x.dist > 0] != x.dist) continue;
		for(auto &i : g1[x.x]){
			if(i.first == -1) enqf(i.second, x.y, x.dist, (edge){x.x, x.y, -1});
		}
		for(auto &i : g2[x.y]){
			if(i.first == -1) enqf(x.x, i.second, x.dist, (edge){x.x, x.y, -1});
		}
		for(auto &i : g1[x.x]){
			for(auto &j : g2[x.y]){
				if(i.first != -1 && i.first == j.first){
					enqb(i.second, j.second, x.dist + 1, (edge){x.x, x.y, (char)i.first});
				}
			}
		}
	}
	if(dist[x.snk][y.snk][1] > 1e7){
		puts("Correct");
		return;
	}
	else{
		puts("Wrong");
		int disval = dist[x.snk][y.snk][1];
		pi p(x.snk, y.snk);
		string ans;
		while(disval > sz(ans)){
			auto v = par[p.first][p.second][1];
			if(v.x != -1) ans.push_back(v.x);
			p.first = v.s;
			p.second = v.e;
		}
		reverse(all(ans));
		cout << ans << endl;
	}
}

int main(){
	solve();
}
