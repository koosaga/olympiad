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

int n, a[100005], ind[100005];

int main(){
	int t;
	scanf("%d",&t);
	while(t--){
		scanf("%d",&n);
		fill(ind, ind + n + 1, 0);
		for(int i=1; i<=n; i++){
			scanf("%d",&a[i]);
			ind[a[i]]++;
		}
		queue<int> q;
		for(int i=1; i<=n; i++){
			if(ind[i] == 0){
				q.push(i);
			}
		}
		int r = 0;
		while(!q.empty()){
			int x = q.front();
			q.pop();
			r++;
			ind[a[x]]--;
			if(ind[a[x]] == 0){
				q.push(a[x]);
			}
		}
		cout << r << endl;
	}
}