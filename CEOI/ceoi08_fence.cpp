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

bool ccw(pi a, pi b, pi c){
	int dx1 = b.first - a.first;
	int dy1 = b.second - a.second;
	int dx2 = c.first - a.first;
	int dy2 = c.second - a.second;
	return dx1 * dy2 > dy1 * dx2;
}

int n, m;
pi a[105], b[105];
vector<pi> hull;

int adj[105][105];
int vis[105];

bool cmp(pi p, pi q){
	return ccw(a[0], p, q);
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	for(int i=0; i<m; i++){
		scanf("%d %d",&b[i].first,&b[i].second);
	}
	swap(a[0], *min_element(a, a+n));
	sort(a+1, a+n, cmp);
	for(int i=0; i<n; i++){
		while(hull.size() >= 2 && !ccw(hull[hull.size()-2], hull.back(), a[i])){
			hull.pop_back();
		}
		hull.push_back(a[i]);
	}
	for(int i=0; i<hull.size(); i++){
		for(int j=0; j<m; j++){
			if(!ccw(hull[i], hull[(i+1)%hull.size()], b[j])){
				vis[j] = 1;
			}
		}
	}
	memset(adj,0x3f,sizeof(adj));
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			if(i == j) continue;
			adj[i][j] = 1;
			for(int k=0; k<m; k++){
				if(vis[k]) continue;
				if(!ccw(a[i], a[j], b[k])){
					adj[i][j] = 1e9;
					break;
				}
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<n; j++){
			for(int k=0; k<n; k++){
				adj[j][k] = min(adj[j][k], adj[j][i] + adj[i][k]);
			}
		}
	}
	int cov = 1e9;
	for(int i=0; i<n; i++){
		cov = min(cov, adj[i][i]);
	}
	if(count(vis, vis + m, 1) == m){
		cov = 0;
	}
	printf("%d",cov * 20 + 111 * count(vis, vis + m, 1));
}