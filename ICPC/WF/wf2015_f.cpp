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
char str[55][55], inp[10005];
bool vis[10005][51][51];
int d1[55][55], d2[55][55], d3[55][55], d4[55][55];

queue<int> qx, qy, qd, ql;

int main(){
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%s",str[i] + 1);
	}
	scanf("%s",inp);
	inp[strlen(inp)] = '*';
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			if(str[i][j] != str[i][j-1]){
				d1[i][j] = j-1;
			}
			else d1[i][j] = d1[i][j-1];
		}
		for(int j=m; j; j--){
			if(str[i][j] != str[i][j+1]){
				d2[i][j] = j+1;
			}
			else d2[i][j] = d2[i][j+1];
		}
	}
	for(int i=1; i<=m; i++){
		for(int j=1; j<=n; j++){
			if(str[j][i] != str[j-1][i]){
				d3[j][i] = j-1;
			}
			else d3[j][i] = d3[j-1][i];
		}
		for(int j=n; j; j--){
			if(str[j][i] != str[j+1][i]){
				d4[j][i] = j+1;
			}
			else d4[j][i] = d4[j+1][i];
		}
	}
	qx.push(1);
	qy.push(1);
	qd.push(0);
	ql.push(0);
	vis[0][1][1] = 1;
	while(!qx.empty()){
		int xf = qx.front();
		int yf = qy.front();
		int df = qd.front();
		int lf = ql.front();
		qx.pop();
		qy.pop();
		qd.pop();
		ql.pop();
		if(!inp[df]){
			printf("%d",lf);
			return 0;
		}
		if(!vis[df + 1][xf][yf] && str[xf][yf] == inp[df]){
			qx.push(xf);
			qy.push(yf);
			qd.push(df + 1);
			ql.push(lf + 1);
			vis[df+1][xf][yf] = 1;
		}
		if(d1[xf][yf] && !vis[df][xf][d1[xf][yf]]){
			qx.push(xf);
			qy.push(d1[xf][yf]);
			qd.push(df);
			ql.push(lf + 1);
			vis[df][xf][d1[xf][yf]] = 1;
		}
		if(d2[xf][yf] <= m && !vis[df][xf][d2[xf][yf]]){
			qx.push(xf);
			qy.push(d2[xf][yf]);
			qd.push(df);
			ql.push(lf + 1);
			vis[df][xf][d2[xf][yf]] = 1;
		}
		if(d3[xf][yf] && !vis[df][d3[xf][yf]][yf]){
			qx.push(d3[xf][yf]);
			qy.push(yf);
			qd.push(df);
			ql.push(lf + 1);
			vis[df][d3[xf][yf]][yf] = 1;
		}
		if(d4[xf][yf] <= n && !vis[df][d4[xf][yf]][yf]){
			qx.push(d4[xf][yf]);
			qy.push(yf);
			qd.push(df);
			ql.push(lf + 1);
			vis[df][d4[xf][yf]][yf] = 1;
		}
	}
}