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
 
int m; 
lint n, t[100005];
string s[100005];
 
lint fcnt[100005], fs[100005];
lint tcnt[100005], ts[100005];
 
int main(){
	cin >> n >> m;
	for(int i=1; i<=m; i++){
		cin >> s[i] >> t[i];
		tcnt[i] = s[i].size();
		fcnt[i] = count(s[i].begin(), s[i].end(), 'F');
		fs[i] = fs[i-1] + t[i] * fcnt[i];
		ts[i] = ts[i-1] + t[i] * tcnt[i];
	}
	if(fs[m] < n){
		puts("-1");
		return 0;
	}
	lint cnt = fs[m] - n, ret = 0;
	for(int i=1; i<=m; i++){
		for(lint j=0; j<t[i]; j+=max(1ll, t[i] - 1)){
			lint lowf = fs[i-1] + j * fcnt[i];
			int tmp = 0;
			for(int k=0; k<s[i].size(); k++){
				if(s[i][k] == 'F'){
					lint mypos = ts[i-1] + j * tcnt[i] + k;
					ret = max(ret, 2 * (lowf - cnt) - mypos);
					lowf++;
				}
			}
		}
	}
	printf("%lld\n", ret);
}