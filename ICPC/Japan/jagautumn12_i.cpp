#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define move fuck
using namespace std;
const int MAXN = 35;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<int, int>;

inline int GET(int msk, int val){ return ((msk >> val) & 1); }

struct state{
	int par[4], sz[4], color[4];
	lint ret;
};

vector<state> leaf_state, rect_state;

void do_renumber(state &st, int x, int y){
	swap(st.par[x], st.par[y]);
	swap(st.sz[x], st.sz[y]);
	swap(st.color[x], st.color[y]);
	for(int i=0; i<4; i++){
		if(st.par[i] == x) st.par[i] = y;
		else if(st.par[i] == y) st.par[i] = x;
	}
}

void do_uni(state &s, int x, int y){
	if(s.color[x] == s.color[y] && s.par[x] != s.par[y]){
		int minv = min(s.par[x], s.par[y]);
		int maxv = max(s.par[x], s.par[y]);
		s.sz[minv] += s.sz[maxv];
		int wantsz = s.sz[minv];
		for(int j=0; j<4; j++){
			if(s.par[j] == minv){
				s.sz[j] = wantsz;
			}
			if(s.par[j] == maxv){
				s.par[j] = minv;
				s.sz[j] = wantsz;
			}
		}
	}
}

void init_state(){
	leaf_state.resize(16);
	rect_state.resize(16);
	for(int i=0; i<16; i++){
		for(int j=0; j<4; j++){
			leaf_state[i].par[j]   = j;
			leaf_state[i].sz[j]    = 1;
			leaf_state[i].color[j] = GET(i, j);
		}
		leaf_state[i].ret = 1;
		do_uni(leaf_state[i], 0, 2);
		do_uni(leaf_state[i], 1, 3);
		do_uni(leaf_state[i], 2, 3);
		rect_state[i] = leaf_state[i];
		do_uni(rect_state[i], 0, 1);
	}
}

int n, k, a[MAXN];
vector<pi> gph[MAXN];
int par[MAXN], pae[MAXN];

