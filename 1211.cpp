// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1211
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n;
	while(cin >> n){
		vector<string> lista;
		for(int i=0;i<n;i++){
			string davez;
			cin >> davez;
			lista.push_back(davez);
		}
		sort(lista.begin(),lista.end());
		int resp = 0;
		for(int i=1;i<n;i++){
			int retorna = 0,idx=0;
			while(idx < lista[i].size()){
				if(lista[i][idx] == lista[i-1][idx]){
					retorna++;
					idx++;
				}
				else{
					break;
				}
			}
			resp += retorna;
		}
		cout << resp << '\n';
	}
	return 0;
}
