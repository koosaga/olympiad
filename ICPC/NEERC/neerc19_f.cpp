#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <memory.h> 
#include <math.h> 
#include <assert.h> 
#include <stack> 
#include <queue> 
#include <map> 
#include <set> 
#include <string> 
#include <algorithm> 
#include <iostream> 
#include <functional>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;

const int MAXN = 200005;
int deg[MAXN];
int n, m, p, q;
vector<int> v1, v2;

int main(){
	cin >> n >> m >> p >> q;
	v1.resize(p);
	v2.resize(q);
	for(auto &i : v1) scanf("%d",&i);
	for(auto &j : v2) scanf("%d",&j);
	int deg1 = sz(v1) + n;
	int deg2 = sz(v2) + m;
	int left = n + m - 2 - p - q;
	reverse(all(v1));
	reverse(all(v2));
	while(left--){
		if(deg1 < deg2){
			deg1++;
			v1.push_back(1);
		}
		else{
			deg2++;
			v2.push_back(n+1);
		}
	}
	if(deg1 != deg2){
		puts("No");
		return 0;
	}
	fill(deg + 1, deg + n + m + 1, 1);
	for(auto &i : v1) deg[i]++;
	for(auto &i : v2) deg[i]++;
	priority_queue<int, vector<int>, greater<int> > pq;
	for(int i=1; i<=n+m; i++){
		if(deg[i] == 1){
			pq.push(i);
		}
	}
	puts("Yes");
	for(int i=0; i<n+m-2; i++){
		int x = pq.top(); pq.pop();
		int y = -1;
		if(x <= n){
			assert(sz(v2));
			y = v2.back();
			v2.pop_back();
		}
		else{
			assert(sz(v1));
			y = v1.back();
			v1.pop_back();
		}
		printf("%d %d\n", x, y);
		deg[x]--;
		deg[y]--;
		if(deg[y] == 1) pq.push(y);
	}
	for(int i=1; i<=n+m; i++) if(deg[i]) printf("%d ", i);
}