vector<state> solve(int x){
	int nxtLink[MAXN];
	memset(nxtLink, -1, sizeof(nxtLink));
	for(auto &i : gph[x]){
		if(i.second != par[x]){
			nxtLink[i.first] = i.second;
		}
	}
	vector<vector<state>> st(a[x] + 2);
	for(int i=1; i<=a[x]; i++){
		if(nxtLink[i] == -1) st[i] = rect_state;
		else st[i] = solve(nxtLink[i]);
	}
	lint up_state[2][2][9][9] = {};
	lint dn_state[2][2][9][9] = {};
	for(auto &x : leaf_state){
		if(*max_element(x.sz, x.sz + 4) <= k){
			up_state[x.color[2]][x.color[3]][x.sz[2]][x.sz[3]] += x.ret;
			dn_state[x.color[2]][x.color[3]][x.sz[2]][x.sz[3]] += x.ret;
		}
	}
	if(x == 0){
		memset(dn_state, 0, sizeof(dn_state));
		dn_state[0][0][1][1] = dn_state[0][1][1][1] = dn_state[1][0][1][1] = dn_state[1][1][1][1] = 1;
	}
	for(int i=1; i<=pae[x] - 1; i++){
		lint nxt_state[2][2][9][9] = {};
		for(int p = 1; p <= k; p++){
			for(int q = 1; q <= k; q++){
				for(auto x : st[i]){
					lint prv_state = up_state[x.color[0]][x.color[1]][p][q];
					if(!prv_state) continue;
					assert((x.color[0] != x.color[1]) || (p == q));
					assert((x.color[0] != x.color[1]) || x.sz[0] == x.sz[1]);
					assert((x.color[0] != x.color[1]) ^ (x.par[0] == x.par[1]));
					assert(x.par[0] != x.par[1] || p >= 2);
					if(x.par[0] == x.par[1]){
						for(int j=0; j<4; j++){
							if(x.par[j] == x.par[0]) x.sz[j] += p - 2;
						}
					}
					else{
						for(int j=0; j<4; j++){
							if(x.par[j] == x.par[0]) x.sz[j] += p - 1;
							if(x.par[j] == x.par[1]) x.sz[j] += q - 1;
						}
					}
					if(*max_element(x.sz, x.sz + 4) <= k){
						nxt_state[x.color[2]][x.color[3]][x.sz[2]][x.sz[3]] += prv_state * x.ret % mod;
					}
				}
			}
		}
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				for(int k=0; k<9; k++){
					for(int l=0; l<9; l++){
						up_state[i][j][k][l] = nxt_state[i][j][k][l] % mod;
						if(up_state[i][j][k][l] && i == j) assert(k == l);
					}
				}
			}
		}
	}
	for(int i=a[x]; i>=pae[x] + 1; i--){
		lint nxt_state[2][2][9][9] = {};
		for(int p = 1; p <= k; p++){
			for(int q = 1; q <= k; q++){
				for(auto x : st[i]){
					lint prv_state = dn_state[x.color[2]][x.color[3]][p][q];
					if(!prv_state) continue;
					assert((x.color[2] != x.color[3]) || (p == q));
					assert((x.color[2] != x.color[3]) || x.sz[2] == x.sz[3]);
					assert((x.color[2] != x.color[3]) ^ (x.par[2] == x.par[3]));
					assert(x.par[2] != x.par[3] ||p >= 2);
					if(x.par[2] == x.par[3]){
						for(int j=0; j<4; j++){
							if(x.par[j] == x.par[2]) x.sz[j] += p - 2;
						}
					}
					else{
						for(int j=0; j<4; j++){
							if(x.par[j] == x.par[2]) x.sz[j] += p - 1;
							if(x.par[j] == x.par[3]) x.sz[j] += q - 1;
						}
					}
					if(*max_element(x.sz, x.sz + 4) <= k){
						nxt_state[x.color[0]][x.color[1]][x.sz[0]][x.sz[1]] += prv_state * x.ret % mod;
					}
				}
			}
		}
		for(int i=0; i<2; i++){
			for(int j=0; j<2; j++){
				for(int k=0; k<9; k++){
					for(int l=0; l<9; l++){
						dn_state[i][j][k][l] = nxt_state[i][j][k][l] % mod;
						if(dn_state[i][j][k][l] && i == j) assert(k == l);
					}
				}
			}
		}
	}
	vector<state> ret;
	for(int i=0; i<16; i++){
		for(int p=1; p<=k; p++){
			for(int q=1; q<=k; q++){
				for(int r=1; r<=k; r++){
					for(int s=1; s<=k; s++){
						state st;
						st.ret = up_state[GET(i, 0)][GET(i, 1)][p][q] * dn_state[GET(i, 2)][GET(i, 3)][r][s] % mod;
						if(!st.ret) continue;
						for(int j=0; j<4; j++){
							st.color[j] = GET(i, j);
							st.sz[j] = vector<int>{p, q, r, s}[j];
							st.par[j] = j;
						}
						if(x != 0 && st.color[2] == st.color[3]){
							assert(st.sz[2] == st.sz[3]);
							st.par[3] = 2;
						}
						if(st.color[0] == st.color[1]){
							assert(st.sz[0] == st.sz[1]);
							st.par[1] = 0;
						}
						do_uni(st, 0, 2);
						do_uni(st, 1, 3);
						if(*max_element(st.sz, st.sz + 4) <= k){
							do_renumber(st, 1, 2);
							/*
							printf("%d %d %d %d %d %d %d %d %d %lld\n", 
							x, st.color[0], st.color[1], st.color[2], st.color[3],
							st.sz[0], st.sz[1], st.sz[2], st.sz[3],
							st.ret);*/
							ret.push_back(st);
						}
					}
				}
			}
		}
	}
	return ret;
}

void dfs(int x, int p){
	for(auto &i : gph[x]){
		if(i.second == p){
			par[x] = p;
			pae[x] = i.first;
		}
		else dfs(i.second, x);
	}
}

int main(){
	init_state();
	while(true){
		for(int i=0; i<MAXN; i++) gph[i].clear();
		scanf("%d %d",&n,&k);
		if(n + k == 0) break;
		for(int i=0; i<n; i++) scanf("%d",&a[i]);
		for(int i=0; i<n-1; i++){
			int s, e, x, y; scanf("%d %d %d %d",&s,&x,&e,&y);
			x++;
			y++;
			gph[s].emplace_back(x, e);
			gph[e].emplace_back(y, s);
		}
		dfs(0, -1);
		pae[0] = a[0] + 1;
		auto ans = solve(0);
		lint ret = 0;
		for(auto &i : ans) ret += i.ret;
		printf("%lld\n", ret % mod);
	}
}
