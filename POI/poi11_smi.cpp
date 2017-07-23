#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 100005;
 
#include <stdio.h>
#include <stdlib.h>
static char _buffer[1 << 19];
static int _currentChar = 0;
static int _charsNumber = 0;
 
static inline int _read() {
	if (_charsNumber < 0) {
		exit(1);
	}
	if (!_charsNumber || _currentChar == _charsNumber) {
		_charsNumber = (int)fread(_buffer, sizeof(_buffer[0]), sizeof(_buffer), stdin);
		_currentChar = 0;
	}
	if (_charsNumber <= 0) {
		return -1;
	}
	return _buffer[_currentChar++];
}
 
static inline int _readInt() {
	int c, x, s;
	c = _read();
	while (c <= 32) c = _read();
	x = 0;
	s = 1;
	if (c == '-') {
		s = -1;
		c = _read();
	}
	while (c > 32) {
		x *= 10;
		x += c - '0';
		c = _read();
	}
	if (s < 0) x = -x;
	return x;
}
 
int n, m;
vector<pi> gph[MAXN];
int ptr[MAXN], vis[1000005];
 
vector<vector<int>> pth;
vector<int> lis;
 
void dfs(int x){
	while(1){
		lis.push_back(x);
		while(ptr[x] < gph[x].size() && vis[gph[x][ptr[x]].second]){
			ptr[x]++;
		}
		if(ptr[x] == gph[x].size()) break;
		int nxt = gph[x][ptr[x]].first;
		vis[gph[x][ptr[x]].second] = 1;
		x = nxt;
	}
}
 
bool instk[MAXN];
 
int main(){
	n = _readInt();
	m = _readInt();
	for(int i=0; i<m; i++){
		int s, e, x, y;
		s = _readInt();
		e = _readInt();
		x = _readInt();
		y = _readInt();
		if(x == y) continue;
		gph[s].push_back(pi(e, i));
		gph[e].push_back(pi(s, i));
	}
	for(int i=1; i<=n; i++){
		if(gph[i].size() & 1){
			puts("NIE");
			return 0;
		}
	}
	for(int i=1; i<=n; i++){
		if(gph[i].empty()) continue;
		lis.clear();
		dfs(i);
		stack<int> stk;
		for(auto &i : lis){
			if(instk[i]){
				vector<int> v = {i};
				while(!stk.empty() && stk.top() != i){
					v.push_back(stk.top());
					instk[stk.top()] = 0;
					stk.pop();
				}
				v.push_back(i);
				pth.push_back(v);
			}
			else{
				stk.push(i);
				instk[i] = 1;
			}
		}
	}
	printf("%d\n", pth.size());
	for(auto &i : pth){
		printf("%d ", i.size() - 1);
		for(auto &j : i) printf("%d ", j);
		puts("");
	}
}
