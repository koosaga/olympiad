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
#include <stdio.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
 
int n, m;
char str[71][71];
int ok[5000], cnt;
 
void input(){
	cin >> n >> m;
	char bt[7] = "aeiouy";
	for(int i=0; i<n; i++){
		char s[105];
		cin >> s;
		for(int j=0; j<m; j++){
			for(int k=0; k<6; k++){
				if(s[j] == bt[k]){
					ok[i*m+j] = 1;
					cnt++;
				}
			}
		}
	}
	for(int i=0; i<n; i++) cin >> str[i];
}
 
vector<int> gph[5000];
 
inline int get(int x, int y){
	return x * m + y;
}
 
void dfs(int x, int y, int od){
	if(od != 1 &&x >= 2 && str[x-2][y] == '|' && str[x-1][y] == '|'){
		dfs(x-2, y, 2);
		gph[get(x, y)].push_back(get(x-2, y));
	}
	if(od != 2 && x+2 < n && str[x+2][y] == '|' && str[x+1][y] == '|'){
		dfs(x+2, y, 1);
		gph[get(x, y)].push_back(get(x+2, y));
	}
	if(od != 3 && y >= 2 && str[x][y-2] == '-' && str[x][y-1] == '-'){
		dfs(x, y-2, 4);
		gph[get(x, y)].push_back(get(x, y-2));
	}
	if(od != 4 && y+2 < m && str[x][y+2] == '-' && str[x][y+1] == '-'){
		dfs(x, y+2, 3);
		gph[get(x, y)].push_back(get(x, y+2));
	}
}
 
int ret, maxdep;
 
int dfs2(int x, int dep){
	for(auto &i : gph[x]){
		dfs2(i, dep + 1);
		ok[x] += ok[i];
		if(ok[i]) ret++, maxdep = max(maxdep, dep + 1);
	}
	return ok[x];
}
 
int main(){
	input();
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == '.'){
				dfs(i, j, 0);
				int p = dfs2(i, 0);
				if(p != cnt){
					puts("NIE");
				}
				else{
					printf("%d\n", ret * 2 - maxdep);
				}
			}
		}
	}
}