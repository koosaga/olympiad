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

int n, x[1005], y[1005];

inline double hyp(double x, double y){
	return x * x + y * y;
}

int main(){
	scanf("%d",&n);
	double px = 0, py = 0;
	for(int i=0; i<n; i++){
		scanf("%d %d",&x[i],&y[i]);
		px += x[i];
		py += y[i];
	}
	px /= n, py = n;
	double rat = 1.0;
	double maxv = 0;
	for(int i=0; i<40000; i++){
		maxv = 0;
		int maxp = -1;
		for(int j=0; j<n; j++){
			double tmp = hyp(x[j] - px, y[j] - py);
			if(maxv <= tmp){
				maxv = tmp;
				maxp = j;
			}
		}
		px += (x[maxp] - px) * rat;
		py += (y[maxp] - py) * rat;
		rat *= 0.999;
	}
	printf("%.3f %.3f\n%.3f",px,py,sqrt(maxv));
}