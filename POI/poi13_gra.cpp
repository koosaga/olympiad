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

int n, m;
bool chk[500005];
vector<int> gph[500005];
vector<int> dap;

int main(){
	scanf("%d %d %*d",&n,&m);
	for(int i=0; i<m; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		gph[s].push_back(e);
		gph[e].push_back(s);
	}
	for(int i=1; i<=n; i++){
		if(!chk[i]){
			chk[i] = 1;
			for(auto &j : gph[i]){
				chk[j] = 1;
				for(auto &k : gph[j]){
					chk[k] = 1;
				}
			}
			dap.push_back(i);
		}
	}
	printf("%d\n", dap.size());
	for(auto &i : dap) printf("%d ", i);
}
