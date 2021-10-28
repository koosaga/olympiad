#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using llf = long double;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()

int main(){
	int n; cin >> n;
	if(n % 2 || n == 2){
		puts("NIE");
		return 0;
	}
	if(n % 4 == 2){
		int k = n / 4;
		printf("0 0\n%d 0\n%d 1\n", n - k, n - k);
		for(int j = k - 1; j >= 0; j--){
			printf("%d 1\n", 2*j+1);
			printf("%d 2\n", 2*j+1);
			printf("%d 2\n", 2*j);
			if(j != 0) printf("%d 1\n", 2*j);
		}
	}
	else if(n > 4){
		int k = n / 4 - 1;
		printf("0 0\n%d 0\n%d 1\n", n - k, n - k);
		for(int j = k - 1; j >= 0; j--){
			printf("%d 1\n", 2*j+2);
			printf("%d 2\n", 2*j+2);
			printf("%d 2\n", 2*j+1);
			printf("%d 1\n", 2*j+1);
		}
		printf("0 1\n");
	}
	else{
		printf("0 0\n2 0\n2 2\n0 2\n");
	}
}
