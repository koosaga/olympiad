#include <bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
const int mod = 1e9 + 7;
using lint = long long;
using pi = pair<lint, lint>;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
const string assoc[4] = {"SOUTH", "EAST", "NORTH", "WEST"};
bool vis[222][222];

void dfs(int x, int y){
	if(vis[x][y]) return;
	vis[x][y] = 1;
	for(int i=0; i<4; i++){
		cout << assoc[i] << endl;
		string xx; cin >> xx;
		if(xx == "EMPTY"){
			dfs(x + dx[i], y + dy[i]);
			cout << assoc[i ^ 2] << endl;
			cin >> xx;
		}
	}
}

int main(){
	dfs(100, 100);
	cout << "DONE" << endl;
}

