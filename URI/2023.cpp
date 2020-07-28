// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/2023
#include <cctype>
#include <iostream>
#include <algorithm>
#include <vector>
#define endl '\n'
using namespace std;
struct crianca{
	string normal, minusculo;
};
bool comp(crianca A , crianca B){
	return A.minusculo < B.minusculo;
}
vector<crianca> vetor;
int n;
int main(){
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	crianca temp;
	while(getline(cin,temp.normal)){
		temp.minusculo = temp.normal;
		for(int j = 0;j < temp.minusculo.size();j++){
			temp.minusculo[j] = tolower(temp.minusculo[j]);
		}
		vetor.push_back(temp);
	}
	sort(vetor.begin(),vetor.end(),comp);
	cout << vetor[vetor.size() - 1].normal << endl;
	return 0;
}
