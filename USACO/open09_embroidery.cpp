#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stack>
#include <queue>
#include <map>
#include <set>
#include <algorithm>
#include <string>
#include <functional>
#include <vector>
#include <numeric>
#include <deque>
#include <utility>
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
typedef pair<double, double> pf;

const double PI = acos(-1);

vector<pf> seg;
vector<pi> seg2;

int n, r;

struct bit{
	int tree[270000], lim;
	void init(int n){
		for(lim = 1; lim <= n; lim <<= 1);
	}
	void add(int x, int v){
		x += lim;
		tree[x] += v;
		while(x > 1){
			x >>= 1;
			tree[x] = tree[2*x] + tree[2*x+1];
		}
	}
	int q(int s, int e){
		s += lim;
		e += lim;
		int ret = 0;
		while(s < e){
			if(s%2 == 1) ret += tree[s++];
			if(e%2 == 0) ret += tree[e--];
			s >>= 1;
			e >>= 1;
		}
		if(s == e) ret += tree[s];
		return ret;
	}
}bit1, bit2;

vector<double> v;

int main(){
	scanf("%d %d",&n,&r);
	for(int i=0; i<n; i++){
		int a, b, c;
		scanf("%d %d %d",&a,&b,&c);
		double dist = abs(c) / hypot(a, b);
		if(dist >= r) continue;
		double ang = acos(dist / r);
		double base = atan2(a, b);
		if(c < 0) base = base + 2 * PI;
		double start = fmod(base - ang + 4 * PI, 2 * PI);
		double end = fmod(base + ang + 4 * PI, 2 * PI);

		if(start > end) swap(start, end);
		seg.push_back(pf(start, end));
		v.push_back(start);
		v.push_back(end);
	}
	sort(v.begin(), v.end());
	v.resize(unique(v.begin(), v.end()) - v.begin());
	seg2.resize(seg.size());
	for(int i=0; i<seg.size(); i++){
		seg2[i].first = (int)(lower_bound(v.begin(), v.end(), seg[i].first) - v.begin());
		seg2[i].second = (int)(lower_bound(v.begin(), v.end(), seg[i].second) - v.begin());
	}
	sort(seg2.begin(), seg2.end());
	bit1.init(v.size());
	bit2.init(v.size());
	for(int i=0; i<seg2.size(); i++){
		bit1.add(seg2[i].first, 1);
		bit2.add(seg2[i].second, 1);
	}
	int ret = 0;
	for(int i=0; i<seg2.size(); i++){
		bit1.add(seg2[i].first, -1);
		bit2.add(seg2[i].second, -1);
		ret += bit1.q(seg2[i].first, seg2[i].second ) - bit2.q(seg2[i].first, seg2[i].second);
	}
	printf("%d",ret);
}