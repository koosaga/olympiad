#include <cstdio>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef pair<long long,int> pi;

long long g(long long x, long long y){return y ? g(y,x%y) : x;}

int n;
long long a[100005];

long long f(int s, int e){
	if(s == e) return a[s];
	int m = (s+e)/2;
	long long ret = max(f(s,m),f(m+1,e));
	vector<pi> left, right;
	left.push_back(pi(a[m],m));
	right.push_back(pi(a[m+1],m+1));
	for (int i=m+2; i<=e; i++) {
		long long gcd = g(right.back().first,a[i]);
		if(gcd == right.back().first){
			right.back().second = i;
		}
		else{
			right.push_back(pi(gcd,i));
		}
	}
	for (int i=m-1; i>=s; i--) {
		long long gcd = g(left.back().first,a[i]);
		if(gcd == left.back().first){
			left.back().second = i;
		}
		else{
			left.push_back(pi(gcd,i));
		}
	}
	for (int i=0; i<left.size(); i++) {
		for (int j=0; j<right.size(); j++) {
			ret = max(ret,g(left[i].first,right[j].first) * (right[j].second - left[i].second + 1));
		}
	}
	return ret;
}

void solve(){
	scanf("%d",&n);
	for (int i=0; i<n; i++) {
		scanf("%lld",&a[i]);
	}
	printf("%lld\n",f(0,n-1));
}

int main(){
	int t;
	scanf("%d",&t);
	while (t--) {
		solve();
	}
}