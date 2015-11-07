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

int n, m;
pi a[50005], b[50005];
lint dp[50005];

struct cht{
	lint pa[50005], pb[50005];
	int st, ed;
	double cross(int a, int b){
		return 1.0 * (pb[b] - pb[a]) / (pa[a] - pa[b]);
	}
	void add(lint a, lint b){
		pa[ed] = a;
		pb[ed] = b;
		while(ed - 2 >= st && cross(ed-2, ed-1) >= cross(ed-1, ed)){
			pa[ed-1] = pa[ed];
			pb[ed-1] = pb[ed];
			ed--;
		}
		ed++;
	}
	lint query(int x){
		while(st + 1 < ed && cross(st, st+1) <= x){
			st++;
		}
		return 1ll * pa[st] * x + pb[st];
	}
}cht;

bool cmp(const pi &a, const pi &b){
		if(a.first != b.first) return a.first > b.first;
		return a.second > b.second;
	}

int main(){
	scanf("%d",&n);
	for(int i=1; i<=n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a+1, a+n+1,cmp);
	b[m] = pi(1e9, -1e9);
	for(int i=1; i<=n; i++){
		if(a[i].first >= b[m].first || a[i].second <= b[m].second) continue;
		b[++m] = a[i];
	}
	cht.add(b[1].first, 0);
	for(int i=1; i<=m; i++){
		dp[i] = cht.query(b[i].second);
		cht.add(b[i+1].first, dp[i]);
	}
	printf("%lld",dp[m]);
}