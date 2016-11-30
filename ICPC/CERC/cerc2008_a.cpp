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

bool che[3000050];

int psum[1000005];

int main(){
	for(int i=2; i<=3000007; i++){
		for(int j=2*i; j<=3000007; j+=i){
			che[j] = 1;
		}
	}
	for(int i=1; i<=1000000; i++){
		psum[i] = psum[i-1] + (che[3 * i + 7] ? 0 : 1);
	}
	int t;
	scanf("%d",&t);
	while(t--){
		int u;
		scanf("%d",&u);
		printf("%d\n",psum[u]);
	}
}