#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<lint, lint>;
const int MAXN = 250005;
const int dx[8] = {1, 1, 0, -1, -1, -1, 0, 1};
const int dy[8] = {0, 1, 1, 1, 0, -1, -1, -1};

struct rect{
	int sx, ex, sy, ey;
}a[MAXN];

struct trail{
	int d, i, v;
}b[MAXN];

struct point{
	int x, y, idx;
}c[MAXN];

struct bit{
	pi tree[MAXN * 2];
	void clear(){
		fill(tree, tree+2*MAXN, pi(0, 0));
	}
	void upd(int x, pi v){
		x += 4;
		for(int i = x; i < MAXN * 2; i += i & -i){
			tree[i].first += v.first;
			tree[i].second += v.second;
		}
	}
	pi query(int x){
		x += 4;
		pi ret(0, 0);
		for(int i = x; i; i -= i & -i){
			ret.first += tree[i].first;
			ret.second += tree[i].second;
		}
		return ret;
	}
}bit;

int n, m, q;
lint ret[MAXN];

vector<pi> updateBatch[6][MAXN*2];
vector<pi> queryBatch[6][MAXN*2];

void segAdd(int p, int q, int s, int e){
	assert(s >= 0);
	assert(e >= s);
	updateBatch[p][q].emplace_back(s, +1);
	updateBatch[p][q].emplace_back(e + 1, -1);
}

void addLeftUp(int sgn2){
	for(int q = 0; q < 6; q++){
		for(int i = 0; i < 2 * MAXN; i++){
			updateBatch[q][i].clear();
			queryBatch[q][i].clear();
		}
	}
	vector<pi> rec(n);
	for(int i = 0; i < n; i++){
		rec[i] = pi(a[i].sx, a[i].sy);
		segAdd(0, a[i].sx, a[i].sy, a[i].sy);
	}
	for(int i = 0; i < m; i++){
		int idx = b[i].i;
		pi cur(rec[idx].first + dx[b[i].d] * 1, rec[idx].second + dy[b[i].d] * 1);
		pi nxt(rec[idx].first + dx[b[i].d] * b[i].v, rec[idx].second + dy[b[i].d] * b[i].v);
		rec[idx] = nxt;
		if(b[i].d >= 4){
			swap(cur, nxt);
		}
		switch(b[i].d % 4){
			case 0:
			segAdd(1, cur.second, cur.first, nxt.first);
			break;
			case 1:
			segAdd(2, cur.second - cur.first + 250001, cur.first, nxt.first);
			segAdd(3, cur.first - cur.second + 250001, cur.second, nxt.second);
			break;
			case 2:
			segAdd(0, cur.first, cur.second, nxt.second);
			break;
			case 3:
			segAdd(4, cur.first + cur.second, cur.second, nxt.second);
			segAdd(5, cur.first + cur.second, 250001 - cur.first, 250001 - nxt.first); 
			break;
			default:
			assert(0);
			break;
		}
	}
	for(int i = 0; i < q; i++){
		queryBatch[0][c[i].x].emplace_back(c[i].y, i);
		queryBatch[1][c[i].y].emplace_back(c[i].x, i);
		queryBatch[2][c[i].y - c[i].x + 250001].emplace_back(c[i].x, i);
		queryBatch[3][c[i].x - c[i].y + 250000].emplace_back(c[i].y, i);
		queryBatch[4][c[i].x + c[i].y].emplace_back(c[i].y, i);
		queryBatch[5][c[i].x + c[i].y].emplace_back(250000 - c[i].x, i);
	}
	for(int i = 0; i < 6; i++){
		int sgn = (i == 5 ? -1 : 1);
		bit.clear();
		for(int j = 0; j < 2 * MAXN; j++){
			for(auto &[pos, val] : updateBatch[i][j]){
			//	printf("add %d %d\n", pos, val);
				bit.upd(pos, pi(val, -val * (pos - 1)));
			}
			for(auto &[pos, idx] : queryBatch[i][j]){
			//	printf("%d %d\n", pos, idx);
				pi ans = bit.query(pos);
				ret[idx] += sgn2 * sgn * (ans.first * pos + ans.second);
			}
		}
	}
}

vector<long long int> count_enclosing_rectangle(vector< pair<int, int> > R1, vector< pair<int, int> > R2,
            vector<int> V, vector<int> I, vector<int> D,
            vector< pair<int, int> > P){
    n = sz(R1);
    m = sz(V);
    q = sz(P);
	for(int i = 0; i < n; i++){
		tie(a[i].sx, a[i].sy) = R1[i];
		tie(a[i].ex, a[i].ey) = R2[i];
		a[i].ex++;
		a[i].ey++;
	}
	for(int i = 0; i < m; i++){
		b[i].d = V[i];
		b[i].i = I[i];
		b[i].v = D[i];
		b[i].i--;
	}
	for(int i = 0; i < q; i++){
		tie(c[i].x, c[i].y) = P[i];
		c[i].idx = i;
	}
	for(int i = 0; i < 4; i++){
		int sgn = 1;
		if(i & 1) sgn = -sgn;
		if(i & 2) sgn = -sgn;
		for(int j = 0; j < n; j++){
			if(i & 1) swap(a[j].sx, a[j].ex);
			if(i & 2) swap(a[j].sy, a[j].ey);
		}
		addLeftUp(sgn);
		for(int j = 0; j < n; j++){
			if(i & 1) swap(a[j].sx, a[j].ex);
			if(i & 2) swap(a[j].sy, a[j].ey);
		}
	}
	vector<lint> rr(ret, ret + q);
	return rr;
}

int main()
{
	int n, m, q;
	scanf("%d %d %d",&n,&m,&q);
	vector<pair<int, int>> R1(n), R2(n);
	vector<int> V(m), I(m), D(m);
	vector<pair<int, int>> P(q);
	for(int i = 0; i < n; i++){
		scanf("%d %d %d %d",&R1[i].first,&R1[i].second,&R2[i].first,&R2[i].second);
	}
	for(int i = 0; i < m; i++){
		scanf("%d %d %d",&V[i],&I[i],&D[i]);
	}
	for(int i = 0; i < q; i++){
		scanf("%d %d",&P[i].first,&P[i].second);
	}
	auto ans = count_enclosing_rectangle(R1, R2, V, I, D, P);
	if(ans.size() != q){
		for(int i = 0; i < q + 420; i++) puts("-1");
		return 0;
	}
	for(auto &i : ans) printf("%lld\n", i);
}