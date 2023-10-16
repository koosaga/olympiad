#include <bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
const int MAXN = 300005;
using lint = long long;
using pi = pair<int, int>;
int dx[256], dy[256];

struct disj{
	int pa[MAXN];
	pi val[MAXN];
	void init(int n){
		iota(pa, pa + n + 1, 0);
	}
	int find(int x){
		return pa[x] = (pa[x] == x ? x : find(pa[x]));
	}
	bool uni(int p, int q){
		p = find(p); q = find(q);
		if(p == q) return 0;
		pa[q] = p; return 1;
	}
	void assign(int p, int x, int y){
		p = find(p);
		val[p] = pi(x, y);
	}
}disj;

struct point{
	int x, y, idx;
	bool operator<(const point &p)const{
		return pi(x, y) < pi(p.x, p.y);
	}
};
set<point> s;

void push(int x, int y, int idx){
	auto l = s.lower_bound((point){x, y, -1});
	if(l != s.end() && pi(l->x, l->y) == pi(x, y)){
		disj.uni(idx, l->idx);
	}
	else{
		s.insert({x, y, idx});
	}
}

int n, q;
char str[MAXN];

int main(){
	dx['L'] = 1;
	dx['R'] = -1;
	dy['D'] = 1;
	dy['U'] = -1;
	scanf("%d", &n);
	scanf("%s", str);
	scanf("%d", &q);
	disj.init(q);
	for(int i=0; i<q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		disj.assign(i, x, y);
		push(x, y, i);
	}
	pi p(0, 0);
	for(int i=0; i<n; i++){
		p.first += dx[str[i]];
		p.second += dy[str[i]];
		auto l = s.lower_bound({p.first, p.second, -1});
		if(l != s.end() && pi(l->x, l->y) == p){
			int idx = l->idx;
			s.erase(l);
			disj.assign(l->idx, p.first + dx[str[i]], p.second + dy[str[i]]);
			push(p.first + dx[str[i]], p.second + dy[str[i]], idx);
		}
	}
	for(int i=0; i<q; i++){
		pi val = disj.val[disj.find(i)];
		val.first -= p.first;
		val.second -= p.second;
		printf("%d %d\n", val.first, val.second);
	}
}
