#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1005;

int n, m;
char a[MAXN][MAXN];
char b[MAXN][MAXN];
bool vis[MAXN][MAXN];

bool cx[MAXN], cy[MAXN];
set<int> Row[MAXN];
set<int> Col[MAXN];

void dfs(int x, int y);

auto go = [&](int x, int y){
	int cnt = 0;
	if(Col[y].empty() || (Col[y].size() == 1 && *Col[y].begin() == x)) cnt++;
	if(Row[x].empty() || (Row[x].size() == 1 && *Row[x].begin() == y)) cnt++;
	return cnt == 2;
};
void Eliminate(int x, int y){
	Row[x].erase(y);
	Col[y].erase(x);
	if(Row[x].size() <= 1){
		for(int i=0; i<m; i++){
			if(!vis[x][i] && go(x, i)) dfs(x, i);
		}
	}
	if(Col[y].size() <= 1){
		for(int i=0; i<n; i++){
			if(!vis[i][y] && go(i, y)) dfs(i, y);
		}
	}
}

void dfs(int x, int y){
	vis[x][y] = 1;
	if(!cx[x]){
		cx[x] = 1;
		while(Row[x].size()){
			Eliminate(x, *Row[x].begin());
		}
	}
	if(!cy[y]){
		cy[y] = 1;
		while(Col[y].size()){
			Eliminate(*Col[y].begin(), y);
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<n; i++){
		scanf("%s",a[i]);
		for(int j=0; j<m; j++){
			if(a[i][j] == 'X') a[i][j] = '0';
			else a[i][j] = '1';
		}
	}
	bool triv = 1;
	for(int i=0; i<n; i++){
		scanf("%s",b[i]);
		for(int j=0; j<m; j++){
			if(b[i][j] == 'X') b[i][j] = '0';
			else b[i][j] = '1';
			if(a[i][j] != b[i][j]) triv = 0;
		}
	}
	if(triv){
		puts("1");
		return 0;
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(b[i][j] == '0'){
				Row[i].insert(j);
				Col[j].insert(i);
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(!vis[i][j] && go(i, j)){
				dfs(i, j);
			}
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(!cx[i] && !cy[j] && a[i][j] != b[i][j]){
				puts("0");
				return 0;
			}
		}
	}
	bool good = 0;
	bool good2 = 0;
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(cx[i] && cy[j] && a[i][j] == '1'){
				good = 1;
			}
			if(cx[i] && cy[j] && b[i][j] == '0'){
				good2 = 1;
			}
		}
	}
	if(!good || !good2) puts("0");
	else puts("1");
}
