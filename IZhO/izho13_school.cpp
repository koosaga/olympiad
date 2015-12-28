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

int n, m, s;
pi a[300005];

struct node{
	int x, y, i;
};

auto func1 = [](const node &a, const node &b){
	if(a.x != b.x) return a.x < b.x;
	return a.y > b.y;
};

auto func2 = [](const node &a, const node &b){
	if(a.y != b.y) return a.y < b.y;
	return a.x > b.x;
};

priority_queue<node, vector<node>, decltype(func1) > pq1 (func1);
priority_queue<node, vector<node>, decltype(func2) > pq2 (func2);
priority_queue<int> lev2;

bool inque[300005];

int main(){
	cin >> n >> m >> s;
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
	}
	sort(a, a+n);
	reverse(a, a+n);
	lint ret = 0;
	for(int i=0; i<m; i++){
		ret += a[i].first;
		lev2.push(a[i].second - a[i].first);
	}
	for(int i=m; i<n; i++){
		inque[i] = 1;
		pq1.push({a[i].first, a[i].second, i});
		pq2.push({a[i].first, a[i].second, i});
	}
	for(int i=0; i<s; i++){
		while(!inque[pq1.top().i]) pq1.pop();
		while(!inque[pq2.top().i]) pq2.pop();
		node p1 = pq1.top(), p2 = pq2.top();
		if(p2.y >= p1.x + lev2.top()){
			ret += p2.y;
			inque[p2.i] = 0;
		}
		else{
			ret += p1.x + lev2.top();
			inque[p1.i] = 0;
			lev2.pop();
			lev2.push(p1.y - p1.x);
		}
		// case 1. get s from empty set
		// case 2. get s from nonempty + get m from empty
	}
	cout<< ret;
}