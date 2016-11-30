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
		scanf("%d %d",&n,&m);
		int t = (m - 1) / 2;
		int u = n - m + (m - 1) / 2;
		printf("%d\n",(t & u) == t);
	}
}