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

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		int n, m;
		int a[1005] = {}, b[1005] ={};
		scanf("%d %d",&n,&m);
		for(int i=0; i<m; i++){
			int p, q, r, s;
			scanf("%d %d %d %d",&p,&q,&r,&s);
			a[p] += r, b[p] += s;
			a[q] += s, b[q] += r;
		}
		double minv = 1e9, maxv = 0;
		for(int i=1; i<=n; i++){
			double tmp;
			if(a[i] + b[i] > 0){
				tmp = (1.0 * a[i] * a[i]) / (1.0 * a[i] * a[i] + 1.0 * b[i] * b[i]);
			}
			else tmp = 0;
			minv = min(minv, tmp);
			maxv = max(maxv, tmp);
		}
		minv = minv * 1000 + 1e-6;
		maxv = maxv * 1000 + 1e-6;
		printf("%d\n%d\n",(int)maxv, (int)minv);
	}
}