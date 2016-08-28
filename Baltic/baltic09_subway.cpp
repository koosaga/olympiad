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

int l, n, a[100005];

int main(){
	scanf("%d %d",&l,&n);
	for(int i=0; i<n; i++){
		scanf("%d %*s",&a[i]);
	}
	sort(a, a+n);
	for(int i=1; i<n; i+=2){
		a[i] = 2 * l - a[i];
	}
	sort(a, a+n);
	double maxi = -1e9, mini = 1e9;
	for(int i=0; i<n; i++){
		maxi = max(maxi, a[i] - 2.0 * i * l / n);
		mini = min(mini, a[i] - 2.0 * i * l / n);
	}
	printf("%.10f",(maxi - mini) / 2);
}