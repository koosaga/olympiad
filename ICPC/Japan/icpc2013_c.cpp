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

int sx[55], sy[55], ex[55], ey[55];
vector<int> px, py;
int n;

bool arr[222][222];
int dx[4] = {1,0,-1,0}, dy[4] = {0,1,0,-1};

void dfs(int x, int y){
	if(arr[x][y]) return;
	arr[x][y] = 1;
	for(int i=0; i<4; i++){
		if(x + dx[i] < 0 || x + dx[i] >= 222 || y + dy[i] < 0 || y + dy[i] >= 222) continue;
		dfs(x + dx[i], y + dy[i]);
	}
}

bool solve(){
	memset(arr,0,sizeof(arr));
	scanf("%d",&n);
	if(n == 0) return 0;
	for(int i=0; i<n; i++){
		scanf("%d %d %d %d",&sx[i],&ey[i],&ex[i],&sy[i]);
		px.push_back(sx[i]);
		py.push_back(sy[i]);
		px.push_back(ex[i]);
		py.push_back(ey[i]);
	}
	sort(px.begin(), px.end());
	sort(py.begin(), py.end());
	px.resize(unique(px.begin(), px.end()) - px.begin());
	py.resize(unique(py.begin(), py.end()) - py.begin());
	for(int i=0; i<n; i++){
		sx[i] = (int)(lower_bound(px.begin(), px.end(), sx[i]) - px.begin());
		ex[i] = (int)(lower_bound(px.begin(), px.end(), ex[i]) - px.begin());
		sy[i] = (int)(lower_bound(py.begin(), py.end(), sy[i]) - py.begin());
		ey[i] = (int)(lower_bound(py.begin(), py.end(), ey[i]) - py.begin());
		for(int j=2*sx[i]+1; j<=2*ex[i]+1; j++){
			arr[j][2*sy[i]+1] = arr[j][2*ey[i]+1] = 1;
		}
		for(int j=2*sy[i]+1; j<=2*ey[i]+1; j++){
			arr[2*sx[i]+1][j] = arr[2*ex[i]+1][j] = 1;
		}
	}
	int cnt = 0;
	for(int i=0; i<222; i++){
		for(int j=0; j<222; j++){
			if(!arr[i][j]){
				cnt++;
				dfs(i, j);
			}
		}
	}
	printf("%d\n",cnt);
	px.clear(); py.clear();
	return 1;
}
int main(){
	while(solve());
	
}