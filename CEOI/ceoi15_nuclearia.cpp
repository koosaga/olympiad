#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long lint;
  
int w, h, n, q;
lint **dx1, **low1, **low2;
lint *low3, *low4;
 
void Trace1(int depth, int px, int py, int d){
	if(depth == 0) return;
	if(px == 1 && py == 1){
		dx1[1][1] += 1ll * depth * d;
		return;
	}
	if(px == 1){
		int dx = min(py-1, depth);
		low4[py - dx + 1] += d;
		low4[py + 1] -= d;
		Trace1(depth - dx, 1, py - dx, d);
		return;
	}
	if(py == 1){
		int dx = min(px-1, depth);
		low3[px - dx + 1] += d;
		low3[px + 1] -= d;
		Trace1(depth - dx, px - dx, 1, d);
		return;
	}
	int dx = min(px-1, min(py-1, depth));
	low1[px - dx + 1][py - dx + 1] += d;
	low1[px + 1][py + 1] -= d;
	Trace1(depth - dx, px - dx, py - dx, d);
}
  
void Trace2(int depth, int px, int py, int d){
	if(depth == 0) return;
	if(px == 1){
		int dx = min(h + 1 - py, depth);
		low4[py] += d;
		low4[py + dx] -= d;
		return;
	}
	if(py == h+1) return;
	int dx = min(depth, min(h + 1 - py, px - 1));
	low2[px - dx + 1][py + dx - 1] += d;
	low2[px+1][py -1] -= d;
	Trace2(depth - dx, px - dx, py + dx, d);
}
  
void Trace3(int depth, int px, int py, int d){
	if(depth == 0) return;
	if(px == w+1) return;
	if(py == 1){
		int dx = min(w + 1 - px, depth);
		low3[px] += d;
		low3[px + dx] -= d;
		return;
	}
	int dx = min(depth, min(w + 1 - px, py - 1));
	low2[px][py] += d;
	low2[px + dx][py - dx] -= d;
	Trace3(depth - dx, px + dx, py - dx, d);
}
  
void Trace4(int depth, int px, int py, int d){
	if(depth == 0) return;
	if(px == w+1 || py == h+1) return;
	int dx = min(depth, min(h + 1 - py, w + 1 - px));
	low1[px][py] += d;
	low1[px + dx][py + dx] -= d;
	Trace4(depth - dx, px + dx, py + dx, d);
}
 
 
static char _buffer[1024];
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
  
int main(){
	w = _readInt();
	h = _readInt();
	n = _readInt();
	dx1 = (lint**) calloc(w+2, sizeof(lint*));
	low1 = (lint**) calloc(w+2, sizeof(lint*));
	low2 = (lint**) calloc(w+2, sizeof(lint*));
	low3 = (lint*) calloc(w+2, sizeof(lint));
	low4 = (lint*) calloc(h+2, sizeof(lint));
	for(int i=0; i<=w+1; i++){
		dx1[i] = (lint*)calloc(h+2, sizeof(lint));
		low1[i] = (lint*)calloc(h+2, sizeof(lint));
		low2[i] = (lint*)calloc(h+2, sizeof(lint));
	}
	for(int i=0; i<n; i++){
		int x, y, a, b;
		x = _readInt();
		y = _readInt();
		a = _readInt();
		b = _readInt();
		int rad = a / b;
		int radx = max(w-x,x) + 1;
		int rady = max(h-y,y) + 1;
		int mrad = max(radx, rady);
		lint tmp1 = a % b + 1ll * max(0,rad - mrad) * b;
		int tmp2 = min(rad, mrad);
		dx1[max(1,x-rad)][max(1,y-rad)] += tmp1;
		dx1[max(1,x-rad)][min(h+1,y+rad+1)] -= tmp1;
		dx1[min(w+1,x+rad+1)][max(1,y-rad)] -= tmp1;
		dx1[min(w+1,x+rad+1)][min(h+1,y+rad+1)] += tmp1;
		Trace1(tmp2, x, y, b);
		Trace2(tmp2, x, y+1, -b);
		Trace3(tmp2, x+1, y, -b);
		Trace4(tmp2, x+1, y+1, b);
	}
	for(int i=1; i<=w; i++){
		for(int j=1; j<=h; j++){
			low1[i][j] += low1[i-1][j-1];
			low2[i][j] += low2[i-1][j+1];
		}
	}
	for(int i=1; i<=w; i++){
		low3[i] += low3[i-1];
		dx1[i][1] += low3[i];
	}
	for(int i=1; i<=h; i++){
		low4[i] += low4[i-1];
		dx1[1][i] += low4[i];
	}
	for(int i=1; i<=w; i++){
		for(int j=1; j<=h; j++){
			dx1[i][j] += dx1[i][j-1] + dx1[i-1][j] - dx1[i-1][j-1];
			dx1[i][j] += low1[i][j] + low2[i][j];
		}
	}
	for(int i=1; i<=w; i++){
		for(int j=1; j<=h; j++){
			dx1[i][j] = dx1[i-1][j] + dx1[i][j-1] - dx1[i-1][j-1] + dx1[i][j];
		}
	}
	int q = _readInt();
	while(q--){
		int sx = _readInt();
		int sy = _readInt();
		int ex = _readInt();
		int ey = _readInt();
		lint res = dx1[ex][ey] - dx1[sx-1][ey] - dx1[ex][sy-1] + dx1[sx-1][sy-1];
		res += (ex - sx + 1) * (ey - sy + 1) / 2;
		res /= 1ll * (ex - sx + 1) * (ey - sy + 1);
		printf("%lld\n",res);
	}
}