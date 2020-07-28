// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci07c6p5
#include <bits/stdc++.h>

using namespace std;
const int MAXN = 1e5 + 10;

map<int,int> AD,BC;
set<int> cjt1[MAXN],cjt2[MAXN];
int N,K,pos_x,pos_y;
string S;

int get_id_ad(int y){
	if(!AD.count(y)){
		AD[y] = AD.size();
	}
	return AD[y];
}

int get_id_bc(int y){
	if(!BC.count(y)){
		BC[y] = BC.size();
	}
	return BC[y];
}

int main(){
	cin.tie(0);ios_base::sync_with_stdio(0);
	cin >> N >> K;
	cin >> S;
	for(int i = 1;i<=N;i++){
		int x,y;
		cin >> x >> y;
		if(i == 1) pos_x = x, pos_y = y;
		cjt1[get_id_ad(y - x)].insert(x);
		cjt2[get_id_bc(y + x)].insert(x);
	}
	for(int vez = 0;vez<K;vez++){
		if(S[vez] == 'A'){
			int id = get_id_ad(pos_y - pos_x);
			set<int>::iterator it = cjt1[id].lower_bound(pos_x);
			if(next(it) == cjt1[id].end()) continue;
			it = next(it);
			int delta = (*it) - pos_x;
			cjt1[id].erase(pos_x);
			cjt2[get_id_bc(pos_y + pos_x)].erase(pos_x);
			pos_x += delta;
			pos_y += delta;
		}
		else if(S[vez] == 'B'){
			int id = get_id_bc(pos_y + pos_x);
			set<int>::iterator it = cjt2[id].lower_bound(pos_x);
			if(next(it) == cjt2[id].end()) continue;
			it = next(it);
			int delta = (*it) - pos_x;
			cjt2[id].erase(pos_x);
			cjt1[get_id_ad(pos_y - pos_x)].erase(pos_x);
			pos_x += delta;
			pos_y -= delta;
		}
		else if(S[vez] == 'C'){
			int id = get_id_bc(pos_y + pos_x);
			set<int>::iterator it = cjt2[id].lower_bound(pos_x);
			if(it == cjt2[id].begin()) continue;
			it = prev(it);
			int delta = (*it) - pos_x;
			cjt2[id].erase(pos_x);
			cjt1[get_id_ad(pos_y - pos_x)].erase(pos_x);
			pos_x += delta;
			pos_y -= delta;
		}
		else{
			int id = get_id_ad(pos_y - pos_x);
			set<int>::iterator it = cjt1[id].lower_bound(pos_x);
			if(it == cjt1[id].begin()) continue;
			it = prev(it);
			int delta = (*it) - pos_x;
			cjt1[id].erase(pos_x);
			cjt2[get_id_bc(pos_y + pos_x)].erase(pos_x);
			pos_x += delta;
			pos_y += delta;
		}
	}
	cout << pos_x << " " << pos_y << endl;
	return 0;
}