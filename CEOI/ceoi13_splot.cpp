#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXN = 100005;

// empty, sreach, treach, streach, path, 
const int series[5][5] = {
	{0, 1, 2, 3, 4},
	{1, -1,  3, -1, 3},
	{2, -1, -1, -1, 2},
	{3, -1, -1, -1, 3},
	{4,  1,  3,  3, 4}
};

int fuck[2][2][5][5];

void genFuck(){
	memset(fuck, -1, sizeof(fuck));
	// both empty
	fuck[0][0][0][0] = 0;
	fuck[1][1][0][0] = 3;
	fuck[0][1][0][0] = fuck[1][0][0][0] = 69; // special case.
	// both passable -> path
	fuck[0][0][0][1] = fuck[0][0][0][2] = fuck[0][0][0][3] = fuck[0][0][0][4] = 4;
	// left
	fuck[0][1][0][1] = 1;
	fuck[0][1][0][4] = 1;
	// right
	fuck[1][0][0][2] = 2;
	fuck[1][0][0][4] = 2;

	fuck[0][0][1][1] = 1;
	fuck[0][1][1][1] = 3;
	fuck[0][0][1][2] = 3;
	fuck[0][0][1][3] = 3;
	fuck[0][0][1][4] = 4;
	fuck[0][1][1][4] = 1;
	
	fuck[0][0][2][2] = 2;
	fuck[1][0][2][2] = 3;
	fuck[0][0][2][3] = 3;
	fuck[0][0][2][4] = 4;
	fuck[1][0][2][4] = 2;

	fuck[0][0][3][3] = 3;
	fuck[0][0][3][4] = 4;
	fuck[0][0][4][4] = 4;
	fuck[1][0][4][4] = 2;
	fuck[0][1][4][4] = 1;

	for(int i = 0; i < 2; i++){
		for(int j = 0; j < 2; j++){
			for(int k = 0; k < 5; k++){
				for(int l = 0; l < k; l++){
					fuck[i][j][k][l] = fuck[i][j][l][k];
				}
			}
		}
	}
}

struct foo{
	int val[5];
}dp[MAXN];

int n;

struct parsetree{
	char c;
	char x, y;
	int l, r;
}a[MAXN];

char str[MAXN];
int ptr;

void solve(int p){
	if(a[p].c == 'S'){
		solve(a[p].l);
		solve(a[p].r);
		fill(dp[p].val, dp[p].val + 5, -1e9);
		for(int k = 0; k < 5; k++){
			for(int l = 0; l < 5; l++){
				if(~series[k][l]){
					dp[p].val[series[k][l]] = 
					max(dp[p].val[series[k][l]],
					dp[a[p].l].val[k] + dp[a[p].r].val[l]);
				}
			}
		}
	}
	else if(a[p].c == 'P'){
		solve(a[p].l);
		solve(a[p].r);
		fill(dp[p].val, dp[p].val + 5, -1e9);
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				for(int k = 0; k < 5; k++){
					for(int l = 0; l < 5; l++){
						if(a[p].x == 'x' && i == 0) continue;
						if(a[p].y == 'x' && j == 0) continue;
						if(fuck[i][j][k][l] == 69){
							for(int j = 1; j < 4; j++){
								dp[p].val[j] = max(dp[p].val[j], 1 + dp[a[p].l].val[k] + dp[a[p].r].val[l]);
							}
							continue;
						}
						if(~fuck[i][j][k][l]){
							dp[p].val[fuck[i][j][k][l]] = 
							max(dp[p].val[fuck[i][j][k][l]], 
							i + dp[a[p].l].val[k] + dp[a[p].r].val[l] + j);
						}
					}
				}
			}
		}
	}
	else{
		fill(dp[p].val + 1, dp[p].val + 4, 1);
		if(a[p].c == 'o') dp[p].val[4] = dp[p].val[0] = 0;
		else dp[p].val[4] = dp[p].val[0] =  -1e9;
	}
}

int parse(){
	int p = n++;
	a[p].c = str[ptr++];
	if(a[p].c == 'S'){
		a[p].l = parse();
		a[p].r = parse();
		assert(str[ptr++] == '#');
	}
	else if(a[p].c == 'P'){
		a[p].x = str[ptr++];
		assert(str[ptr++] == '|');
		a[p].l = parse();
		a[p].r = parse();
		assert(str[ptr++] == '|');
		a[p].y = str[ptr++];
		assert(str[ptr++] == '#');
	}
//	printf("%d -> (%d, %d, %c, %c)\n", p, a[p].l, a[p].r, a[p].x, a[p].y);
	return p;
}

string s;

void track(int p, int c){
//	printf("node %d -> %d\n", p, c);
	if(a[p].c == 'S'){
		int lhs = -1, rhs = -1;
		for(int k = 0; k < 5; k++){
			for(int l = 0; l < 5; l++){
				if(series[k][l] == c && dp[p].val[series[k][l]] == dp[a[p].l].val[k] + dp[a[p].r].val[l]){
					lhs = k;
					rhs = l;
				}
			}
		}
		s += "S";
		track(a[p].l, lhs);
		track(a[p].r, rhs);
		s += "#";
	}
	else if(a[p].c == 'P'){
		int lhs = -1, rhs = -1;
		int x = -1, y = -1;
		for(int i = 0; i < 2; i++){
			for(int j = 0; j < 2; j++){
				for(int k = 0; k < 5; k++){
					for(int l = 0; l < 5; l++){
						if(a[p].x == 'x' && i == 0) continue;
						if(a[p].y == 'x' && j == 0) continue;
						if(fuck[i][j][k][l] == c && 
								dp[p].val[fuck[i][j][k][l]] == i + dp[a[p].l].val[k] + dp[a[p].r].val[l] + j){
							lhs = k;
							rhs = l;
							x = i;
							y = j;
						}
					}
				}
			}
		}
		if(lhs == -1 && rhs == -1){
			x = 1;
			y = 0;
			if(a[p].y == 'x') swap(x, y);
			lhs = 0;
			rhs = 0;
		}
		s += "P";
		s += (x ? "x" : "o");
		s += "|";
		track(a[p].l, lhs);
		track(a[p].r, rhs);
		s += "|";
		s += (y ? "x" : "o");
		s += "#";
	}
	else{
		if(a[p].c == 'o' && (c == 0 || c == 4)) s += "o";
		else s += "x";
	}
}


int main(){
	genFuck();
	scanf("%s", str);
	int r = parse();
	solve(r);
    printf("%d\n", max(dp[r].val[1], dp[r].val[4]));
    track(r, dp[r].val[1] > dp[r].val[4] ? 1 : 4);
    cout << s << endl;
}
