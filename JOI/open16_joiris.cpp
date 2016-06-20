#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef long double llf;
typedef pair<int, int> pi;

int n, k, a[55];
int sum[55];

int main(){
	cin >> n >> k;
	for(int i=0; i<n; i++){
		cin >> a[i];
		sum[i%k] += a[i];
	}
	for(int i=1; i<n%k; i++){
		if(sum[i-1] % k != sum[i] % k){
			puts("-1");
			return 0;
		}
	}
	for(int i=n%k+1; i<k; i++){
		if(sum[i-1] % k != sum[i] % k){
			puts("-1");
			return 0;
		}
	}
	vector<pi> v;
	for(int i=1; i<n; i++){
		while(a[i-1] > a[i]){
			v.push_back(pi(1, i));
			a[i] += k;
		}
	}
	int b[55] = {};
	for(int i=1; i<n; i++){
		for(int j=a[i-1]; j<a[i]; j++){
			for(int l=i; l>=k; l-=k){
				v.push_back(pi(2, l-k));
			}
			for(int l=0; l<i%k; l++){
				b[l]--;
			}
		}
	}
	for(int i=0; i<n; i++) a[i] = b[i];
	for(int i=0; i<k-1; i++){
		while(a[i] < 0){
			v.push_back(pi(1, i));
			a[i] += k;
		}
	}
	int upmax = *max_element(a+n%k, a+k);
	for(int i=0; i<n; i++){
		while(a[i] < upmax){
			v.push_back(pi(1, i));
			a[i] += k;
		}
	}
	upmax = *max_element(a, a+n%k);
	for(int i=0; i<n%k; i++){
		while(a[i] < upmax){
			v.push_back(pi(1, i));
			a[i] += k;
		}
	}
	for(int i=n%k; i<n; i+=k){
		for(int j=0; j<upmax; j++){
			v.push_back(pi(2, i));
		}
	}
	printf("%d\n",v.size());
	for(auto &i : v){
		printf("%d %d\n", i.first, i.second + 1);
	}
}

