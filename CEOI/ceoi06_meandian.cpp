#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;
#include "libmean.h"
 
int n, arr[166];
deque<int> Q;
 
void resolve(int a, int b, int c, int d, int e){
	vector<pi> v;
	v.emplace_back(Meandian(a, b, c, d), e);
	v.emplace_back(Meandian(a, b, c, e), d);
	v.emplace_back(Meandian(a, b, d, e), c);
	v.emplace_back(Meandian(a, c, d, e), b);
	v.emplace_back(Meandian(b, c, d, e), a);
	sort(v.begin(), v.end());
	int sum = 0;
	for(int i=1; i<4; i++){
		sum += v[i].first;
	}
	arr[v[2].second] = sum - 2 * v[2].first;
}
 
int main(){
	n = Init();
	memset(arr, -1, sizeof(arr));
	for(int i=0; i<n; i++){
		Q.push_back(i + 1);
	}
	while(Q.size() >= 5){
		resolve(Q[0], Q[1], Q[2], Q[3], Q[4]); 
		vector<int> tmp;
		for(int i=0; i<5; i++){
			if(arr[Q.front()] == -1) tmp.push_back(Q.front());
			Q.pop_front();
		}
		for(auto &i : tmp){
			Q.push_back(i);
		}
	}
	Solution(arr + 1);
}
