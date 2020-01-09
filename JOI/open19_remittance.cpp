#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
const int MAXN = 1000005;

int n;
lint a[MAXN], b[MAXN], f[MAXN];

void my_ass(bool p){
	if(!p){
		puts("No");
		exit(0);
	}
}

int main(){
	scanf("%d",&n);
	vector<lint> need(n);
	for(int i=0; i<n; i++){
		scanf("%lld %lld",&a[i],&b[i]);
		need[i] = b[i] - a[i];
	}
	if(count(need.begin(), need.end(), 0) == n){
		puts("Yes");
		return 0;
	}
	for(int i=0; i<30; i++){
		for(int j=0; j<n; j++){
			if(need[j] & 1){
				f[j] += (1ll << i);
				need[j]--;
				need[(j+n-1)%n] += 2;
			}
		}
		for(int j=0; j<n; j++) need[j] >>= 1;
	}
	lint tot_bal = *min_element(f, f + n);
	int pos = min_element(f, f + n) - f;
	rotate(a, a + pos, a + n);
	rotate(b, b + pos, b + n);
	for(int i=0; i<n; i++) b[i] += tot_bal;
	for(int i=0; i<n; i++){
		lint toSend = a[i] - b[i];
		if(i == n - 1) my_ass(toSend == 0);
		my_ass(toSend >= 0 && toSend % 2 == 0);
		a[i + 1] += toSend / 2;
		a[i] -= toSend;
	}
	bool good = 0;
	for(int i=0; i<n; i++){
		my_ass(a[i] >= tot_bal);
		if(a[i] > tot_bal) good = 1;
	}
	my_ass(good);
	puts("Yes");
}
