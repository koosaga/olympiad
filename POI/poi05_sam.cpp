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

int n, k, q;
vector<int> lis[100005];
int a[500005], cur[100005];

int getnxt(int pos, int cur){
	auto t = upper_bound(lis[pos].begin(), lis[pos].end(), cur);
	if(t == lis[pos].end()) return 1e9;
	return *t;
}

int main(){
	cin >> n >> k >> q;
	for(int i=1; i<=q; i++){
		scanf("%d",&a[i]);
		lis[a[i]].push_back(i);
	}
	set<pi> s;
	int ret = 0;
	for(int i=1; i<=q; i++){
		if(cur[a[i]]){
			s.erase(pi(i, a[i]));
			s.insert(pi(getnxt(a[i], i), a[i]));
		}
		else{
			if(s.size() == k){
				auto t = *s.rbegin();
				cur[t.second] = 0;
				s.erase(--s.end());
			}
			ret++;
			s.insert(pi(getnxt(a[i], i), a[i]));
			cur[a[i]] = 1;
		}
	}
	cout << ret;
}

