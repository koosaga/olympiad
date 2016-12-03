#include <bits/stdc++.h> 
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;

char inp[7][100] = {
"xxxxx....xxxxxxxxxxxx...xxxxxxxxxxxxxxxxxxxxxxxxxx.....",
"x...x....x....x....xx...xx....x........xx...xx...x..x..",
"x...x....x....x....xx...xx....x........xx...xx...x..x..",
"x...x....xxxxxxxxxxxxxxxxxxxxxxxxxx....xxxxxxxxxxxxxxxx",
"x...x....xx........x....x....xx...x....xx...x....x..x..",
"x...x....xx........x....x....xx...x....xx...x....x..x..",
"xxxxx....xxxxxxxxxxx....xxxxxxxxxxx....xxxxxxxxxxx....."};

char str[8][505];

int getval(int p){
	for(int i=0; i<11; i++){
		bool mat = 1;
		for(int j=0; j<7; j++){
			for(int k=0; k<5; k++){
				if(inp[j][5 * i + k] != str[j][6 * p + k]){
					mat = 0;
					break;
				}
			}
		}
		if(mat) return i;
	}
	assert(0);
}

char ret[7][505];
void setval(int p, int v){
	if(p != -1){
		for(int i=0; i<7; i++){
			ret[i][p] = '.';
		}
	}
	for(int i=0; i<7; i++){
		for(int j=0; j<5; j++){
			ret[i][p+j+1] = inp[i][5*v+j];
		}
	}
}


int main(){
	for(int i=0; i<7; i++){
		cin >> str[i];
	}
	int p = strlen(str[0]);
	vector<int> ps;
	for(int i=0; i<p; i+=6){
		ps.push_back(getval(i/6));
	}
	int a = 0, b = 0, m = 0;
	for(auto &i : ps){
		if(i == 10) m++;
		else if(m == 0) a = a * 10 + i;
		else b = b * 10 + i;
	}
	a += b;
	vector<int> prnt;
	while(a){
		prnt.push_back(a % 10);
		a /= 10;
	}
	p = 0;
	while(!prnt.empty()){
		setval(6 * p - 1, prnt.back());
		prnt.pop_back();
		p++;
	}
	for(int i=0; i<7; i++) cout << ret[i] << endl;
}
