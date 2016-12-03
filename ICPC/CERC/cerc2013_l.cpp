#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int main(){
	int t;
	cin >> t;
	while(t--){
		int x;
		scanf("%d",&x);
		printf("%d\n", (1<<x) - 1);
	}
}