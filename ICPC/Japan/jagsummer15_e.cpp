#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, m, q;
pi a[100005];
bool vis[100005];
 
vector<int> gph[100005];
vector<int> v;
 
void dfs(int x){
	if(vis[x]) return;
	v.push_back(x);
	vis[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
	}
}
 
lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}
 
bool cmp(int p, int q, int i){
	if(p == q) return 0;
	int dx1 = a[p].first - a[i].first;
	int dy1 = a[p].second - a[i].second;
	int dx2 = a[q].first - a[i].first;
	int dy2 = a[q].second - a[i].second;
	if(dy1 == 0 && dx1 > 0) return 1;
	if(dy2 == 0 && dx2 > 0) return 0; 
	if(1ll * dy1 * dy2 <= 0) return dy1 > dy2;
	return ccw(a[i], a[p], a[q]) > 0;
}
 
struct line{
	pi s, e;
	int mode, idx;
	bool operator==(const line &l)const{
		return idx == l.idx;
	}
};
 
struct sweep{
	int pos;
	line l;
};
 
struct query{
	int x, y, idx;
};
 
int ret[100005];
 
vector<sweep> ins, del;
vector<query> qry;
 
int piv;
 
void add_edge(int s, int e){
	if(a[s].first < a[e].first){
		ins.push_back({a[s].first, {a[s], a[e], 1, piv}}); 
		del.push_back({a[e].first, {a[s], a[e], 1, piv}}); 
		piv++;
	}
	if(a[s].first > a[e].first){
		ins.push_back({a[e].first, {a[e], a[s], -1, piv}}); 
		del.push_back({a[s].first, {a[e], a[s], -1, piv}}); 
		piv++;
	}
}
 
double crs(line a, double x){
	double rat = 1.0 * (x - a.s.first) / (a.e.first - a.s.first);
	return a.s.second + (a.e.second - a.s.second) * rat;
}
 
line bkt[505][805];
int idxbkt[200005], sz[505], sum[505], cnt;
 
void reinit(){
	vector<line> col;
	for(int i=0; i<500; i++){
		for(int j=0; j<sz[i]; j++){
			col.push_back(bkt[i][j]);
		}
		sz[i] = sum[i] = 0;
	}
	assert(cnt == col.size());
	for(int i=0; i<500; i++){
		for(int j=0; j<400 && 400 * i + j < col.size(); j++){
			bkt[i][j] = col[400*i+j];
			idxbkt[bkt[i][j].idx] = i;
			sz[i]++;
			sum[i] += bkt[i][j].mode;
		}
	}
}
 
void bkt_ins(line a, int x){
	double y = crs(a, x+ 0.5);
	for(int j=499; j>=0; j--){
		if(sz[j] == 0) continue;
		if(crs(bkt[j][0], x + 0.5) <= y){
			int low = -1;
			for(int k=0; k<sz[j]; k++){
				if(crs(bkt[j][k], x + 0.5) <= y){
					low = k+1;
				}
			}
			assert(low != -1);
			for(int k=sz[j]; k>low; k--){
				bkt[j][k] = bkt[j][k-1];
			}
			bkt[j][low] = a;
			idxbkt[a.idx] = j;
			sz[j]++;
			sum[j] += a.mode;
			cnt++;
			if(sz[j] > 800) reinit();
			return;
		}
	}
	for(int k=sz[0]; k; k--){
		bkt[0][k] = bkt[0][k-1];
	}
	bkt[0][0] = a;
	idxbkt[a.idx] = 0;
	sz[0]++;
	sum[0] += a.mode;
	cnt++;
	if(sz[0] > 800) reinit();
}
 
void bkt_del(line a, int x){
	cnt--;
	int p = idxbkt[a.idx];
	int sentinel = -1;
	for(int i=0; i<sz[p]; i++){
		if(bkt[p][i] == a){
			sentinel = i;
			break;
		}
	}
	assert(sentinel != -1);
	sz[p]--;
	sum[p] -= bkt[p][sentinel].mode;
	for(int i=sentinel; i<sz[p]; i++){
		bkt[p][i] = bkt[p][i+1];
	}
}
 
int bkt_qry(int x, int y){
	int ret = 0;
	for(int i=0; i<500; i++){
		if(sz[i] == 0) continue;
		if(crs(bkt[i][sz[i] - 1], x) <= y){
			ret += sum[i];
		}
		else{
			for(int j=0; j<sz[i]; j++){
				if(crs(bkt[i][j], x) <= y){
					ret += bkt[i][j].mode;
				}
			}
			break;
		}
	}
	return ret;
}
 
vector<int> lis;
 
int main(){
	cin >> n >> m >> q;
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		lis.push_back(a[i].first);
	}
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		sort(gph[i].begin(), gph[i].end(), [&](const int &p, const int &q){
			return cmp(p, q, i);
		});
	}
	for(int i=1; i<=n; i++){
		if(!vis[i]){
			v.clear();
			dfs(i);
			if(v.size() == 1) continue;
			int minp = *min_element(v.begin(), v.end(), [&](const int &p, const int &q){
				return pi(a[p].second, a[p].first) < pi(a[q].second, a[q].first);
			});
			int prev = minp;
			int pos = gph[minp][0];
			add_edge(prev, pos);
			pi orig = pi(prev, pos);
			while(1){
				auto t = lower_bound(gph[pos].begin(), gph[pos].end(), prev, [&](const int &p, const int &q){
					return cmp(p, q, pos);
				});
				t++;
				if(t == gph[pos].end()){
					t = gph[pos].begin();
				}
				int nxt = *t;
				if(orig == pi(pos, nxt)){
					break;
				}
				add_edge(pos, nxt);
				prev = pos;
				pos = nxt;
			}
		}
	}
	for(int i=0; i<q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		lis.push_back(x);
		qry.push_back({x, y, i});
	}
	sort(lis.begin(), lis.end());
	lis.resize(unique(lis.begin(), lis.end()) - lis.begin());
	sort(ins.begin(), ins.end(), [&](const sweep &a, const sweep &b){
		return a.pos < b.pos;
	});
	sort(del.begin(), del.end(), [&](const sweep &a, const sweep &b){
		return a.pos < b.pos;
	});
	sort(qry.begin(), qry.end(), [&](const query &a, const query &b){
		return a.x < b.x;
	});
	int p1 = 0, p2 = 0, p3 = 0;
	vector<line> v;
	for(auto &i : lis){
		while(p2 < del.size() && del[p2].pos == i){
			bkt_del(del[p2++].l, i);
		}
		while(p1 < ins.size() && ins[p1].pos == i){
			bkt_ins(ins[p1++].l, i);
		}
		while(p3 < qry.size() && qry[p3].x == i){
			ret[qry[p3].idx] = (bkt_qry(qry[p3].x, qry[p3].y) > 0);
			p3++;
		}
	}
	for(int i=0; i<q; i++) puts(ret[i] ? "Yes" : "No");
}
