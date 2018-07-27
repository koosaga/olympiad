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
#include <bitset>
#include <iostream>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 200005;
const int mod = 1e9 + 7;

int f(int x){
	int ans = 0;
	while(x){
		ans += (x % 10) * (x % 10);
		x /= 10;
	}
	return ans;
}

int main(){
	int n;
	cin >> n;
	for(int i=0; i<10000; i++) n = f(n);
	if(n == 1) puts("HAPPY");
	else puts("UNHAPPY");
}

