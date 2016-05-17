#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

char str[30][100], ret[30][100];
int r, c, dp[13][41][1<<12][2];

int f(int x, int y, int bit, int lef){
	if(y == c / 2) return 0;
	if(x == r / 2){
		if(lef) return 1e9;
		return dp[x][y][bit][lef] = f(0, y+1, bit, 0);
	}
	if(~dp[x][y][bit][lef]) return dp[x][y][bit][lef];
	int ret = 1e9;
	if(str[2*x+1][2*y+1] == 'X'){
		if(lef && (bit >> x) % 2 == 0){
			ret = min(ret, f(x+1, y, bit, 0) + 2);
		}
		if(!lef && str[2*x+2][2*y+1] == ' ' && (bit >> x) % 2 == 0){
			ret = min(ret, f(x+1, y, bit, 1));
		}
		if(!lef && (bit >> x) % 2 == 1){
			ret = min(ret, f(x+1, y, bit ^ (1<<x), 0) + 2);
		}
		if(!lef && str[2*x+1][2*y+2] == ' ' && (bit >> x) % 2 == 0){
			ret = min(ret, f(x+1, y, bit ^ (1<<x), 0));
		}
	}
	else{
		if(!lef && (bit >> x) % 2 == 0){
			ret = min(ret, f(x+1, y, bit, 0));
		}
		if(lef && (bit >> x) % 2 == 1){
			ret = min(ret, f(x+1, y, bit ^ (1<<x), 0) + 4);
		}
		if(!lef && (bit >> x) % 2 == 1 && str[2*x+1][2*y+2] == ' '){
			ret = min(ret, f(x+1, y, bit, 0) + 2);
		}
		if(lef && (bit >> x) % 2 == 0 && str[2*x+1][2*y+2] == ' '){
			ret = min(ret, f(x+1, y, bit ^ (1<<x), 0) + 2);
		}
		if(lef && (bit >> x) % 2 == 0 && str[2*x+2][2*y+1] == ' '){
			ret = min(ret, f(x+1, y, bit, 1) + 2);
		}
		if(!lef && (bit >> x) % 2 == 0 && str[2*x+1][2*y+2] == ' ' && str[2*x+2][2*y+1] == ' '){
			ret = min(ret, f(x+1, y, bit ^ (1<<x), 1));
		}
		if(!lef && (bit >> x) % 2 == 1 && str[2*x+2][2*y+1] == ' '){
			ret = min(ret, f(x+1, y, bit ^ (1<<x), 1) + 2);
		}
	}
	return dp[x][y][bit][lef] = ret;
}

void track(int x, int y, int bit, int lef){
	if(y == c / 2) return;
	if(x == r / 2){
		track(0, y+1, bit, 0);
		return;
	}
	if(str[2*x+1][2*y+1] == 'X'){
		if(lef && (bit >> x) % 2 == 0 && f(x, y, bit, lef) == f(x+1, y, bit, 0) + 2){
			track(x+1, y, bit, 0);
		}
		else if(!lef && str[2*x+2][2*y+1] == ' ' && (bit >> x) % 2 == 0 && f(x, y, bit, lef) == f(x+1, y, bit, 1)){
			str[2*x+2][2*y+1] = '.';
			track(x+1, y, bit, 1);
		}
		else if(!lef && (bit >> x) % 2 == 1 && f(x, y, bit, lef) == f(x+1, y, bit ^ (1<<x), 0) + 2){
			track(x+1, y, bit ^ (1<<x), 0);
		}
		else if(!lef && str[2*x+1][2*y+2] == ' ' && (bit >> x) % 2 == 0 && f(x, y, bit, lef) == f(x+1, y, bit ^ (1<<x), 0)){
			str[2*x+1][2*y+2] = '.';
			track(x+1, y, bit ^ (1<<x), 0);
		}
		else{
			assert(0);
		}
	}
	else{
		if(!lef && (bit >> x) % 2 == 0 && f(x, y, bit, lef) == f(x+1, y, bit, 0)){
			track(x+1, y, bit, 0);
		}
		else if(lef && (bit >> x) % 2 == 1 && f(x, y, bit, lef) == f(x+1, y, bit ^ (1<<x), 0) + 4){
			str[2*x+1][2*y+1] = '.';
			track(x+1, y, bit ^ (1<<x), 0);
		}
		else if(!lef && (bit >> x) % 2 == 1 && str[2*x+1][2*y+2] == ' ' && f(x, y, bit, lef) == f(x+1, y, bit, 0) + 2){
			str[2*x+1][2*y+1] = '.';
			str[2*x+1][2*y+2] = '.';
			track(x+1, y, bit, 0);
		}
		else if(lef && (bit >> x) % 2 == 0 && str[2*x+1][2*y+2] == ' ' && f(x, y, bit, lef) == f(x+1, y, bit ^ (1<<x), 0) + 2){
			str[2*x+1][2*y+2] = '.';
			str[2*x+1][2*y+1] = '.';
			track(x+1, y, bit ^ (1<<x), 0);
		}
		else if(lef && (bit >> x) % 2 == 0 && str[2*x+2][2*y+1] == ' ' && f(x, y, bit, lef) == f(x+1, y, bit, 1) + 2){
			str[2*x+2][2*y+1] = '.';
			str[2*x+1][2*y+1] = '.';
			track(x+1, y, bit, 1);
		}
		else if(!lef && (bit >> x) % 2 == 0 && str[2*x+1][2*y+2] == ' ' && str[2*x+2][2*y+1] == ' ' && f(x, y, bit, lef) == f(x+1, y, bit ^ (1<<x), 1)){
			str[2*x+2][2*y+1] = '.';
			str[2*x+1][2*y+2] = '.';
			str[2*x+1][2*y+1] = '.';
			track(x+1, y, bit ^ (1<<x), 1);
		}
		else if(!lef && (bit >> x) % 2 == 1 && str[2*x+2][2*y+1] == ' ' && f(x, y, bit, lef) == f(x+1, y, bit ^ (1<<x), 1) + 2){
			str[2*x+2][2*y+1] = '.';
			str[2*x+1][2*y+1] = '.';
			track(x+1, y, bit ^ (1<<x), 1);
		}
		else{
			assert(0);
		}
	}
}

int main(){
	memset(dp, -1, sizeof(dp));
	scanf("%d %d\n",&r,&c);
	for(int i=0; i<r; i++){
		fgets(str[i], 88, stdin);
	}
	cout << f(0, 0, 0, 0) << endl;
	track(0, 0, 0, 0);
	for(int i=0; i<r; i++) cout << str[i];
}