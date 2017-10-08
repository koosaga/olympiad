#include <cstdio>
#include <algorithm>
using namespace std;

int n, k, a[1000005];

bool trial(int x){
	int stack = 0;
	int cnt = n;
	int pos = 0;
	while(pos < 2 * n * k){
		if(cnt && a[pos+1] - a[pos] <= x){
			cnt--;
			stack += 2 * k - 2;
			pos += 2;
		}
		else{
			stack--;
			if(stack < 0) return 0;
			pos++;
		}
	}
	return stack >= 0;
}

int main(){
	scanf("%d %d",&n,&k);
	for(int i=0; i<2*n*k; i++){
		scanf("%d",&a[i]);
	}
	sort(a,a+2*n*k);
	int s = 0, e = 1e9;
	while(s != e){
		int m = (s+e)/2;
		if(trial(m)) e = m;
		else s = m+1;
	}
	printf("%d",s);
}