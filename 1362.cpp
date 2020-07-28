// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1362
#include <iostream>
#include <vector>
#include <map>
#define MAXN 31
#define endl '\n'
using namespace std;
int capacidade,n,TC;
map<string,int> conversao;
vector<int> grafo[MAXN],vis;
vector< vector<int> > match;
int augmenting_path(int l){
	if(vis[l]) return 0;
	vis[l] = 1;
	for(int i=0;i<grafo[l].size();i++){
		int r = grafo[l][i];
		if(match[r].size() < capacidade){
			match[r].push_back(l);
			return 1;
		}
		for(int j = 0; j < match[r].size();j++){
			int k = match[r][j];
			if(augmenting_path(k)){
				match[r][j] = l;
				return 1;
			}
		}
	}
	return 0;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin >> TC;
	conversao["XXL"] = 31;
	conversao["XL"] = 32;
	conversao["L"] = 33;
	conversao["M"] = 34;
	conversao["S"] = 35;
	conversao["XS"] = 36;
	while(TC--){
		cin >> capacidade >> n;
		capacidade = capacidade / 6;
		for(int i=1;i<=n;i++){
			string a,b;
			cin >> a >> b;
			grafo[i].clear();
			grafo[i].push_back(conversao[a]);
			grafo[i].push_back(conversao[b]);
		}
		vector<int> temp;
		match.assign(40,temp);
		int resp = 0;
		for(int i=1;i<=n;i++){
			vis.assign(40,0);
			resp += augmenting_path(i);
		}
		if(resp == n) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}
