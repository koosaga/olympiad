// Ivan Carvalho
// Solution to https://www.spoj.com/problems/MATSUM/
#include <iostream>
#include <string>
#include <cstring>
#define MAXN 1037
#define LSOne(S) (S & (-S))
#define endl '\n'
int bit[MAXN][MAXN],a[MAXN][MAXN];
using namespace std;
void update(int r, int c, int val){
	for (int i = r; i <= MAXN; i += i & -i)
		for (int j = c; j <= MAXN; j += j & -j)
			bit[i][j] += val;
}
int sum(int r, int c){
	int s = 0;
	for (int i = r; i > 0; i &= i - 1)
		for (int j = c; j > 0; j &= j - 1)
			s += bit[i][j];
	return s;
}
int main(){
	cin.tie(0);
	ios_base::sync_with_stdio(0);
	int casos;
	cin >> casos;
	string atualizar = "SET", somar = "SUM", fim = "END";
	while(casos--){
		memset(a,0,sizeof(a));
		memset(bit,0,sizeof(bit));
		string op;
		int dummy;
		cin >> dummy;
		while(cin >> op){
			if (op == fim) break;
			//cout << op << endl;
			if (op == atualizar){
				//cout << "Atualizar" << endl;
				int x,y,num;
				cin >> x >> y >> num;
				x++;
				y++;
				update(x,y,num - a[x][y]);
				a[x][y] = num;
			}
			else{
				int x1,y1,x2,y2;
				cin >> x1 >> y1 >> x2 >> y2;
				x1++;
				y1++;
				x2++;
				y2++;
				cout << sum(x2,y2) + sum(x1-1,y1-1) - sum(x2,y1-1) - sum(x1-1,y2) << endl;
			}
		}
		cout << endl;
	}
	return 0;
}