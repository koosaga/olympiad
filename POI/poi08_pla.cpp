#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
const int MAXN = 1005;

int n;
stack<int> stk;

int main(){
	int ans = 0;
	scanf("%d",&n);
	for(int i=0; i<n; i++){
		int x;
		scanf("%*d %d",&x);
		while(!stk.empty() && stk.top() > x) stk.pop();
		if(!stk.empty() && stk.top() == x) continue;
		ans++;
		stk.push(x);
	}
	cout << ans;
}
