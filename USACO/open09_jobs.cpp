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

int n;
pi a[100005];
priority_queue<int> pq;

int main(){
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first,&a[i].second);
	}
	sort(a,a+n);
	int cnt = 0, e = n-1;
	int lst = a[n-1].first;
	lint ret = 0;
	for(int i=n-1; i>=0; ){
		cnt = lst - a[i].first;
		lst = a[i].first;
		while(!pq.empty() && cnt){
			ret += pq.top();
			pq.pop();
			cnt--;
		}
		while(e >= 0 && a[i].first == a[e].first){
			pq.push(a[e--].second);
		}
		i = e;
	}
	cnt = lst;
	while(!pq.empty() && cnt){
		ret += pq.top();
		pq.pop();
		cnt--;
	}
	printf("%lld",ret);
}