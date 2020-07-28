// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1024
#include <cctype>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;
int main(){
	int a,casodavez;
	cin >> a;
	cin.ignore();
	for(casodavez=0;casodavez<a;casodavez++){
		string texto;
		getline(cin,texto);
		int tamanho=texto.size(),i;
		for(i=0;i<tamanho;i++){
			char davez = texto[i];
			if (isalpha(davez)) texto[i] = davez + 3;
		}
		reverse(texto.begin(),texto.end());
		for(i=tamanho/2;i<tamanho;i++){
			texto[i] = texto[i] - 1;
		}
		cout << texto << endl;
	}
	return 0;
}
