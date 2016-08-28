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
 
int a[300005], n, m;
 
int main(){
	a[0] = 2e9;
	scanf("%d %d",&n,&m);
	for(int i=1; i<=n; i++){
		scanf("%d",&a[i]);
		a[i] = min(a[i], a[i-1]);
	}
	int p = n+1;
	while(m--){
		int x;
		scanf("%d",&x);
		p--;
		while(p > 0 && a[p] < x) p--;
	}
	printf("%d",max(p,0));
}