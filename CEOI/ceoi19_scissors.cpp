#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
using point = complex<llf>;
using polygon = vector<point>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 2005;
const llf eps = 1e-8L;
 
lint ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return 1ll * dx1 * dy2 - 1ll * dy1 * dx2;
}
lint ccwsgn(pi a, pi b, pi c){
	lint q = ccw(a, b, c);
	if(q != 0) return q > 0 ? 1 : -1;
	return 0;
}
 
bool insec(pi a, pi b, pi c, pi d){
	if(a == c || a == d || b == c || b == d) return 0;
	if(ccwsgn(a, b, c) * ccwsgn(a, b, d) > 0) return 0;
	if(ccwsgn(c, d, a) * ccwsgn(c, d, b) > 0) return 0;
	if(ccwsgn(a, b, c) == 0 && ccwsgn(a, b, d) == 0){
		if(a > b) swap(a, b);
		if(c > d) swap(c, d);
		if(a.second > b.second) swap(a.second, b.second);
		if(c.second > d.second) swap(c.second, d.second);
		return max(a.first, c.first) <= min(b.first, d.first) &&
		max(a.second, c.second) <= min(b.second, d.second);
	}
	return 1;
};
 
vector<vector<int>> triangulation(vector<pi> poly){
	int n = sz(poly);
	vector<int> vis(n);
	auto get_prv = [&](int x){
		int prv = (x + n - 1) % n;
		while(vis[prv]) prv = (prv + n - 1) % n;
		return prv;
	};
	auto get_nxt = [&](int x){
		int nxt = (x + 1) % n;
		while(vis[nxt]) nxt = (nxt + 1) % n;
		return nxt;
	};
	auto ear = [&](int cur){
		int prv = get_prv(cur);
		int nxt = get_nxt(cur);
		int nnxt = get_nxt(nxt);
		int pprv = get_prv(prv);
		if(nnxt == prv) return 1;
		if(ccw(poly[prv], poly[cur], poly[nxt]) <= 0) return 0;
		if(ccw(poly[nxt], poly[prv], poly[nnxt]) >= 0 && 
			ccw(poly[nxt], poly[nnxt], poly[cur]) >= 0) return 0;
		if(ccw(poly[prv], poly[pprv], poly[nxt]) >= 0 && 
			ccw(poly[prv], poly[cur], poly[pprv]) >= 0) return 0;
		for(int i = nxt; nnxt != prv; ){
			if(insec(poly[i], poly[nnxt], poly[prv], poly[nxt])){
				return 0;
			}
			i = nnxt;
			nnxt = get_nxt(nnxt);
		}
		return 1;
	};
	queue<int> que;
	vector<vector<int>> res;
	for(int i=0; i<n; i++){
		if(ear(i)) que.push(i);
	}
	for(int i=0; i<n-2; i++){
		while(vis[que.front()] || !ear(que.front())) que.pop();
		int x = que.front(); que.pop();
		int prv = get_prv(x);
		int nxt = get_nxt(x);
		res.push_back(vector<int>{prv, x, nxt});
		if(sz(res) == n - 2) break;
		vis[x] = 1;
		if(ear(prv)) que.push(prv);
		if(ear(nxt)) que.push(nxt);
	}
	return res;
}
 
struct answer{
	int direction;
	vector<int> src;
	int snk;
	answer(int direction, vector<int> src, int snk) : direction(direction), src(std::move(src)), snk(snk) {}
};
 
