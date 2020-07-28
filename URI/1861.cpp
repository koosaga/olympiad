// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1861
#include <iostream>
#include <map>
#include <set>
#include <string>
#define endl '\n'
using namespace std;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << "HALL OF MURDERERS" << endl;
	string s1,s2;
	set<string> mortos;
	map<string,int> quantosmatou;
	while(cin >> s1 >> s2){
		if(quantosmatou.count(s1)){
			quantosmatou[s1]++;
			mortos.insert(s2);
		}
		else{
			quantosmatou[s1] = 1;
			mortos.insert(s2);
		}
	}
	for(auto it = quantosmatou.begin();it != quantosmatou.end();it++){
		if(!mortos.count((*it).first)){
			cout << (*it).first << " " << (*it).second << endl;
		}
	}
	return 0;
}
