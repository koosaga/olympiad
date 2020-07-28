// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1251
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#define endl '\n'
#define MP make_pair
using namespace std;
typedef pair<int,int> ii;
int frequencia[300];
int main(){
	bool first= false;
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	string s;
	while(getline(cin,s)){
		priority_queue<ii> heap;
		memset(frequencia,0,sizeof(frequencia));
		if (first) cout << endl;
		else first = true;
		for(int i=0;i<s.size();i++){
			frequencia[(int)s[i]]++;
		}
		for(int i=256;i>=0;i--) if (frequencia[i]){
			heap.push(MP(-frequencia[i],i));
		}
		while(!heap.empty()){
			cout << heap.top().second << " " << -heap.top().first << endl;
			heap.pop();
		}
	}
	return 0;
}
