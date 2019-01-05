#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using real_t = long double;
using pi = pair<int, int>;
const int MAXN = 105;

int n, a, b;

int d1[MAXN][MAXN];
int d2[MAXN][MAXN];
int petyr(int x, int y);
int varys(int x, int y);

int varys(int x, int y){
	if(x == 0 && y == 0) return 0;
	if(~d2[x][y]) return d2[x][y];
	for(int i=1; i<=b; i++){
		if(x>=i&&!petyr(x - i, y)) return d2[x][y] = 1;
		if(y>=i&&!petyr(x,y-i)) return d2[x][y] = 1;
	}
	return d2[x][y] = 0;
}

int petyr(int x, int y){
	if(x == 0 && y == 0) return 0;
	if(~d1[x][y]) return d1[x][y];
	for(int i=1; i<=a; i++){
		if(x>=i&&!varys(x - i, y)) return d1[x][y] = 1;
		if(y>=i&&!varys(x, y - i)) return d1[x][y] = 1;
	}
	return d1[x][y] = 0;
}


int main(){
	memset(d1,-1, sizeof(d1));
	memset(d2,-1,sizeof(d2));
	int nimv = 0;
	scanf("%d %d %d",&n,&a,&b);
	if(a == b){
		for(int i=0; i<n; i++){
			int x; scanf("%d",&x);
			x %= (a + 1);
			nimv ^= x;
		}
	}
	if(a > b){
		for(int i=0; i<n; i++){
			int x; scanf("%d",&x);
			if(x > b){
				puts("Petyr");
				return 0;
			}
			nimv ^= x;
		}
	}
	if(a < b){
		vector<int> v;
		for(int i=0; i<n; i++){
			int x; scanf("%d",&x);
			if(x > a) v.push_back(x);
			else nimv ^= x;
		}
		if(v.size() > 1){
			puts("Varys");
			return 0;
		}
		if(v.size() == 1){
			// If can adjust to: 
			// x <= a
			// nimv == 0
			// then you win
			for(int i=1; i<=a; i++){
				if(v[0] - i == nimv){
					puts("Petyr");
					return 0;
				}
			}
			puts("Varys");
			return 0;
		}
	}
	puts(nimv ? "Petyr" : "Varys");
}
