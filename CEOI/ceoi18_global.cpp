#include <bits/stdc++.h>
using namespace std;
typedef long long lint;
typedef pair<int, int> pi;
const int MAXN = 2005;

int p1[6], p2[6], pt[6][3];
int ans[4];

int main(){
	string s[4];
	map<string, int> mp;
	for(int i=0; i<4; i++){
		cin >> s[i];
		mp[s[i]] = i;
	}
	for(int i=0; i<6; i++){
		string a, b;
		double x, y, z;
		cin >> a >> b >> x >> y >> z;
		p1[i] = mp[a];
		p2[i] = mp[b];
		pt[i][0] = (int)round(1000 * x);
		pt[i][1] = (int)round(1000 * y);
		pt[i][2] = (int)round(1000 * z);
	}
	srand(0x14004);
	int cnt = 0;
	while(clock() < 0.995 * CLOCKS_PER_SEC){
		cnt += 60000;
		for(int it = 0; it < 10000; it++){
			int sc[4] = {}, p[4] = {0, 1, 2, 3};
			for(int j=0; j<6; j++){
				int dice = rand() % 1000;
				if(dice < pt[j][0]) sc[p1[j]] += 3;
				else if(dice < pt[j][0] + pt[j][1]) sc[p1[j]] += 1, sc[p2[j]] += 1;
				else sc[p2[j]] += 3;
			}

			sort(p, p + 4, [&](int x, int y){
				return sc[x] > sc[y];
			});
			if(sc[p[1]] == sc[p[2]]){
				int lop = 1, rip = 2;
				if(sc[p[0]] == sc[p[1]]) lop = 0;
				if(sc[p[2]] == sc[p[3]]) rip = 3;
				int gyesu = (2 - lop) * (12 / (rip - lop + 1));
				for(int j=lop; j<=rip; j++){
					ans[p[j]] += gyesu;
				}
				for(int j=0; j<lop; j++) ans[p[j]] += 12;
			}
			else{
				ans[p[0]] += 12;
				ans[p[1]] += 12;
			}

		}
	}
	for(int i=0; i<4; i++) printf("%.10f\n", 0.5 * ans[i]/cnt);
}
