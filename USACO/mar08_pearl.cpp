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

priority_queue<pi> pq;

int main(){
	int n, q;
	scanf("%d %d",&n,&q);
	for(int i=1; i<=q; i++){
		int x;
		scanf("%d",&x);
		if(x) pq.push(pi(x, i));
	}
	while(!pq.empty()){
		pi t1 = pq.top();
		pq.pop();
		pi t2 = pq.top();
		pq.pop();
		printf("%d %d\n",t1.second, t2.second);
		t1.first--;
		t2.first--;
		if(t1.first) pq.push(t1);
		if(t2.first) pq.push(t2);
	}
}