#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int mod = 1e9 + 7;

struct pnt{
	int x, y, idx;
};

struct val{
	deque<pi> xr, yr;
	vector<pnt> v;
	int offx, offy;
	val(int s){
		offx = offy = 0;
		v.push_back({0, 0, s});
		xr.push_back(pi(0, 0));
		yr.push_back(pi(0, 0));
	}
	int size(){ return v.size(); }
	void apply_off(){
		if(offx == 0 && offy == 0) return;
		for(auto &j : v) j.x += offx, j.y += offy;
		for(auto &i : xr) i.first += offy, i.second += offy;
		for(auto &i : yr) i.first += offx, i.second += offx;
		offx = offy = 0;
	}
};

int mat[300005];
char str[300005];
int n;

int rmerge(val &a, val &b){
	int dx = -1e9;
	for(int i=0; i<a.xr.size() && i<b.xr.size(); i++){
		dx = max(dx, a.xr[i].second + a.offy - b.offy + 1 - b.xr[i].first);
	}
	if(a.size() > b.size()){
		b.apply_off();
		for(auto &j : b.v){
			j.y += dx;
			assert(j.x >= 0 && j.y >= 0);
			while(a.xr.size() <= j.x) a.xr.push_back(pi(1e9, -1e9));
			while(a.yr.size() <= j.y) a.yr.push_back(pi(1e9, -1e9));
			a.xr[j.x].first = min(a.xr[j.x].first, j.y - a.offy);
			a.xr[j.x].second = max(a.xr[j.x].second, j.y - a.offy);
			a.yr[j.y].first = min(a.yr[j.y].first, j.x - a.offx);
			a.yr[j.y].second = max(a.yr[j.y].second, j.x - a.offx);
			a.v.push_back({j.x - a.offx, j.y - a.offy, j.idx});
		}
		return -1;
	}
	else{
		a.apply_off();
		b.offy += dx;
		for(int j=0; j<dx; j++){
			b.yr.push_front(pi(1e9, -1e9));
		}
		for(auto &j : a.v){
			assert(j.x >= 0 && j.y >= 0);
			while(b.xr.size() <= j.x) b.xr.push_back(pi(1e9, -1e9));
			while(b.yr.size() <= j.y) b.yr.push_back(pi(1e9, -1e9));
			b.xr[j.x].first = min(b.xr[j.x].first, j.y - b.offy);
			b.xr[j.x].second = max(b.xr[j.x].second, j.y - b.offy);
			b.yr[j.y].first = min(b.yr[j.y].first, j.x - b.offx);
			b.yr[j.y].second = max(b.yr[j.y].second, j.x - b.offx);
			b.v.push_back({j.x - b.offx, j.y - b.offy, j.idx});
		}
		return 1;
	}
}

int dmerge(val &a, val &b){
	int dx = -1e9;
	for(int i=0; i<a.yr.size() && i<b.yr.size(); i++){
		dx = max(dx, a.yr[i].second + a.offx - b.offx + 1 - b.yr[i].first);
	}
	if(a.size() > b.size()){
		b.apply_off();
		for(auto &j : b.v){
			j.x += dx;
			while(a.xr.size() <= j.x) a.xr.push_back(pi(1e9, -1e9));
			while(a.yr.size() <= j.y) a.yr.push_back(pi(1e9, -1e9));
			a.xr[j.x].first = min(a.xr[j.x].first, j.y - a.offy);
			a.xr[j.x].second = max(a.xr[j.x].second, j.y - a.offy);
			a.yr[j.y].first = min(a.yr[j.y].first, j.x - a.offx);
			a.yr[j.y].second = max(a.yr[j.y].second, j.x - a.offx);
			a.v.push_back({j.x - a.offx, j.y - a.offy, j.idx});
		}
		return -1;
	}
	else{
		a.apply_off();
		b.offx += dx;
		for(int j=0; j<dx; j++){
			b.xr.push_front(pi(1e9, -1e9));
		}
		for(auto &j : a.v){
			while(b.xr.size() <= j.x) b.xr.push_back(pi(1e9, -1e9));
			while(b.yr.size() <= j.y) b.yr.push_back(pi(1e9, -1e9));
			b.xr[j.x].first = min(b.xr[j.x].first, j.y - b.offy);
			b.xr[j.x].second = max(b.xr[j.x].second, j.y - b.offy);
			b.yr[j.y].first = min(b.yr[j.y].first, j.x - b.offx);
			b.yr[j.y].second = max(b.yr[j.y].second, j.x - b.offx);
			b.v.push_back({j.x - b.offx, j.y - b.offy, j.idx});
		}
		return 1;
	}
}

val* solve(int s, int e){
	if(s == e){
		return new val(s);
	}
	if(str[e] == ')'){
		if(mat[e] == s) return solve(s+1, e-1);
		auto l = solve(s, mat[e] - 2);
		auto r = solve(mat[e] + 1, e - 1);
		if(str[mat[e] - 1] == '>'){
			if(rmerge(*l, *r) == -1) return l;
			return r;
		}
		else{
			if(dmerge(*l, *r) == -1) return l;
			return r;
		}
	}
	else{
		val* l = solve(s, e - 2);
		val* r = solve(e, e);
		if(str[e - 1] == '>'){
			if(rmerge(*l, *r) == -1) return l;
			return r;
		}
		else{
			if(dmerge(*l, *r) == -1) return l;
			return r;
		}
	}
}

int main(){
	cin >> str;
	n = strlen(str);
	stack<int> stk;
	for(int i=0; i<n; i++){
		if(str[i] == '(') stk.push(i);
		else if(str[i] == ')'){
			mat[i] = stk.top();
			stk.pop();
		}
	}
	val k = *solve(0, n-1);
	sort(k.v.begin(), k.v.end(), [&](const pnt &a, const pnt &b){
		return a.idx < b.idx;
	});
	for(auto &i : k.v) printf("%d %d\n", i.y + k.offy, i.x + k.offx);
}
