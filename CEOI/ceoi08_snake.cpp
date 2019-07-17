#include <bits/stdc++.h>
#include "snakelib.h"
using namespace std;

char a1, a2;

int main(){
	int k = get_speed();
	ask_snake(4040, 8080, &a1, &a2);
	int sl, el, sr, er;
	if(a1 == 'f'){
		tie(sl, el, sr, er) = make_tuple(0, 4040, 0, 4040);
	}
	else if(a1 == 's'){
		tie(sl, el) = make_tuple(0, 4040);
		if(a2 == 's') tie(sr, er) = make_tuple(8080, 12121);
		else tie(sr, er) = make_tuple(4040, 8080);
	}
	else{
		if(a2 == 'f') tie(sl, el, sr, er) = make_tuple(4040, 8080, 4040, 8080);
		else if(a2 == 's') tie(sl, el, sr, er) = make_tuple(4040, 8080, 8080, 12121);
		else tie(sl, el, sr, er) = make_tuple(8080, 12121, 8080, 12121);
	}
	for(int i=0; (er - sr > k || el - sl > k); i++){
		el += k;
		er += k;
		int ml = (sl + el) / 2;
		int mr = (sr + er) / 2;
		ask_snake(ml, mr, &a1, &a2);
		if(a1 == 'b') sl = ml + 1;
		else el = ml;
		if(a2 == 'f') er = mr;
		else sr = mr + 1;
	}
	int est1 = (er - el);
	int est2 = (sr - sl);
	tell_length(max(1, (est1 + est2) / 2));
}
