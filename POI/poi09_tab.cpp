#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
typedef long long lint;
const int offset = 1000000;
const int MAXN = 2000005;

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

int vx[2][MAXN], vy[2][MAXN], vis[MAXN];
int p1[1005], p2[1005];

int main(){
	int t = _readInt();
	while(t--){
		int n = _readInt();
		int m = _readInt();
		memset(p1, -1, sizeof(p1));
		memset(p2, -1, sizeof(p2));
		memset(vis, 0, sizeof(vis));
		for(int i=0; i<2; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<m; k++){
					int v = _readInt() + offset;
					vis[v]++;
					vx[i][v] = j;
					vy[i][v] = k;
				}
			}
		}
		int cnt = 0, bad = 0;
		for(int i=0; i<MAXN; i++){
			if(vis[i] != 2) continue;
			cnt++;
			if(p1[vx[0][i]] == -1) p1[vx[0][i]] = vx[1][i];
			if(p2[vy[0][i]] == -1) p2[vy[0][i]] = vy[1][i];
			if(p1[vx[0][i]] != vx[1][i]) bad = 1;
			if(p2[vy[0][i]] != vy[1][i]) bad = 1;
		}
		if(cnt != n * m) bad = 1;
		puts(bad ? "NIE" : "TAK");
	}
}
