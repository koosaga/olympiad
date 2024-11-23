#include <bits/stdc++.h>
using namespace std;

struct UF {
    int n;
    vector<int> par;
    UF(int _n) : n(_n) {
        for(int i = 0; i < n; i++) par.push_back(i);
    }
    int find(int a){
        if(a != par[a]) par[a] = find(par[a]);
        return par[a];
    }
    bool join(int a, int b){
        a = find(a);
        b = find(b);
        par[a] = b;
        return (a != b);
    }
};

int main(){
	ios_base::sync_with_stdio(false), cin.tie(nullptr);
	int N;
	cin >> N;
	vector<int> A(N), B(N);
	for(int i = 0; i < N; i++){
		cin >> A[i];
	}
	for(int i = 0; i < N; i++){
		cin >> B[i];
	}

	int G = int(1e6) + 10;

	UF uf(G);
	vector<int> extra(G);
	for(int i = 0; i < N; i++){
		if(!uf.join(A[i], B[i])){
			extra[A[i]]++;
		}
	}
	vector<vector<int> > cc(G);
	vector<int> is_extra(G, 0);
	for(int i = 0; i < G; i++){
		cc[uf.find(i)].push_back(i);
		if(extra[i]){
			is_extra[uf.find(i)] = 1;
		}
	}
	int ans = 0;
	for(int i = 0; i < G; i++){
		if(cc[i].size() == 0) continue;
		if(is_extra[i]){
			ans += cc[i].size();
		} else {
			ans += cc[i].size() - 1;
		}
	}
	cout << ans << '\n';

}
