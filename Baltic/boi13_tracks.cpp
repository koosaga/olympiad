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
int dx[4] = {1, 0, -1, 0}, dy[4] = {0, 1, 0, -1};

queue<pi> q1, q2;

int n, m, ret;
char str[4005][4005];
bool vis[4005][4005];

void bfs(queue<pi> &q1, queue<pi> &q2, int d){
	if(q1.empty()) return;
	ret = d;
	while(!q1.empty()){
		pi x = q1.front();
		q1.pop();
		for(int i=0; i<4; i++){
			if(x.first + dx[i] < 0 || x.second + dy[i] < 0 || x.first + dx[i] >= n || x.second + dy[i] >= m){
				continue;
			}
			if(vis[x.first+dx[i]][x.second+dy[i]] || str[x.first+dx[i]][x.second+dy[i]] == '.') continue;
			vis[x.first+dx[i]][x.second+dy[i]] = 1;
			if(str[x.first + dx[i]][x.second + dy[i]] != str[x.first][x.second]) q2.push(pi(x.first + dx[i], x.second + dy[i]));
			else q1.push(pi(x.first + dx[i], x.second + dy[i]));
		}
	}
	bfs(q2, q1, d+1);
}

int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++) cin >> str[i];
	q1.push(pi(0, 0));
	vis[0][0] = 1;
	bfs(q1, q2, 1);
	cout << ret;
}