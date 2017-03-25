#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n;
char str[25][15];
int chk[25][15];
bool vis[21][10][1<<10][1<<10];

inline int get_bit(int msk, int pos){
	return msk & (1 << pos);
}

bool f(int x, int y, int m1, int m2){
	if(x == 4 * n - 1) return 1;
	if(y == 2 * n) return f(x+1, 0, m1, m2);
	if(vis[x][y][m1][m2]) return 0;

	int nxt1 = (m1 & ~(1 << y)) ^ get_bit(m2, y);
	int nxt2 = m2 ^ get_bit(m2, y);

	if(chk[x][y]){
		if(f(x, y+1, nxt1, nxt2)) return 1;
		vis[x][y][m1][m2] = 1;
		return 0;
	}

	if(!get_bit(nxt1, y) && !chk[x+1][y] && !chk[x+2][y]){
		int col = (x+1) + (y&1) * 3;
		col %= 6;
		col++;
		chk[x][y] = chk[x+1][y] = chk[x+2][y] = col;
		if(f(x, y + 1, nxt1 | (1 << y), nxt2 | (1 << y))) return 1;
		chk[x][y] = chk[x+1][y] = chk[x+2][y] = 0;
	}
	if((x + y + n) % 2 == 0 && !get_bit(nxt1, y) && !get_bit(nxt2, y+1) 
			&& !chk[x+1][y] && !chk[x+1][y+1]){
		int col = (x+1) + (y&1) * 3;
		col %= 6;
		col++;
		chk[x][y] = chk[x+1][y] = chk[x+1][y+1] = col;
		if(f(x, y+1, nxt1 | (1<<y), nxt2 | (1<<(y+1)))) return 1;
		chk[x][y] = chk[x+1][y] = chk[x+1][y+1] = 0;
	}
	if((x + y + n - 1) % 2 == 0 && y 
			&& !get_bit(nxt1, y) && !get_bit(nxt1, y-1) && 
			!chk[x+1][y] && !chk[x+1][y-1]){
		int col = (x+1) + (y&1) * 3;
		col %= 6;
		col++;
		chk[x][y] = chk[x+1][y] = chk[x+1][y-1] = col;
		if(f(x, y+1, nxt1 | (1<<y) | (1<<(y-1)), nxt2)) return 1;
		chk[x][y] = chk[x+1][y] = chk[x+1][y-1] = 0;
	}
	if((x + y + n - 1) % 2 == 0 && !chk[x][y+1] && !chk[x+1][y+1] &&
			!get_bit(nxt1, y+1) && !get_bit(nxt2, y+1)){
		int col = x + ((y+1)&1) * 3;
		col %= 6;
		col++;
		chk[x][y] = chk[x][y+1] = chk[x+1][y+1] = col;
		if(f(x, y+1, nxt1 | (1<<(y+1)), nxt2 | (1<<(y+1)))) return 1;
		chk[x][y] = chk[x][y+1] = chk[x+1][y+1] = 0;
	}
	if((x + y + n - 1) % 2 == 0 && !chk[x][y+1] && !chk[x+1][y] &&
			!get_bit(nxt1, y) && !get_bit(nxt1, y+1)){
		int col = x + (y&1) * 3;
		col %= 6;
		col++;
		chk[x][y] = chk[x][y+1] = chk[x+1][y] = col;
		if(f(x, y+1, nxt1 | (1<<y) | (1<<(y+1)), nxt2)) return 1;
		chk[x][y] = chk[x][y+1] = chk[x+1][y] = 0;
	}
	vis[x][y][m1][m2] = 1;
	return 0;
}

int sz[20];

int main(){
	cin >> n;
	for(int i=0; i<4*n+3; i++){
		for(int j=0; j<2*n+3; j++){
			chk[i][j] = -1;
		}
	}
	int cnt = 0;
	for(int i=0; i<2*n; i++){
		string buf;
		cin >> buf;
		sz[i] = buf.size();
		int dis = max(n - 1 - i, i - n);
		for(int j=dis; j<dis + buf.size(); j++){
			if(buf[j-dis] == '0'){
				chk[j][i] = 0;
				cnt++;
			}
		}
	}
	if(cnt % 3 != 0){
		puts("nemoguce");
		return 0;
	}
	if(!f(0, 0, 0, 0)){
		puts("nemoguce");
		return 0;
	}
	for(int i=0; i<2*n; i++){
		int dis = max(n - 1 - i, i - n);
		for(int j=dis; j<dis + sz[i]; j++){
			if(chk[j][i] == -1) printf(".");
			else printf("%d", chk[j][i]);
		}
		puts("");
	}
}

