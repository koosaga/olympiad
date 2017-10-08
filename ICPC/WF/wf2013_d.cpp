#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <assert.h>
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
const lint inf = (1ll << 63) - 1;

lint bino[63][63];
int plist[105];
map<lint, lint> mp;

inline bool multiply(lint a, lint b){return a <= inf / b;}

void generate(lint x, lint y, int cpk, int l, int sum){
	if(cpk == 25) return;
	if(x > 1){
		if(mp.find(x) != mp.end()) mp[x] = min(mp[x], y);
		else mp[x] = y;
	}
	for(int i=0; i<=l && sum+i <= 62; i++){
		if(multiply(x, bino[sum+i][i])){
			generate(x * bino[sum+i][i], y, cpk + 1, i, sum + i);
		}
		if(multiply(y, plist[cpk])){
			y *= plist[cpk];
		}
		else break;
	}
}

bool isp(int x){
	for(int i=2; i*i<=x; i++){
		if(x%i == 0) return 0;
	}
	return 1;
}

int main(){
	int p = 2;
	for(int i=0; i<25; i++){
		while(!isp(p)) p++;
		plist[i] = p;
		p++;
	}
	for(int i=0; i<=62; i++){
		bino[i][0] = 1;
		for(int j=1; j<=i; j++){
			bino[i][j] = bino[i-1][j] + bino[i-1][j-1];
		}
	}
	generate(1, 1, 0, 62, 0);
	lint x;
	mp[1] = 2;
	while(~scanf("%lld",&x)){
		printf("%lld %lld\n",x, mp[x]);
	}
}