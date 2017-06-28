#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int mod = 1234567;

vector<int> m[20005][5];
vector<int> gph[20005];
int n, q, p[20005], p10[6];
vector<lint> mem[20005][5];
lint dp[20005], mul[20005];

struct event1{
	int lst, pos, end;
	lint val;
	int priority, in;
	bool operator<(const event1 &ev)const{
		return pos < ev.pos;
	}
};

struct event2{
	int priority, endtime;
	lint value;
	bool operator<(const event2 &ev)const{
		return priority < ev.priority;
	}
};

struct event3{
	int s, e, x;
};

struct seg{
	int tree[132000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(tree, tree + 2 * lim, 1);
	}
	void upd(int s, int e, int x){
		s += lim;
		e += lim;
		while(s < e){
			if(s%2 == 1){
				tree[s] = 1ll * tree[s] * x % mod;
				s++;
			}
			if(e%2 == 0){
				tree[e] = 1ll * tree[e] * x % mod;
				e--;
			}
			s >>= 1; 
			e >>= 1;
		}
		if(s == e) tree[s] = 1ll * tree[s] * x % mod;
	}
	int query(int x){
		x += lim;
		int ret = 1;
		while(x){
			ret = 1ll * ret * tree[x] % mod;
			x >>= 1;
		}
		return ret;
	}
}seg[4];

void dfs(int pos){
	mul[pos] = 1;
	vector<event3> qry[4];

	for(auto &son : gph[pos]){
		dfs(son);
		mul[pos] = (mul[pos] * dp[son]) % mod;
		vector<event1> ev1[4];

		for(int i=1; i<5; i++){
			for(int j=0; j<10; j++){
				ev1[i-1].push_back({j, 0, (int)m[pos][i-1].size(), mul[son], 0, 1});
				ev1[i-1].push_back({j, (int)m[pos][i-1].size(), (int)m[pos][i-1].size(), mul[son], 0, -1});
			}
		}

		for(int len = 1; len <= 5; len++){
			for(int mat = 0; mat < m[son][len - 1].size(); mat++){
				lint wapp = (len == 5 ? 0 : mem[son][len - 1][mat]);
				int po = m[son][len - 1][mat] % p10[len - 1];
				int l = m[son][len - 1][mat] / p10[len - 1];
				for(int nlen = len - 1; nlen < 5; nlen++){
					if(nlen == 0) continue;
					int s = po * p10[nlen - len + 1];
					int e = (po + 1) * p10[nlen - len + 1];
					s = lower_bound(m[pos][nlen - 1].begin(), m[pos][nlen - 1].end(), s) - m[pos][nlen - 1].begin();
					e = lower_bound(m[pos][nlen - 1].begin(), m[pos][nlen - 1].end(), e) - m[pos][nlen - 1].begin();
					if(s < e){
						ev1[nlen - 1].push_back({l, s, e, wapp, len, 1});
						ev1[nlen - 1].push_back({l, e, e, wapp, len, -1});
					}
				}
			}
		}

		for(int i=1; i<5; i++){
			priority_queue<event2> pq[10];
			sort(ev1[i-1].begin(), ev1[i-1].end());
			for(int j=0; j<ev1[i-1].size(); ){
				int e = j;
				while(e < ev1[i-1].size() && ev1[i-1][j].pos == ev1[i-1][e].pos) e++;
				if(e == ev1[i-1].size()) break;
				for(int k=j; k<e; k++){
					event1 cur = ev1[i-1][k];
					if(cur.in == 1){
						pq[cur.lst].push({cur.priority, cur.end, cur.val});
					}
				}
				int sum = 0;
				for(int k=0; k<10; k++){
					while(!pq[k].empty() && pq[k].top().endtime <= ev1[i-1][j].pos) pq[k].pop();
					assert(!pq[k].empty());
					sum += pq[k].top().value;
				}
				qry[i-1].push_back({ev1[i-1][j].pos, ev1[i-1][e].pos-1, sum % mod});
				j = e;
			}
		}
	}

	for(int i=0; i<4; i++){
		seg[i].init(m[pos][i].size());
		for(auto &j : qry[i]){
			seg[i].upd(j.s, j.e, j.x);
		}
		for(int j=0; j<m[pos][i].size(); j++){
			mem[pos][i][j] = seg[i].query(j);
		}
	}

	for(int i=0; i<10; i++){
		auto l = lower_bound(m[pos][0].begin(), m[pos][0].end(), i);
		if(l != m[pos][0].end() && *l == i) dp[pos] += mem[pos][0][l - m[pos][0].begin()];
		else dp[pos] += mul[pos];
	}
	dp[pos] %= mod;
}

int main(){
	p10[0] = 1;
	p10[1] = 10;
	p10[2] = 100;
	p10[3] = 1000;
	p10[4] = 10000;
	p10[5] = 100000;
	scanf("%d %d",&n,&q);
	for(int i=1; i<n; i++){
		scanf("%d",&p[i]);
		gph[p[i]].push_back(i);
	}
	for(int i=0; i<q; i++){
		int v, k = 0;
		char str[10];
		scanf("%d %s",&v, str);
		for(int i=0; i<5; i++){
			k = k * 10 + str[i] - '0';
		}
		for(int j=0; j<5; j++){
			m[v][4-j].push_back(k);
			k %= p10[4 - j];
			v = p[v];
		}
	}
	lint cur = 1;
	for(int i=0; i<n; i++){
		cur *= 10;
		cur %= mod;
		for(int j=0; j<5; j++){
			sort(m[i][j].begin(), m[i][j].end());
			m[i][j].resize(unique(m[i][j].begin(), m[i][j].end()) - m[i][j].begin());
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<5; j++){
			mem[i][j].resize(m[i][j].size(), 1);
		}
	}
	dfs(0);
	cout << (cur - dp[0] + mod) % mod << endl;
}
