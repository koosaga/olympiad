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
const int offset = 1e6;
 
int n;
pi a[100005];
vector<int> elem[2000005];
vector<int> ok;
 
int solve(int x){
	int ret = 0;
	for(int i=0; i<elem[x].size(); i++){
		for(int j=0; j<i; j++){
			int dx = elem[x][i] - elem[x][j];
			pi p1 = pi(x + dx, elem[x][i]);
			pi p2 = pi(x + dx, elem[x][j]);
			if(x + dx <= 2000000 && *lower_bound(a, a+n, p1) == p1 && *lower_bound(a, a+n, p2) == p2){
				ret++;
				if(elem[x + dx].size() >= 250) ret++;
			}
			p1 = pi(x - dx, elem[x][i]);
			p2 = pi(x - dx, elem[x][j]);
			if(x - dx >= 0 && *lower_bound(a, a+n, p1) == p1 && *lower_bound(a, a+n, p2) == p2){
				ret++;
				if(elem[x - dx].size() >= 250) ret++;
			}
		}
	}
	return ret;
}
 
int main(){
	scanf("%d",&n);
	a[n] = pi(-1, -1);
	for(int i=0; i<n; i++){
		scanf("%d %d",&a[i].first, &a[i].second);
		a[i].first += offset;
		a[i].second += offset;
	}
	sort(a, a+n);
	for(int i=0; i<n; i++){
		elem[a[i].first].push_back(a[i].second);
	}
	lint ret = 0;
	for(int i=0; i<=2*offset; i++){
		if(elem[i].empty()) continue;
		if(elem[i].size() >= 250) ok.push_back(i);
		else{
			ret += solve(i);
		}
	}
	for(int i=0; i<ok.size(); i++){
		for(int j=0; j<i; j++){
			vector<int> vect;
			int p = 0;
			for(auto &k : elem[ok[i]]){
				while(p < elem[ok[j]].size() && elem[ok[j]][p] < k) p++;
				if(p < elem[ok[j]].size() && elem[ok[j]][p] == k){
					vect.push_back(k);
				}
			}
			p = 0;
			for(auto &k : vect){
				while(p < vect.size() && k - vect[p] > ok[i] - ok[j]) p++;
				if(p < vect.size() && k - vect[p] == ok[i] - ok[j]){
					ret+=2;
				}
			}
		}
	}
	cout << ret/2;
}