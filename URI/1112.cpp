// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1112
#include <cstdio>
#include <algorithm>
#define MAXN 1010
#define LSOne(S) (S & (-S))
#define gc getchar_unlocked
void getint(int &x){
    register int c = gc();
    x = 0;
    for(;(c<48 || c>57);c = gc());
    for(;c>47 && c<58;c = gc()) {x = (x<<1) + (x<<3) + c - 48;}
}
using namespace std;
int bit[MAXN][MAXN];
void update(int x, int y, int val){
	while(x < MAXN){
		int ty = y;
		while(ty < MAXN){
			bit[x][ty] += val;
			ty += LSOne(ty);
		}
		x += LSOne(x);
	}
}
int sum(int x, int y){
	if (x <= 0 || y <= 0) return 0;
	int answer = 0;
	while(x > 0){
		int ty = y;
		while(ty > 0){
			answer += bit[x][ty];
			ty -= LSOne(ty);
		}
		x -= LSOne(x);
	}
	return answer;
}
int query(int x1,int y1, int x2, int y2){
	return sum(x2,y2) + sum(x1-1,y1-1) - sum(x1-1,y2) - sum(x2,y1-1);
}
int main(){
	int x,y,z;
	while(1){
		getint(x);
		getint(y);
		getint(z);
		if (x == 0 && y == 0 && z == 0) break;
		for(int i=0;i<=x+1;i++){
			for(int j=0;j<=y+1;j++){
				bit[i][j] = 0;
			}
		}
		int q;
		getint(q);
		while(q--){
			char op;
			scanf("%c",&op);
			if (op == 'A'){
				int a,b,c;
				getint(a);
				getint(b);
				getint(c);
				b++;
				c++;
				update(b,c,a);
			}
			if (op == 'P'){
				int a,b,c,d;
				getint(a);
				getint(b);
				getint(c);
				getint(d);
				if (a > c) swap(a,c);
				if (b > d) swap(b,d);
				printf("%d\n",z*query(a+1,b+1,c+1,d+1));
			}
		}
		printf("\n");
	}
	return 0;
}
