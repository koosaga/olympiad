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

int n, m;
int col[200005];
vector<int> gph[200005];

void dfs(int x, int c){
	if(col[x]) return;
	col[x] = c;
	for(int i=0; i<gph[x].size(); i++){
		dfs(gph[x][i], 3-c);
	}
}

int main(){
	cin >> n >> m;
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		if(gph[i].size() == 0){
			puts("NIE");
			return 0;
		}
		if(!col[i]){
			dfs(i, 1);
		}
	}
	puts("TAK");
	for(int i=1; i<=n; i++){
		puts(col[i] == 1 ? "K" : "S");
	}
}
