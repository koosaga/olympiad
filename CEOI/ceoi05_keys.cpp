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

int n, m;
int last[1000005], ret[1000005];

int main(){
	scanf("%d %d",&n,&m);
	for(int i=0; i<m; i++){
		int t;
		scanf("%d",&t);
		last[t] = i+1;
	}
	for(int i=1; i<=n; i++) ret[i] = i;
	sort(ret+ 1, ret + n + 1, [&](const int &a, const int &b){
		return last[a] < last[b];
	});
	int p = 1;
	while(last[ret[p]] == 0) p++;
	printf("%d\n",n + 1 - p);
	for(int i=p; i<=n; i++) printf("%d ",ret[i]);
}