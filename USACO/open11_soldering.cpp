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
const lint inf = 1e11;

vector<int> gph[50005];
int n;
lint opt[50005], ans;

struct line{
	lint x, y;
	bool operator<(const line &l)const{
		return x == l.x ? y < l.y : x < l.x;
	}
};

struct convex_hull_trick{
	vector<line> joo;
	vector<line> boo;
	size_t size(){ return joo.size() + boo.size(); }
	bool bad(line a, line b, line c){
		return 1ll * (a.y - b.y) * (c.x - b.x) <= 1ll * (b.y - c.y) * (b.x - a.x);
	}
	void renew(){
		vector<line> aux(joo.size() + boo.size());
		sort(boo.begin(), boo.end());
		merge(joo.begin(), joo.end(), boo.begin(), boo.end(), aux.begin());
		joo.clear();
		boo.clear();
		for(auto &i : aux){
			if(!joo.empty() && joo.back().x == i.x) continue; 
			while(joo.size() >= 2 && bad(joo[joo.size()-2], joo.back(), i)) joo.pop_back();
			joo.push_back(i);
		}
	}
	void add(line l){
		if(boo.size() >= 200) renew();
		boo.push_back(l);
	}
	lint query(int x){
		lint ret = inf;
		for(auto &i : boo) ret = min(ret, i.x * x + i.y);
		if(!joo.empty()){
			int s = 0, e = joo.size() - 1;
			while(s != e){
				int m = (s+e)/2;
				if(joo[m].x * x + joo[m].y < joo[m+1].x * x + joo[m+1].y) e = m;
				else s = m+1;
			}
			ret = min(ret, joo[s].x * x + joo[s].y);
		}
		return ret;
	}
	vector<line> retrieve(){
		vector<line> aux;
		for(auto &i : joo) aux.push_back(i);
		for(auto &i : boo) aux.push_back(i);
		return aux;
	}
};

struct dp{
	convex_hull_trick cht;
	lint offsetx, offsety, offsetq;

	dp(){
		offsetx = offsety = offsetq = 0;
	}

	size_t size(){ return cht.size(); }

	void add(line l){
		l.x -= offsetx;
		l.y -= offsety;
		l.y -= offsetq * l.x;
		cht.add(l);
	}

	void shift_line(int x, int y){
		offsetx += x;
		offsety += y;
	}

	void change_query(int x, int y){
		offsety += y + offsetx * x;
		offsetq += x;
	}

	lint query(int x){
		return cht.query(x + offsetq) + offsetx * x + offsety;
	}
	
	vector<line> retrieve(){
		auto ret = cht.retrieve();
		for(auto &i : ret){
			i.y += offsety + offsetq * i.x;
			i.x += offsetx;
		}
		return ret;
	}

};

dp solve(int x){
	if(gph[x].empty()){
		dp ret;
		ret.add({1, 0});
		opt[x] = 1;
		return ret;
	}
	lint sum = 0;
	lint minv = inf;
	dp cur;
	for(auto &i : gph[x]){
		auto tmp = solve(i);
		if(cur.size() < tmp.size()){
			swap(cur, tmp);
		}
		auto tv = tmp.retrieve();
		for(auto &i : tv) minv = min(minv, cur.query(2 * i.x) + i.y + 1);
		for(auto &i : tv) cur.add(i);
		sum += opt[i];
	}
	cur.shift_line(1, sum);
	cur.change_query(2, -1);
	cur.add({1, minv + sum});
	ans = minv + sum - 1;
	opt[x] = cur.query(0);
	cur.shift_line(0, -opt[x]);
	return cur;
}

void dfs(int x){
	for(auto &i : gph[x]){
		gph[i].erase(find(gph[i].begin(), gph[i].end(), x));
		dfs(i);
	}
}

int main(){
	cin >> n;
	if(n == 1){ puts("0"); return 0; }
	if(n == 2){ puts("1"); return 0; }
	for(int i=0; i<n-1; i++){
		int s, e;
		cin >> s >> e;
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	int root = 1;
	for(int i=1; i<=n; i++){
		if(gph[i].size() > 1) root = i;
	}
	dfs(root);
	solve(root);
	cout << ans << endl;
}
