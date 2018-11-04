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

bool palin(int x, int b){
	vector<int> v, u;
	while(x){
		v.push_back(x % b);
		x /= b;
	}
	u = v;
	reverse(u.begin(), u.end());
	return (u == v);
}
int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int u;
		scanf("%d",&u);
		int bad = 1;
		for(int i=2; i<=64; i++){
			if(palin(u, i)){
				puts("1");
				bad = 0;
				break;
			}
		}
		if(bad) puts("0");
	}
}