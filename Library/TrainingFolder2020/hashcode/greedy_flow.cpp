#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <string>
#include <bitset>
#include <map>
#include <set>
#include <tuple>
#include <string.h>
#include <math.h>
#include <random>
#include <functional>
#include <assert.h>
#include <math.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using pi = pair<int, int>;
using lint = long long;
const int MAXN = 205005;

namespace MCMF{
	struct edg{ int pos, cap, rev, cost; };
	vector<edg> gph[MAXN];
	void clear(){ for(int i=0; i<MAXN; i++) gph[i].clear(); }
	void add_edge(int s, int e, int x, int c){
		gph[s].push_back({e, x, (int)gph[e].size(), c});
		gph[e].push_back({s, 0, (int)gph[s].size()-1, -c});
	}
	int phi[MAXN], inque[MAXN], dist[MAXN];
	void prep(int src, int sink){
		memset(phi, 0x3f, sizeof(phi));
		memset(dist, 0x3f, sizeof(dist));
		queue<int> que;
		que.push(src);
		inque[src] = 1;
		while(!que.empty()){
			int x = que.front();
			que.pop();
			inque[x] = 0;
			for(auto &i : gph[x]){
				if(i.cap > 0 && phi[i.pos] > phi[x] + i.cost){
					phi[i.pos] = phi[x] + i.cost;
					if(!inque[i.pos]){
						inque[i.pos] = 1;
						que.push(i.pos);
					}
				}
			}
		}
		for(int i=0; i<MAXN; i++){
			for(auto &j : gph[i]){
				if(j.cap > 0) j.cost += phi[i] - phi[j.pos];
			}
		}
		priority_queue<pi, vector<pi>, greater<pi> > pq;
		pq.push(pi(0, src));
		dist[src] = 0;
		while(!pq.empty()){
			auto l = pq.top();
			pq.pop();
			if(dist[l.second] != l.first) continue;
			for(auto &i : gph[l.second]){
				if(i.cap > 0 && dist[i.pos] > l.first + i.cost){
					dist[i.pos] = l.first + i.cost;
					pq.push(pi(dist[i.pos], i.pos));
				}
			}
		}
	}
	bool vis[MAXN];
	int ptr[MAXN];
	int dfs(int pos, int sink, int flow){
		vis[pos] = 1;
		if(pos == sink) return flow;
		for(; ptr[pos] < gph[pos].size(); ptr[pos]++){
			auto &i = gph[pos][ptr[pos]];
			if(!vis[i.pos] && dist[i.pos] == i.cost + dist[pos] && i.cap > 0){
				int ret = dfs(i.pos, sink, min(i.cap, flow));
				if(ret != 0){
					i.cap -= ret;
					gph[i.pos][i.rev].cap += ret;
					return ret;
				}
			}
		}
		return 0;
	}
	int match(int src, int sink, int sz){
		prep(src, sink);
		for(int i=0; i<sz; i++) dist[i] += phi[sink] - phi[src];
		int ret = 0;
		while(true){
			memset(ptr, 0, sizeof(ptr));
			memset(vis, 0, sizeof(vis));
			int tmp = 0;
			while((tmp = dfs(src, sink, 1e9))){
				ret += dist[sink] * tmp;
				memset(vis, 0, sizeof(vis));
			}
			tmp = 1e9;
			for(int i=0; i<sz; i++){
				if(!vis[i]) continue;
				for(auto &j : gph[i]){
					if(j.cap > 0 && !vis[j.pos]){
						tmp = min(tmp, (dist[i] + j.cost) - dist[j.pos]);
					}
				}
			}
			if(tmp > 1e9 - 200) break;
			for(int i=0; i<sz; i++){
				if(!vis[i]) dist[i] += tmp;
			}
		}
		return ret;
	}
}

int B, L, D;
int score[MAXN];

struct output_buffer {
	vector<vector<int>> v;
	void print(vector<int> w) {
		v.push_back(w);
	}
	void flush() {
		cout << sz(v) / 2 << endl;
		for (auto &i : v) {
			for (auto &j : i) {
				printf("%d ", j);
			}
			puts("");
		}
	}
}buf;

struct library {
	int signup, speed, id;
	vector<int> books;
}a[MAXN];

bool vis[MAXN];
bool procing[MAXN];

int extract_idx(int dates) {
	pair<double, int> ret(-1, -1);
	for (int i = 0; i<L; i++) {
		if (vis[i] || dates <= a[i].signup) continue;
		sort(all(a[i].books), [&](const int &a, const int &b) {
				return score[a] > score[b];
				});
		int siz = (int)min(1ll * (dates - a[i].signup) * a[i].speed, 1ll * sz(a[i].books));
		lint accm = 0;
		for (int j = 0; j < siz; j++)
			accm += score[a[i].books[j]];
		ret = max(ret, make_pair(1.0 * accm / pow(a[i].signup, 0.9), i));
	}
	return ret.second;
}
int main() {
	int orig_score[MAXN];
	cin >> B >> L >> D;
	for (int i = 0; i<B; i++) cin >> score[i];
	memcpy(orig_score, score, sizeof(score));
	for (int i = 0; i<L; i++) {
		int siz;
		cin >> siz >> a[i].signup >> a[i].speed;
		a[i].id = i;
		a[i].books.resize(siz);
		for (auto &j : a[i].books) {
			scanf("%d", &j);
		}
	}
	int tick = 0;
	vector<int> v;
	while (tick < D) {
		int i = extract_idx(D - tick);
		if (i == -1) break;
		vis[i] = 1;
		tick += a[i].signup;
		int siz = (int)min(1ll * (D - tick) * a[i].speed, 1ll * sz(a[i].books));
		assert(siz > 0);
		v.push_back(i);
		for(int j=0; j<siz; j++){
			score[a[i].books[j]] = 0;
		}
	}
	memcpy(score, orig_score, sizeof(score));
	tick = 0;
	for(int i=0; i<sz(v); i++){
		tick += a[v[i]].signup;
		int siz = (int)min(1ll * (D - tick) * a[v[i]].speed, 1ll * sz(a[v[i]].books));
		MCMF::add_edge(0, i + 1, siz, 0);
		for(auto &j : a[v[i]].books){
			MCMF::add_edge(i + 1, sz(v) + j + 1, 1, 0);
		}
	}
	for(int i=0; i<B; i++){
		MCMF::add_edge(sz(v) + i + 1, sz(v) + B + 1, 1, -score[i]);
	}
	MCMF::match(0, sz(v) + B + 1, sz(v) + B + 2);
	for(int i=0; i<sz(v); i++){
		vector<int> novo;
		for(auto &j : MCMF::gph[i + 1]){
			if(j.cap == 0 && j.pos > sz(v)){
				novo.push_back(j.pos - sz(v) - 1);
			}
		}
		buf.print({a[v[i]].id,  sz(novo)});
		buf.print(novo);
	}
	buf.flush();
}