pair<vector<answer>, vector<polygon>> solve(){
	int n; cin >> n;
	vector<pi> pp(n);
	polygon P(n);
	for(int i = 0; i < n; i++){
		cin >> pp[i].first >> pp[i].second;
		P[i] = point(pp[i].first, pp[i].second);
	}
	vector<answer> ret;
	vector<polygon> steps = {P};
	auto EB = [&](int d, vector<int> v, int x){
		ret.emplace_back(d, v, x);
	};
	{
		auto trian = triangulation(pp);
		vector<int> src;
		for(auto &v : trian){
			polygon p;
			p.push_back(P[v[0]]);
			p.push_back(P[v[1]]);
			p.push_back(P[v[2]]);
			src.push_back(sz(steps));
			steps.push_back(p);
		}
		EB(1, src, 0);
	}
	auto ccw = [&](point a, point b, point c){
		return (conj(b - a) * (c - a)).imag();
	};
	auto intersection = [&](point z1, point z2, point z3, point z4){
		llf x = ccw(z1, z2, z3);
		llf y = ccw(z1, z2, z4);
		return z4 + y * ((z4 - z3) / (x - y));
	};
	vector<int> rects;
	llf area = 0;
	for(int i = sz(steps) - 1; i >= 1; i--){
		int fuck = 0;
		for(int j = 1; j < 3; j++){
			if(abs(steps[i][(j+1)%3] - steps[i][j]) > abs(steps[i][(fuck+1)%3] - steps[i][fuck])){
				fuck = j;
			}
		}
		point x = steps[i][fuck];
		point y = steps[i][(fuck+1)%3];
		point z = steps[i][(fuck+2)%3];
		point m1 = (x + z) * 0.5L;
		point m2 = (y + z) * 0.5L;
		point m3 = intersection(m1, m2, z, z + (m2 - m1) * point(0, 1));
		point m4 = m1 * 2.0L - m3;
		point m5 = m2 * 2.0L - m3;
		polygon p[6] = {
			{x, y, m2, m1},
			{m2, z, m3},
			{m1, m3, z},
			{m2, y, m5},
			{m1, m4, x},
			{x, y, m5, m4}};
		if(abs(p[5][1] - p[5][0]) > abs(p[5][2] - p[5][1])){
			rotate(p[5].begin(), p[5].begin() + 1, p[5].end());
		}
		int L = sz(steps);
		for(int j = 0; j < 6; j++){
			steps.push_back(p[j]);
		}
		EB(1, {L, L+1, L+2}, i);
		EB(0, {L+1}, L+3);
		EB(0, {L+2}, L+4);
		EB(0, {L, L+3, L+4}, L+5);
		area += abs(p[5][1] - p[5][0]) * abs(p[5][2] - p[5][1]);
		rects.push_back(L + 5);
	}
	llf R = sqrt(area) * 1.169;
	llf W = area / R;

	llf sum = 0;
	vector<int> total;
	for(auto i : rects){
		int idx = i;
		polygon p = steps[idx];
		while(abs(p[1] - p[0]) < R){
			point m1 = (p[0] + p[3]) * 0.5L;
			point m2 = (p[1] + p[2]) * 0.5L;
			point m3 = p[2] * 2.0L - p[3];
			point m4 = m2 * 2.0L - m1;
			polygon p1 = {p[0], p[1], m2, m1};
			polygon p2 = {m1, m2, p[2], p[3]};
			polygon p3 = {m2, m4, m3, p[2]};
			polygon p4 = {m1, m4, m3, p[3]};
			int L = sz(steps);
			steps.push_back(p1);
			steps.push_back(p2);
			steps.push_back(p3);
			steps.push_back(p4);
			EB(1, {L, L+1}, idx);
			EB(0, {L}, L+2);
			EB(0, {L+2, L+1}, L+3);
			p = p4;
			idx = L + 3;
		}
		if(abs(p[1] - p[0]) / R > 1 + 1e-14L){
			llf d = abs(p[1] - p[0]) / R;
			point q[5];
			q[0] = p[0] + (p[1] - p[0]) / d,
			q[1] = p[2] + (p[3] - p[2]) / d,
			q[2] = p[1] + (q[1] - p[1]) * (d - 1);
			q[3] = p[0] + (p[3] - p[0]) * d;
			q[4] = q[0] + (p[3] - p[0]) * d;
			polygon x[6];
			x[0] = {p[0], q[0], q[2], q[1], p[3]};
			x[1] = {q[0], p[1], q[2]};
			x[2] = {p[1], p[2], q[1]};
			x[3] = {p[3], q[1], q[3]}; // 1->3
			x[4] = {q[2], q[4], q[3]}; // 2->4
			x[5] = {p[0], q[0], q[4], q[3]}; // 034->5
			int L = sz(steps);
			for(int i = 0; i < 6; i++) steps.push_back(x[i]);
			EB(1, {L, L+1, L+2}, idx);
			EB(0, {L+1}, L+3);
			EB(0, {L+2}, L+4);
			EB(0, {L, L+3, L+4}, L+5);
			p = x[5];
			idx = L + 5;
		}
		llf cur = abs(p[2] - p[1]);
		polygon q = {point(0, sum), point(R, sum), point(R, sum + cur), point(0, sum + cur)};
		steps.push_back(q);
		EB(0, {idx}, sz(steps) - 1);
		total.push_back(sz(steps) - 1);
		sum += cur;
	}
	polygon ans = {point(0, 0), point(R, 0), point(R, sum), point(0, sum)};
	steps.push_back(ans);
	EB(0, total, sz(steps) - 1);
	return pair(ret, steps);
}
 
void print(polygon p){
	printf("%d", sz(p));
	for(auto i : p){
		printf(" %.20Lf %.20Lf", i.real(), i.imag());
	}
	puts("");
}
 
int main(){
	vector<answer> seq1, seq2;
	vector<polygon> step1, step2;
	tie(seq1, step1) = solve();
	tie(seq2, step2) = solve();
	for(auto &i : seq2){
		i.direction ^= 1;
		i.snk = sz(step1) + sz(step2) - i.snk - 2;
		for(auto &j : i.src){
			j = sz(step1) + sz(step2) - j - 2;
		}
		if(sz(i.src) == 1){
			i.direction ^= 1;
			swap(i.snk, i.src[0]);
		}
	}
	step2.pop_back();
	reverse(all(seq2));
	reverse(all(step2));
	for(auto &i : step2) step1.push_back(i);
	for(auto &i : seq2) seq1.push_back(i);
	vector<polygon> step(sz(step1));
	map<int, int> mp;
	auto mem = [&](int x){
		if(mp.find(x) != mp.end()) return mp[x];
		int w = sz(mp);
		mp[x] = w;
		step[w] = step1[x];
		return w;
	};
	for(auto &i : seq1){
		if(i.direction == 0){
			for(auto &j : i.src) j = mem(j);
			i.snk = mem(i.snk);
		}
		else{
			i.snk = mem(i.snk);
			for(auto &j : i.src) j = mem(j);
		}
	}
	for(auto &i : seq1){
		if(i.direction == 0){
			printf("tape\n");
			printf("%d", sz(i.src));
			for(auto &j : i.src) printf(" %d", j);
			printf("\n");
			if(sz(i.src) == 1){
				print(step[i.snk]);
				print(step[i.snk]);
				continue;
			}
			for(auto &j : i.src){
				print(step[j]);
			}
			print(step[i.snk]);
		}
		else{
			printf("scissors\n");
			printf("%d %d\n", i.snk, sz(i.src));
			for(auto &j : i.src){
				print(step[j]);
			}
		}
	}
}
 
 

