#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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
char str[105][105];
int idx[105][105], p;
 
vector<int> gph[40005]; // up = 0, dn = 1, le = 2, ri = 3;
vector<int> rev[40005];
bool vis[40005];
vector<int> dfn;
int comp[40005], cmp;
 
bool ok(int p){
	return comp[p^1] < comp[p];
}
 
void dfs(int x){
	if(vis[x]) return;
	vis[x] = 1;
	for(auto &i : gph[x]){
		dfs(i);
	}
	dfn.push_back(x);
}
 
void rdfs(int x, int p){
	if(comp[x]) return;
	comp[x] = p;
	for(auto &i : rev[x]){
		rdfs(i, p);
	}
}
 
void solve_2sat(){
	for(int i=0; i<4*p; i++){
		if(!vis[i]){
			dfs(i);
		}
	}
	reverse(dfn.begin(), dfn.end());
	for(auto &i : dfn){
		if(!comp[i]){
			rdfs(i, ++cmp);
		}
	}
	for(int i=0; i<4*p; i++){
		if(comp[i] == comp[i^1]){
			assert(0);
		}
	}
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] != 'T'){
				putchar(str[i][j]);
			}
			else{
				int p = idx[i][j];
				if(ok(4 * p + 2) && ok(4 * p + 1)){
					putchar('1');
				}
				else if(ok(4 * p + 3) && ok(4 * p + 1)){
					putchar('2');
				}
				else if(ok(4 * p + 3) && ok(4 * p)){
					putchar('3');
				}
				else{
					putchar('4');
				}
			}
		}
		puts("");
	}
}
 
void add_edge(int x, int y){
	gph[x].push_back(y);
	rev[y].push_back(x);
}
 
void always_true(int x){
	add_edge(x^1, x);
}
 
void proc_tower(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'T'){
				for(int k=j+1; k<m; k++){
					if(str[i][k] == 'T'){
						always_true(idx[i][j] * 4 + 2);
						break;
					}
					if(str[i][k] == '#') break;
				}
				for(int k=j-1; k>=0; k--){
					if(str[i][k] == 'T'){
						always_true(idx[i][j] * 4 + 3);
						break;
					}
					if(str[i][k] == '#') break;
				}
				for(int k=i+1; k<n; k++){
					if(str[k][j] == 'T'){
						always_true(idx[i][j] * 4 + 0);
						break;
					}
					if(str[k][j] == '#') break;
				}
				for(int k=i-1; k>=0; k--){
					if(str[k][j] == 'T'){
						always_true(idx[i][j] * 4 + 1);
						break;
					}
					if(str[k][j] == '#') break;
				}
			}
		}
	}
}
 
void proc_evil(){
	for(int i=0; i<n; i++){
		for(int j=0; j<m; j++){
			if(str[i][j] == 'n'){
				vector<int> px, py;
				for(int k=j+1; k<m; k++){
					if(str[i][k] == 'T'){
						py.push_back(4 * idx[i][k] + 2);
						break;
					}
					if(str[i][k] == '#') break;
				}
				for(int k=j-1; k>=0; k--){
					if(str[i][k] == 'T'){
						py.push_back(4 * idx[i][k] + 3);
						break;
					}
					if(str[i][k] == '#') break;
				}
				for(int k=i+1; k<n; k++){
					if(str[k][j] == 'T'){
						px.push_back(4 * idx[k][j] + 0);
						break;
					}
					if(str[k][j] == '#') break;
				}
				for(int k=i-1; k>=0; k--){
					if(str[k][j] == 'T'){
						px.push_back(4 * idx[k][j] + 1);
						break;
					}
					if(str[k][j] == '#') break;
				}
				if(px.size() == 2) px.clear();
				if(py.size() == 2) py.clear();
				if(px.size() == 0 && py.size() == 0){
					assert(0);
				}
				if(px.size() == 1 && py.size() == 0){
					always_true(px[0]);
				}
				if(px.size() == 0 && py.size() == 1){
					always_true(py[0]);
				}
				if(px.size() == 1 && py.size() == 1){
					add_edge(px[0] ^ 1, py[0]);
					add_edge(py[0] ^ 1, px[0]);
				}
			}
		}
	}
}
 
int main(){
	cin >> n >> m;
	for(int i=0; i<n; i++){
		cin >> str[i];
		for(int j=0; j<m; j++){
			if(str[i][j] == 'T') idx[i][j] = (p++);
		}
	}
	proc_tower();
	proc_evil();
	solve_2sat();
}