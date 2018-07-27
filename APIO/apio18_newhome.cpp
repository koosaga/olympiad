#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 300005;
 
struct query{
	int pos, t, idx;
	bool operator<(const query &q)const{
		return t < q.t;
	};
}qry[MAXN];
 
struct query2{
	int t, mode, val;
	bool operator<(const query2 &q)const{
		return pi(t, mode) < pi(q.t, q.mode);
	};
};
 
struct rect{ int st, et, y, mode, rpos; };
// mode 1 : [0, y]
// mode -1 : [y, inf]
struct intv{ int s, e, x; };
vector<intv> house[MAXN];
vector<rect> rec;
int n, k, q, ans[MAXN];
const int inf = 500000005;
 
struct rect2{
	int sx, ex, ins;
	bool operator<(const rect2 &r)const{
		return sx < r.sx;
	}
};
 
void process(int h){
	vector<query2> v;
	for(auto &i : house[h]){
		i.s = lower_bound(qry, qry + q, (query){-1, i.s, -1}) - qry;
		i.e = upper_bound(qry, qry + q, (query){-1, i.e, -1}) - qry;
		if(i.s == i.e) continue;
		v.push_back({i.s, 1, i.x});
		v.push_back({i.e, -1, i.x});
	}
	sort(v.begin(), v.end());
	map<int, int> cnt;
	set<rect2> r;
	r.insert({-1, inf, 0});
	auto insert_rect = [&](int st, int et, int sy, int ey){
		if(st == et) return;
		et--;
		if(sy == -1){
			rec.push_back({st, et, -1, -1, ey});
			return;
		}
		if(ey == inf){
			rec.push_back({st, et, inf, 1, sy});
			return;
		}
		int my = (sy + ey) / 2;
		rec.push_back({st, et, my, 1, sy});
		rec.push_back({st, et, my+1, -1, ey});
	};
	for(int i=0; i<v.size(); i++){
		auto insert_intv = [&](int pos){
			auto l = --r.upper_bound({pos, -1, -1});
			insert_rect(l->ins, v[i].t, l->sx, l->ex);
			rect2 ins1 = {l->sx, pos, v[i].t};
			rect2 ins2 = {pos, l->ex, v[i].t};
			r.erase(l);
			r.insert(ins1);
			r.insert(ins2);
		};
		auto remove_intv = [&](int pos){
			auto nxt = r.lower_bound({pos, -1, -1});
			auto prv = prev(nxt);
			insert_rect(prv->ins, v[i].t, prv->sx, prv->ex);
			insert_rect(nxt->ins, v[i].t, nxt->sx, nxt->ex);
			rect2 ins = {prv->sx, nxt->ex, v[i].t};
			r.erase(prv);
			r.erase(nxt);
			r.insert(ins);
		};
		for(int j=i; j<i+1; j++){
			if(cnt[v[j].val] == 0) insert_intv(v[j].val);
			cnt[v[j].val] += v[j].mode;
			if(cnt[v[j].val] == 0) remove_intv(v[j].val);
		}
	}
}
 
struct query3{
	int pos, l, r, v;
	bool operator<(const query3 &q)const{
		return pos < q.pos;
	}
};
 
vector<query3> mode1,mode2;
// mode1 : disappear after y + 1
// mode2 : appear after y
 
struct seg{
	int seg[1050000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
		fill(seg, seg + 1050000, 1e9);
	}
	void add(int l, int r, int val){
		l += lim;
		r += lim;
		while(l < r){
			if(l%2 == 1) seg[l] = min(seg[l], val), l++;
			if(r%2 == 0) seg[r] = min(seg[r], val), r--;
			l >>= 1;
			r >>= 1;
		}
		if(l == r) seg[l] = min(seg[l], val);
	}
	int query(int pos){
		pos += lim;
		int ans = 1e9;
		while(pos){
			ans = min(ans, seg[pos]);
			pos >>= 1;
		}
		return ans;
	}
}seg;
 
int main(){
	scanf("%d %d %d",&n,&k,&q);
	for(int i=0; i<n; i++){
		int x, t, s, e;
		x = rand()%100000000 + 1;
		t = rand()%k +1;
		s = 1;
		e = 100000000;
		scanf("%d %d %d %d",&x,&t,&s,&e);
		house[t].push_back({s, e, x});
	}
	for(int i=1; i<=k; i++){
		house[i].push_back({1, 100000000, 500000000});
	}
	for(int i=0; i<q; i++){
		qry[i].pos = rand()%100000000 + 1;
		qry[i].t = 1;
		scanf("%d %d",&qry[i].pos,&qry[i].t);
		qry[i].idx = i;
	}
	sort(qry, qry + q);
	for(int i=1; i<=k; i++) process(i);
	for(auto &j : rec){
		if(j.mode == 1){
			mode1.push_back({j.y, j.st, j.et, j.rpos});
		}
		else{
			mode2.push_back({j.y, j.st, j.et, j.rpos});
		}
	}
	for(int i=0; i<q; i++) qry[i].t = i;
	sort(qry, qry + q, [&](const query &a, const query &b){
		return a.pos < b.pos;
	});
	sort(mode1.begin(), mode1.end());
	sort(mode2.begin(), mode2.end());
	int ptr = 0;
	seg.init(q + 1);
	for(int i=0; i<q; i++){
		while(ptr < mode2.size() && mode2[ptr].pos <= qry[i].pos){
			seg.add(mode2[ptr].l, mode2[ptr].r, -mode2[ptr].v);
			ptr++;
		}
		int query2 = -seg.query(qry[i].t) - qry[i].pos;
		ans[qry[i].idx] = max(ans[qry[i].idx], query2);
	}
	seg.init(q + 1);
	ptr = mode1.size();
	for(int i=q-1; i>=0; i--){
		while(ptr > 0 && mode1[ptr-1].pos >= qry[i].pos){
			ptr--;
			seg.add(mode1[ptr].l, mode1[ptr].r, mode1[ptr].v);
		}
		int query1 = qry[i].pos - seg.query(qry[i].t);
		ans[qry[i].idx] = max(ans[qry[i].idx], query1);
	}
	for(int i=0; i<q; i++){
		if(ans[i] > 2e8) ans[i] = -1;
		printf("%d\n", ans[i]);
	}
}