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

int n;
vector<pi> gph[50005];
bool inque[50005];
int dist[50005];

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		int s, e, x;
		scanf("%d %d %d",&s,&e,&x);
		gph[s].emplace_back(e+1, -x);
	}
	for(int i=0; i<50001; i++){
		gph[i+1].emplace_back(i, 1);
		gph[i].emplace_back(i+1, 0);
	}
	queue<int> que;
	que.push(0);
	memset(dist, 0x3f, sizeof(dist));
	dist[0] = 0;
	while(!que.empty()){
		int x = que.front();
		que.pop();
		inque[x] = 0;
		for(auto &i : gph[x]){
			if(dist[i.first] > dist[x] + i.second){
				dist[i.first] = dist[x] + i.second;
				if(!inque[i.first]) que.push(i.first);
				inque[i.first] = 1;
			}
		}
	}
	cout << -dist[50001];
}