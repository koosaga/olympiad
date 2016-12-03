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

char s[6][6];

bool sm(char a, char b, char c){
	return a == b && b == c;
}
int main(){
	int t;
	cin >> t;
	while(t--){
		for(int i=0; i<5; i++) scanf("%s",s[i]);
		bool vis[128] = {};
		for(int i=0; i<5; i++){
			for(int j=0; j<3; j++){
				if(sm(s[i][j], s[i][j+1], s[i][j+2])){
					vis[s[i][j]] = 1;
				}
				if(sm(s[j][i], s[j+1][i], s[j+2][i])){
					vis[s[j][i]] = 1;
				}
			}
		}
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				if(sm(s[i][j], s[i+1][j+1], s[i+2][j+2])){
					vis[s[i][j]] = 1;
				}
				if(sm(s[i][4-j], s[i+1][3-j], s[i+2][2-j])){
					vis[s[i][4-j]] = 1;
				}
			}
		}
		if(vis['A'] && vis['B']) puts("draw");
		else if(vis['A']) puts("A wins");
		else puts("B wins");
	}
}