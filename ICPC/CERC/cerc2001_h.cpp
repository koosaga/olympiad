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
 
int n;
struct seg{int s, e, x;}a[8005];
vector<int> graph[8005];
 
int cross(vector<int> &v1, vector<int> &v2){
	int ret = 0, p = 0;
	for(auto &i : v1){
		while(p < v2.size() && v2[p] < i) p++;
		if(p < v2.size() && v2[p] == i) ret++;
	}
	return ret;
}
 
bool cross(int s1, int e1, int s2, int e2){
	return max(s1, s2) <= min(e1, e2);
}
 
void add_edge(int s, int e){
	graph[s].push_back(e);
	graph[e].push_back(s);
	//printf("%d %d\n",s, e);
}
void solve(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d %d",&a[i].s, &a[i].e, &a[i].x);
		a[i].s *= 2;
		a[i].e *= 2;
		graph[i].clear();
	}
	sort(a, a+n, [&](const seg &a, const seg &b){
		return a.x < b.x;
	});
	int color[16005] = {};
	memset(color, -1, sizeof(color));
	for(int i=0; i<n; i++){
		for(int j=a[i].s; j<=a[i].e; j++){
			int e = j;
			while(e <= a[i].e && color[j] == color[e]) e++;
			if(color[j] != -1){
				add_edge(i, color[j]);
			}
			j = e-1;
		}
		for(int j=a[i].s; j<=a[i].e; j++){
			color[j] = i;
		}
	}
	lint ret = 0;
	for(int i=0; i<n; i++){
		sort(graph[i].begin(), graph[i].end());
		graph[i].resize(unique(graph[i].begin(), graph[i].end()) - graph[i].begin());
		for(auto &j : graph[i]){
			if(j >= i) break;
			ret += cross(graph[j], graph[i]);
		}
	}
	while(ret % 3 != 0);
	printf("%lld\n",ret / 3);
}
 
int main(){
	int t;
	cin >> t;
	while(t--){
		solve();
	}
}