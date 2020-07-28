// Ivan Carvalho
// Solution to https://dmoj.ca/problem/tle17c1p2
#include <bits/stdc++.h>
using namespace std;
typedef pair<int,string> si;
int main(){
	int tipos;
	map<string,int> mapa;
	cin >> tipos;
	for(int i = 0;i < tipos;i++){
		string s;
		int val;
		cin >> s >> val;
		mapa[s] = val;
	}
	int resp = 0, energy = 0,pos = 0,n;
	cin >> n;
	vector<si> vetorzao;
	while(n--){
		string s;
		int e;
		cin >> s >> e;
		vetorzao.push_back(si(e,s));
	}
	sort(vetorzao.begin(),vetorzao.end());
	for(int i = 0;i < vetorzao.size();i++){
		int dist = vetorzao[i].first;
		int val = mapa[vetorzao[i].second];
		if(pos != dist && energy < abs(pos - dist)){
			break;
		}
		energy -= abs(pos - dist);
		resp++;
		pos = dist;
		energy += val;
	}
	cout << resp << endl;
	return 0;
}