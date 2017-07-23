#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct pnt{
	int x, y, c;
	int r1, r2;
}a[30005], s, e;

lint ccw(pnt a, pnt b, pnt c){
	return 1ll * (b.x - a.x) * (c.y - a.y) - 1ll * (c.x - a.x) * (b.y - a.y);
}

int n, m;
int stx[30005], sty[30005], edx[30005], edy[30005];

void label1(){
	sort(a, a+n, [&](const pnt &p, const pnt &q){
		bool bh1 = ccw(s, e, p) > 0;
		bool bh2 = ccw(s, e, q) > 0;
		if(bh1 != bh2) return bh1 > bh2;
		return ccw(s, p, q) > 0;
	});
	int dv = 0;
	for(int i=0; i<n; i++){
		a[i].r1 = i;
		if(ccw(s, e, a[i]) > 0) dv = i+1;
	}
	int p = 0;
	for(int i=dv; i<n; i++){
		while(p < dv && ccw(s, a[i], a[p]) > 0) p++;
		stx[i] = i;
		edx[i] = p;
	}
	p = dv;
	for(int i=0; i<dv; i++){
		while(p < n && ccw(s, a[i], a[p]) > 0) p++;
		stx[i] = p;
		edx[i] = i;
	}
}

void label2(){
	sort(a, a+n, [&](const pnt &p, const pnt &q){
		bool bh1 = ccw(s, e, p) > 0;
		bool bh2 = ccw(s, e, q) > 0;
		if(bh1 != bh2) return bh1 > bh2;
		return ccw(e, p, q) > 0;
	});
	int dv = 0;
	for(int i=0; i<n; i++){
		a[i].r2 = i;
		if(ccw(s, e, a[i]) > 0) dv = i+1;
	}
	int p = 0;
	for(int i=dv; i<n; i++){
		while(p < dv && ccw(e, a[i], a[p]) > 0) p++;
		sty[i] = p;
		edy[i] = i;
	}
	p = dv;
	for(int i=0; i<dv; i++){
		while(p < n && ccw(e, a[i], a[p]) > 0) p++;
		sty[i] = i;
		edy[i] = p;
	}
}

vector<pi> grp[30005];
map<pi, int> mp;
int refer[100005], ans[100005];

struct sweep1{
	int pos, s, e, dx, idx;
	bool operator<(const sweep1 &c)const{
		return pos < c.pos;
	}
};

struct sweep2{
	int pos, idx;
	bool operator<(const sweep2 &c)const{
		return pos < c.pos;
	}
};

struct sweep3{
	int px, py, idx;
	bool operator<(const sweep3 &c)const{
		return pi(py, px) < pi(c.py, c.px);
	}
};

vector<sweep1> s1[30005];
vector<sweep2> s2[30005];
vector<sweep3> s3[30005];

void add_sweep(int sx, int ex, int sy, int ey, int gnum, int idx){
	if(sx > ex || sy > ey) return;
	s1[gnum].push_back({sx - 1, sy, ey, -1, idx});
	s1[gnum].push_back({ex, sy, ey, 1, idx});
}

void add_sweep2(int y, int gnum, int idx){
	s2[gnum].push_back({y, idx});
}

void add_sweep3(int x, int y, int gnum, int idx){
	s3[gnum].push_back({x, y, idx});
}

struct bit{
	int tree[30005];
	void add(int x, int v){
		x += 2;
		while(x <= n+2){
			tree[x] += v;
			x += x & -x;
		}
	}
	int query(int x){
		x += 2;
		int ret = 0;
		while(x){
			ret += tree[x];
			x -= x & -x;
		}
		return ret;
	}
}bit;

struct sweep4{
	int x, y, dx;
	bool operator<(const sweep4 &c)const{
		return pi(y, x) < pi(c.y, c.x);
	}
};

void proc_sweep(int gnum){
	sort(s1[gnum].begin(), s1[gnum].end());
	sort(s2[gnum].begin(), s2[gnum].end());
	sort(s3[gnum].begin(), s3[gnum].end());
	sort(grp[gnum].begin(), grp[gnum].end());
	int p = 0;
	for(auto &i : s1[gnum]){
		while(p < grp[gnum].size() && grp[gnum][p].first <= i.pos){
			bit.add(grp[gnum][p++].second, 1);
		}
		ans[i.idx] += i.dx * (bit.query(i.e) - bit.query(i.s - 1));
	}
	while(p > 0){
		bit.add(grp[gnum][--p].second, -1);
	}
	vector<pi> vt;
	for(auto &i : grp[gnum]){
		vt.push_back(pi(sty[i.second], 1));
		vt.push_back(pi(edy[i.second], -1));
	}
	sort(vt.begin(), vt.end());
	int sum = 0;
	for(auto &i : s2[gnum]){
		while(p < vt.size() && vt[p].first <= i.pos){
			sum += vt[p++].second;
		}
		ans[i.idx] += sum;
	}
	vector<sweep4> vu;
	for(auto &i : grp[gnum]){
		vu.push_back({edx[i.first], sty[i.second], 1});
		vu.push_back({stx[i.first], sty[i.second], -1});
		vu.push_back({edx[i.first], edy[i.second], -1});
		vu.push_back({stx[i.first], edy[i.second], 1});
	}
	p = 0;
	sort(vu.begin(), vu.end());
	for(auto &i : s3[gnum]){
		while(p < vu.size() && vu[p].y <= i.py){
			bit.add(vu[p].x, vu[p].dx);
			p++;
		}
		ans[i.idx] -= bit.query(i.px);
	}
	while(p > 0){
		p--;
		bit.add(vu[p].x, -vu[p].dx);
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].x,&a[i].y,&a[i].c);
	}
	scanf("%d %d %d %d",&s.x,&s.y,&e.x,&e.y);
	label1();
	label2();
	for(int i=0; i<n; i++){
		grp[a[i].c].push_back(pi(a[i].r1, a[i].r2));
	}
	int q;
	scanf("%d",&q);
	for(int i=1; i<=q; i++){
		int x, y;
		scanf("%d %d",&x,&y);
		if(mp.find(pi(x, y)) != mp.end()){
			refer[i] = mp[pi(x, y)];
			continue;
		}
		if(grp[x].size() < grp[y].size()){
			for(auto &j : grp[x]){
				add_sweep(0, edx[j.first] - 1, sty[j.second], edy[j.second] - 1, y, i);
				add_sweep(stx[j.first], n-1, sty[j.second], edy[j.second] - 1, y, i);
			}
		}
		else{
			for(auto &j : grp[y]){
				add_sweep2(j.second, x, i);
				add_sweep3(j.first, j.second, x, i);
			}
		}
		mp[pi(x, y)] = i;
	}
	for(int i=1; i<=m; i++) proc_sweep(i);
	for(int i=1; i<=q; i++){
		if(refer[i]) printf("%d\n", ans[refer[i]]);
		else printf("%d\n", ans[i]);
	}
}

