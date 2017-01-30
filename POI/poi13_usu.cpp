#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#include <iostream>
#include <functional>
#include <numeric>
#include <algorithm>
#include <stack>
#include <queue>
#include <deque>
#include <vector>
#include <string>
#include <bitset>
#include <map>
#include <set>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, k;
char str[1000005];

int pos[1000005], stk[1000005], pnt;
vector<vector<int> > dap;

int main(){
	cin >> n >> k >> str;
	for(int i=0; i<n; i++){
		pnt++;
		pos[pnt] = i+1;
		stk[pnt] = stk[pnt-1] + (str[i] == 'b' ? 1 : -1);
		if(pnt-k-1 >= 0 && stk[pnt] - stk[pnt-k-1] == k-1){
			vector<int> v;
			for(int j=pnt-k; j<=pnt; j++){
				v.push_back(pos[j]);
			}
			pnt -= k+1;
			dap.push_back(v);
		}
	}
	reverse(dap.begin(), dap.end());
	for(auto &i : dap){
		for(auto &j : i){
			printf("%d ", j);
		}
		puts("");
	}
}
