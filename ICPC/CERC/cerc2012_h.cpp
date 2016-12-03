#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int get(int x){
	for(int i=1; i<=10; i++){
		if(i * i * 400 >= x){
			return 11 - i;
		}
	}
	return 0;
}

int main(){
	int t;
	cin >> t;
	while(t--){
		int n;
		scanf("%d",&n);
		int ret = 0;
		for(int i=0; i<n; i++){
			int x, y;
			scanf("%d %d",&x,&y);
			ret += get(x*x+y*y);
		}
		printf("%d\n",ret);
	}
}