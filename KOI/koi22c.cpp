#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<int, int>;
#define sz(v) ((int)(v).size())
#define all(v) (v).begin(), (v).end()
const int mod = 1e9 + 7;

struct foo{
	lint X, B;
};

foo promote(lint X, lint A, lint B, lint C, lint K, lint T){
	lint sum = X * (B - A) + (X + 1) * (C - B);
	sum += T * (K - A);
	return (foo){sum / (C - A), A + (C - A) - sum % (C - A)};
}

int main(){
	ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
	int n; cin >> n;
	vector<int> a(n);
	for(int i = 0; i < n; i++) cin >> a[i];
	sort(all(a));
	int M, K; cin >> M >> K;
	int X = a[K - 1];
	int A = lower_bound(all(a), X) - a.begin();
	int B = lower_bound(all(a), X + 1) - a.begin();
	int C = lower_bound(all(a), X + 2) - a.begin();
	// [0, A) [A, B) [B, C) [C, N)
	int cur = 0;
	while(cur < M){
		int bang = M;
		if(A > 0){
			int s = cur, e = M;
			while(s != e){
				int m = (s + e) / 2;
				if(a[A - 1] + m >= promote(X, A, B, C, K, m - cur).X) e = m;
				else s = m + 1;
			}
			bang = min(bang, s);
		}
		if(C < n){
			int s = cur, e = M;
			while(s != e){
				int m = (s + e) / 2;
				if(promote(X, A, B, C, K, m - cur).X + 1 >= a[C]) e = m;
				else s = m + 1;
			}
			bang = min(bang, s);
		}
		assert(cur < bang);
		auto foo = promote(X, A, B, C, K, bang - cur);
		while(A > 0 && a[A - 1] + bang == foo.X) A--;
		B = foo.B;
		while(C < n && a[C] == foo.X + 1) C++; 
		X = foo.X;
		cur = bang;
	}
	for(int i = 0; i < A; i++) a[i] += M;
	for(int i = A; i < B; i++) a[i] = X;
	for(int i = B; i < C; i++) a[i] = X + 1;
	for(auto &x : a) cout << x << " ";
}
