//// aaaaaaaaaaaaaaaaaaaaaaaang seunghyundeeeeeeeeeeeeeeeeee
#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

int n;
char str[1000005];

bool trial(int x){
	int c1 = 0, c2 = 0, c3 = 0, cnt = 0;
	for(int i=n-1; i>=0; i--){
		if(str[i] == 'I' && cnt < x){
			c3++;
			cnt++;
		}
		else if(str[i] == 'O') c2 = min(c2+1, c3);
		else c1 = min(c1+1, c2);
	}
	return c1 >= x;
}

int main(){
	cin >> n >> str;
	int s = 0, e = n/3;
	while(s != e){
		int m = (s+e+1)/2;
		if(trial(m)) s = m;
		else e = m-1;
	}
	cout << s << endl;
}
