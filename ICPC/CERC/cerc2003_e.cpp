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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

struct seg{int sx, sy, ex, ey, idx;}a[40005];
vector<int> vx;

int n, water[40005], vs[40005], ve[40005];
vector<int> segs[80005];

double eval(seg a, int p){
	double rat = 1.0 * (p - a.sx) / (a.ex - a.sx);
	return a.sy + (a.ey - a.sy) * rat;
}

bool vis[40005];
int ret[40005];
vector<int> tree[40005];

int f(int x){
	if(vis[x]) return ret[x];
	vis[x] = 1;
	ret[x] = water[x];
	for(auto &i : tree[x]){
		ret[x] += f(i);
	}
	return ret[x];
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> a[i].sx >> a[i].sy >> a[i].ex >> a[i].ey;
		a[i].idx = i;
		vx.push_back(a[i].sx);
		vx.push_back(a[i].ex);
	}
	sort(vx.begin(), vx.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	for(int i=0; i<n; i++){
		vs[i] = lower_bound(vx.begin(), vx.end(), a[i].sx) - vx.begin();
		ve[i] = lower_bound(vx.begin(), vx.end(), a[i].ex) - vx.begin();
		for(int j=vs[i]; j<ve[i]; j++){
			segs[j].push_back(i);
		}
	}
	for(int i=0; i<vx.size()-1; i++){
		int pmax = max_element(segs[i].begin(), segs[i].end(), [&](const int &p, const int &q){
			return eval(a[p], vx[i]) < eval(a[q], vx[i]);
		}) - segs[i].begin();
		if(pmax == segs[i].size()) continue;
		water[segs[i][pmax]] += vx[i+1] - vx[i];
	}
	for(int i=0; i<n; i++){
		segs[ve[i]].push_back(i);
	}
	for(int i=0; i<n; i++){
		int nxtx, nxty;
		if(a[i].sy < a[i].ey){
			nxtx = vs[i];
			nxty = a[i].sy;
		}
		else{
			nxtx = ve[i];
			nxty = a[i].ey;
		}
		double ret = -1;
		int retp = -1;
		for(auto &j : segs[nxtx]){
			double t = eval(a[j], vx[nxtx]);
			if(t + 1e-6 < nxty){
				if(ret < t){
					ret = t;
					retp = j;
				}
			}
		}
		if(retp != -1)tree[retp].push_back(i);
	}
	for(int i=0; i<n; i++){
		printf("%d\n", f(i));
	}
}