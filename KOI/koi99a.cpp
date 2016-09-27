#include <cstdio>
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;
typedef pair<short,char> pi;
 
char str[105];
int n;
 
char div_point[105][105];
bool vis[105][105];
pi dp[105][105];
 
pi f(int s, int e){
	if(s > e) return pi(0,0);
	if(vis[s][e]) return dp[s][e];
	vis[s][e] = 1;
	short res = 1e5;
	char resh = 0;
	for (int i=s+1; i<=e; i+=2) {
		if(str[s] != str[i]){
			pi x = f(s+1,i-1);
			pi y = f(i+1,e);
			if(res > x.first + y.first + (i - s) + (x.second + 1) * 2){
				res = x.first + y.first + (i - s) + (x.second + 1) * 2;
				resh = (x.second + 1 > y.second ? x.second + 1 : y.second);
				div_point[s][e] = i;
			}
		}
	}
	return dp[s][e] = pi(res,resh);
}
 
void track(int s, int e){
	if(s > e) return;
	int p = div_point[s][e];
	printf("%d %d\n",s+1,p+1);
	track(s+1,p-1);
	track(p+1,e);
}
 
int main(){
	scanf("%d %s",&n,str);
	printf("%hd\n",f(0,n-1).first);
	track(0,n-1);
}