// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1808
#include <iostream>
#include <string>
#include <cstdio> 
#define endl '\n'
using namespace std;
int converter(char davez){
	if (davez == '0') return 9;
	if (davez == '1') return 1;
	if (davez == '2') return 2;
	if (davez == '3') return 3;
	if (davez == '4') return 4;
	if (davez == '5') return 5;
	if (davez == '6') return 6;
	if (davez == '7') return 7;
	if (davez == '8') return 8;
	if (davez == '9') return 9;
	return 0;
}
int main(){
	string s;
	cin >> s;
	int numeros=0, soma=0;
	for(int i=0;i<s.size();i++){
		soma += converter(s[i]);
		if (s[i] != '0') numeros++;
	}
	printf("%.2lf\n",double(soma)/double(numeros));
	return 0;
}
