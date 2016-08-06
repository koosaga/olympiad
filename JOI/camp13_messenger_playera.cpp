#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pi;

static int di, dj, x, it, startj;
void InitA(int T, int X) {
	di = -1, dj = -1, x = X, it = 0;
}

static int go(int x, int y, int d){
	if(d == -1) x--;
	if(d == -2) x++;
	if(d == -3) y--;
	if(d == -4) y++;
	tie(di, dj) = pi(x, y);
	return d;
}

int GameA(int I, int J) {
	//printf("gamea %d %d\n", I, J);
	if(di == -1){
		startj = J;
		if(J > 2){
			return go(I, J, -3);
		}
		else{
			return go(I, J, -4);
		}
	}
	else if(di == I && dj == J){
		if(startj == 1){
			if(J <= 2) return go(I, J, -4);
			else return go(I, J, -3);
		}
		if(startj == 2){
			if(J <= 3) return go(I, J, -4);
			else return go(I, J, -3);
		}
		if(startj == 3){
			if(J >= 2) return go(I, J, -3);
			else return go(I, J, -4);
		}
		if(startj == 4){
			if(J >= 3) return go(I, J, -3);
			else return go(I, J, -4);
		}
		return 0;
	}
	else{
		if(di != I){
			startj = J;
			if(startj == 1){
				if(J <= 2) return go(I, J, -4);
				else return go(I, J, -3);
			}
			if(startj == 2){
				if(J <= 3) return go(I, J, -4);
				else return go(I, J, -3);
			}
			if(startj == 3){
				if(J >= 2) return go(I, J, -3);
				else return go(I, J, -4);
			}
			if(startj == 4){
				if(J >= 3) return go(I, J, -3);
				else return go(I, J, -4);
			}
			return 0;
		}
		//printf("send bit %d\n", ((x >> (it)) % 2));
		it++;
		startj = J;
		if(((x >> (it-1)) % 2) != (I % 2)){
			if(I > 1) return go(I, J, -1);
			else return go(I, J, -2);
		}
		else{
			if(J > 2) return go(I, J, -3);
			return go(I, J, -4);
		}
	}
	return 0;
}
