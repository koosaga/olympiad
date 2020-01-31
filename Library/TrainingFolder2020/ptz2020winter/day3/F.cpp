#include<bits/stdc++.h>
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
using namespace std;
using lint = long long;
using pi = pair<int, int>;
const int MAXN = 300005;

int n, a, b;

int main(){
	scanf("%d %d %d",&n,&a,&b);
	priority_queue<int, vector<int>, greater<int>> pq;
	lint sum = 1, nsum = 0;
	for(int i=0; i<n; i++){
		int x; scanf("%d",&x);
		x--;
		int T = (b <= a ? 0 : ((x % b) / a));
		int diff_not = x / b + 1;
		int diff_use = (x - a * T) / b - (T + 1);
		sum += diff_not;
		nsum += diff_use - diff_not;
		pq.push(diff_use - diff_not);
		if(sz(pq) && sum + nsum < 0){
			nsum -= pq.top();
			pq.pop();
		}
	}
	cout << sz(pq) << endl;
}
