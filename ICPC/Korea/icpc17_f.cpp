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
const int MAXN = 300005;
const int mod = 1e9 + 7;

pi rec(int n, int m){
	if(n == 1) return pi(0, 0);
	else{
		int s = n * n / 4;
		if(m < s){
			auto x = rec(n / 2, m);
			x = pi(x.second, x.first);
			return x;
		}
		else if(m < 2 * s){
			auto x = rec(n / 2, m - s);
			x = pi(x.first, n / 2 + x.second);
			return x;
		}
		else if(m < 3 * s){
			auto x = rec(n / 2, m - 2 * s);
			x = pi(x.first + n / 2, x.second + n / 2);
			return x;
		}
		else{
			auto x = rec(n / 2, 4 * s - 1 - m);
			x = pi(n - 1 - x.second, x.first);
			return x;
		}
	}
}

int main(){
	int n, m;
	cin >> n >> m;
	int x, y;
	tie(x, y) = rec(n, m - 1);
	cout << x + 1 << " " << y + 1 << endl;
}
