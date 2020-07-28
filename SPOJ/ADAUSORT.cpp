// Ivan Carvalho
// Solution to https://www.spoj.com/problems/ADAUSORT/
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
const int MAXN = 1e5 + 10;
vector<ii> vetorzao;
int resp[MAXN],N;
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	cin >> N;
	for(int i = 1;i<=N;i++){
		int x;
		cin >> x;
		vetorzao.push_back(ii(x,-i));
	}
	sort(vetorzao.begin(),vetorzao.end());
	for(int i = 0;i<vetorzao.size();i++){
		resp[i+1] = -vetorzao[i].second;
	}
	for(int i = 1;i<=N;i++) cout << resp[i] << " ";
	cout << endl;
	return 0;
}