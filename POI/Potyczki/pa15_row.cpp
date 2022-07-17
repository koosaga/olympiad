#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int MAXT = 1050005;

lint getsum(lint n){
	lint ret = 0;
	for(lint i = n; i; i /= 10) ret += (i%10) * (i%10);
	return ret;
}
int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	lint k, a, b; cin >> k >> a >> b;
	int ret = 0;
	for(lint i = 1; i <= 2000 && i * k <= b; i++){
		if(i * k >= a && getsum(i * k) == i) ret++;
	}
	cout << ret << "\n";
}
