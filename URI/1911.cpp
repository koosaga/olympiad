// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1911
#include <iostream>
#include <string>
#include <map>
using namespace std;
int meudiff(string a,string b){
	int retorna = 0;
	for(int i=0;i<a.size();i++){
		retorna += int(a[i] != b[i]);
	}
	return retorna;
}
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	int n,m;
	while(cin >> n && n){
		map<string,string> mapa;
		while(n--){
			string s1,s2;
			cin >> s1 >> s2;
			mapa[s1] = s2;
		}
		cin >> m;
		int resp = m;
		while(m--){
			string s1,s2;
			cin >> s1 >> s2;
			if(meudiff(mapa[s1],s2) <= 1){
				resp--;
			}
		}
		cout << resp << endl;
	}
	return 0;
}
