// Ivan Carvalho
// Solution to https://dmoj.ca/problem/bfs17p2
#include <bits/stdc++.h>
using namespace std;
int qtd[6],last,n;
vector<int> perm;
int check(){
	int total = 0;
	last = -1;
	while(true){
		int available = 0;
		//for(int i = 0;i<6;i++) cout << qtd[i] << endl;
		for(int i = 5;i>=0;i--){
			if(i != last) available += qtd[i];
		}
		if(available == 0) break;
		for(int i = 5;i>=0;i--){
			if(i == last) continue;
			if(qtd[i] == 0) continue;
			total++;
			last = i;
			qtd[i]--;
			break;
		}
	}
	return total;
}
int main(){
	cin.tie(0);cout.tie(0);ios_base::sync_with_stdio(0);
	cin >> n;
	for(int i = 1;i<=n;i++){
		string s;
		cin >> s;
		if(s == "red") qtd[0]++;
		if(s == "orange") qtd[1]++;
		if(s == "yellow") qtd[2]++;
		if(s == "green") qtd[3]++;
		if(s == "blue") qtd[4]++;
		if(s == "black") qtd[5]++;
	}
	sort(qtd,qtd+6);
	cout << check() << endl;
	return 0;
}