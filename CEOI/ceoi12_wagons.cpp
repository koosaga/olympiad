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

int n, k, s, arr[20005];
bool adj[1005][1005];
vector<int> sink[1005];

int ret = -1, pa, pb, pc;

void backtrack(int pos, int a, int b, int c, int cmode){
	if(cmode == 3){
		if(ret < pos){
			ret = pos;
			pa = a, pb = b, pc = c;
		}
		if(pos == n && pb != 0 && (b == 0 && c == 0)){
			pa = a, pb = b, pc = c;
		}
		if(pos == n && pc != 0 && c == 0){
			pa = a, pb = b, pc = c;
		}
		return;
	}
	if(cmode == 0){
		if(adj[arr[pos]][a] || adj[arr[pos]][b] || (b == 0 && adj[arr[pos]][c])){
			backtrack(pos + 1, a, b, c, cmode);
		}
		else{
			if(!a) for(auto &i : sink[arr[pos]]){
				backtrack(pos + 1, i, b, c, cmode);
			}
			if(!b) for(auto &i : sink[arr[pos]]){
				backtrack(pos + 1, a, i, c, cmode);
			}
			if(!b&&!c) for(auto &i : sink[arr[pos]]){
				backtrack(pos + 1, a, b, i, cmode);
			}
			backtrack(pos, a, b, c, cmode + 1);
		}
	}
	if(cmode == 1){
		if(adj[arr[pos]][b] || adj[arr[pos]][c]){
			backtrack(pos + 1, a, b, c, cmode);
		}
		else{
			if(!b) for(auto &i : sink[arr[pos]]){
				backtrack(pos + 1, a, i, c, cmode);
			}
			if(!c) for(auto &i : sink[arr[pos]]){
				backtrack(pos + 1, a, b, i, cmode);
			}
			backtrack(pos, a, b, c, cmode + 1);
		}
	}
	if(cmode == 2){
		if(adj[arr[pos]][c]){
			backtrack(pos + 1, a, b, c, cmode);
		}
		else{
			if(c == 0){
				for(auto &i : sink[arr[pos]]){
					backtrack(pos + 1, a, b, i, cmode);
				}
			}
			backtrack(pos, a, b, c, cmode + 1);
		}
	}
}
int main(){
	scanf("%d %d %d",&n,&k,&s);
	for(int i=1; i<=s; i++){
		int t;
		while(1){
			scanf("%d",&t);
			if(t == 0) break;
			adj[t][i] = 1;
			sink[t].push_back(i);
		}
	}
	for(int i=0; i<n; i++){
		scanf("%d",&arr[i]);
	}
	backtrack(0, 0, 0, 0, 0);
	printf("%d\n%d %d %d",ret, pa, pb, pc);
}