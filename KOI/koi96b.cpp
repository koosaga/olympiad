#include <cstdio>
#include <algorithm>
#include <utility>
using namespace std;
typedef pair<int,int> pi;
 
int n;
pi a[55];
int dp[101][101];
 
int calc(int start, int end){
	if(start > end) return 0;
	if(dp[start][end]) return dp[start][end];
	int res = 0;
	for (int i=0; i<n; i++) {
		if(start < a[i].first && a[i].second < end){
			res = max(res,1 + calc(start,a[i].first) + calc(a[i].first,a[i].second) + calc(a[i].second,end));
		}
	}
	return dp[start][end] = res;
}
 
int main(){
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		scanf("%d %d",&a[i].first,&a[i].second);
		if(a[i].second < a[i].first) swap(a[i].first,a[i].second);
	}
	printf("%d",calc(0,100));
}