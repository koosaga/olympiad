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

int a[2005][2005];
int s[2005][2005];
vector<int> vx, vy;
int n, x[1005], y[1005];
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

int f(int x, int y){
	queue<int> qx, qy;
	qx.push(x);
	qy.push(y);
	a[x][y] = 1;
	int ret = 0;
	while(!qx.empty()){
		x = qx.front();
		y = qy.front();
		qx.pop();
		qy.pop();
		ret += s[x][y];
		for(int i=0; i<4; i++){
			if(x + dx[i] < 0 || x + dx[i] >= 2*n || y + dy[i] < 0 || y + dy[i] >= 2*n){
				continue;
			}
			if(a[x + dx[i]][y + dy[i]]) continue;
			a[x + dx[i]][y + dy[i]] = 1;
			qx.push(x + dx[i]);
			qy.push(y + dy[i]);
		}
	}
	return ret;
}

int main(){
	cin >> n;
	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i];
		vx.push_back(x[i]);
		vy.push_back(y[i]);
	}
	sort(vx.begin(), vx.end());
	vx.resize(unique(vx.begin(), vx.end()) - vx.begin());
	sort(vy.begin(), vy.end());
	vy.resize(unique(vy.begin(), vy.end()) - vy.begin());
	for(int i=0; i<n; i++){
		x[i] = lower_bound(vx.begin(), vx.end(), x[i]) - vx.begin();
		y[i] = lower_bound(vy.begin(), vy.end(), y[i]) - vy.begin();
	}
	for(int i=0; i<n; i++){
		if(x[i] == x[(i+1)%n]){
			int st = min(y[i], y[(i+1)%n]);
			int ed = max(y[i], y[(i+1)%n]);
			for(int j=2*st+1; j<=2*ed+1; j++){
				a[2*x[i]+1][j] = 1;
			}
		}
		else{
			int st = min(x[i], x[(i+1)%n]);
			int ed = max(x[i], x[(i+1)%n]);
			for(int j=2*st+1; j<=2*ed+1; j++){
				a[j][2*y[i]+1] = 1;
			}
		}
	}
	for(int i=0; i<vx.size()-1; i++){
		for(int j=0; j<vy.size()-1; j++){
			s[2*i+2][2*j+2] = (vx[i+1] - vx[i]) * (vy[j+1] - vy[j]);
		}
	}
	s[0][0] = -1e9;
	int ret = 0;
	for(int i=0; i<2*n; i++){
		for(int j=0; j<2*n; j++){
			if(!a[i][j]){
				ret = max(ret, f(i, j));
			}
		}
	}
	cout << ret;
}