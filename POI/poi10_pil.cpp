#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n, k;

deque<pi> dq1, dq2;

int main(){
	scanf("%d %d",&k,&n);
	int lp = 0, ret = 0;
	for(int i=1; i<=n; i++){
		int x;
		scanf("%d",&x);
		while(!dq1.empty() && dq1.back().first >= x) dq1.pop_back();
		while(!dq2.empty() && dq2.back().first <= x) dq2.pop_back();
		dq1.push_back(pi(x, i));
		dq2.push_back(pi(x, i));
		while(dq2.front().first - dq1.front().first > k){
			if(dq1.front().second < dq2.front().second){
				lp = dq1.front().second;
				dq1.pop_front();
			}
			else{
				lp = dq2.front().second;
				dq2.pop_front();
			}
		}
		ret = max(ret, i - lp);
	}
	cout << ret;
}
