#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
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

bool adj[53][53];
bool ok[53];

int code(char* t, int p){
	if(t[p] == '0') return 52;
	return (t[p] - 'A') + (t[p+1] == '-' ? 26 : 0);
}

int bande(int x){
	if(x == 52) return 52;
	return (x + 26) % 52;
}

int main(){
	int n;
	scanf("%d",&n);
	while(n--){
		char s[10];
		scanf("%s",s);
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				if(i == j) continue;
				adj[code(s,2*i)][bande(code(s,2*j))] = 1;
				adj[code(s,2*j)][bande(code(s,2*i))] = 1;
			}
		}
	}
	for(int i=0; i<52; i++){
		for(int j=0; j<52; j++){
			for(int k=0; k<52; k++){
				adj[j][k] |= (adj[j][i] & adj[i][k]);
			}
		}
	}
	for(int i=0; i<52; i++){
		if(adj[i][i]){
			puts("unbounded");
			return 0;
		}
	}
	puts("bounded");
}