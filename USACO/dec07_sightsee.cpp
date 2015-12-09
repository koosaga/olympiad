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

int n, m, a[1005];
int s[5005], e[5005], c[5005];

bool trial(double x){
	double dist[1005];
	fill(dist + 1, dist + n + 1, 1e9);
	dist[1] = 0;
	for(int i=0; i<=n; i++){
		bool upd = 0;
		for(int j=0; j<m; j++){
			double tmp = dist[s[j]] + c[j] * x - a[e[j]];
			if(dist[e[j]] > tmp){
				dist[e[j]] = tmp;
				upd = 1;
			}
		}
		if(!upd) break;
		if(i == n) return 1;
	}
	return 0;
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
	}
	for(int i=0; i<m; i++){
		scanf("%d %d %d",&s[i],&e[i],&c[i]);
	}
	double s = 0, e = 20; // nasty hack
	for(int i=0; i<15; i++){
		double m = (s+e)/2;
		if(trial(m)) s = m; // odd cycle
		else e = m;
	}
	printf("%.2f",s);
}