#include<bits/stdc++.h>
using namespace std;
const int MAXN = 100005;
using lint = long long;
using real_t = long double;
using pi = pair<int, int>;

int n, m;
vector<int> gph[MAXN];
bool win[2][MAXN]; // whether second can win, assuming the holder is i
bool draw[2][MAXN]; // whether first can draw, assuming the holder is i
int deg[MAXN];

void calc_win(){
	memset(deg, 0, sizeof(deg));
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]) deg[j]++;
	}
	queue<pi> que;
	for(int i=1; i<=n; i++){
		if(deg[i] == 0){
			que.emplace(0, i);
			win[0][i] = 1;
		}
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(x.first == 0){
			for(auto &j : gph[x.second]){
				if(!win[1][j]){
					win[1][j] = 1;
					que.emplace(1, j);
				}
			}
		}
		else{
			for(auto &j : gph[x.second]){
				deg[j]--;
				if(deg[j] == 0 && !win[0][j]){
					win[0][j] = 1;
					que.emplace(0, j);
				}
			}
		}
	}
}

void calc_draw(){
	memset(deg, 0, sizeof(deg));
	for(int i=1; i<=n; i++){
		for(auto &j : gph[i]) deg[j]++;
		draw[0][i] = draw[1][i] = 1;
	}
	queue<pi> que;
	for(int i=1; i<=n; i++){
		if(deg[i] == 0){
			que.emplace(0, i);
			que.emplace(1, i);
			draw[0][i] = draw[1][i] = 0;
		}
	}
	while(!que.empty()){
		auto x = que.front();
		que.pop();
		if(x.first == 0){
			for(auto &j : gph[x.second]){
				if(draw[1][j]){
					draw[1][j] = 0;
					que.emplace(1, j);
				}
			}
		}
		else{
			for(auto &j : gph[x.second]){
				deg[j]--;
				if(deg[j] == 0 && draw[0][j]){
					draw[0][j] = 0;
					que.emplace(0, j);
				}
			}
		}
	}
}

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e; scanf("%d %d",&s,&e);
		gph[e].push_back(s);
	}
	calc_win();
	calc_draw();
	for(int i=1; i<=n; i++){
		if(draw[0][i]) putchar('D');
		else if(win[0][i]) putchar('L');
		else putchar('W');
	}
	puts("");
	for(int i=1; i<=n; i++){
		if(win[1][i]) putchar('W');
		else if(draw[1][i]) putchar('D'); 
		else putchar('L');
	}
}
