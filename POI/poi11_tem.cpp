#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;
const int MAXN = 1000005;

int n;
deque<pi> stk;

int main(){
	scanf("%d",&n);
	int ret = 0;
	int keut = -1;
	for(int i=0; i<n; i++){
		int s, e;
		scanf("%d %d",&s,&e);
		while(!stk.empty() && stk.back().first <= s) stk.pop_back();
		while(!stk.empty() && stk.front().first > e){
			keut = stk.front().second;
			stk.pop_front();
		}
		stk.push_back(pi(s, i));
		ret = max(ret, i - keut);
	}
	cout << ret;
}
