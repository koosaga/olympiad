#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using real_t = long double;
using pi = pair<int, int>;

real_t Tf, Vf, Hf;
real_t Td, Vd, Hd;

real_t joobjoob(){
	real_t frisbee_run = sqrt(2 * Hf);
	real_t distance = frisbee_run * Vf;
	return max(frisbee_run + Tf, distance / Vd + Td) + distance / Vd;
}

bool trial(real_t x){
	real_t alloc_for_dog = min(x - Td, sqrt(2.0 * Hd / 3.0));
	real_t can_run = sqrt(6 * Hd) * alloc_for_dog - 1.5 * (alloc_for_dog * alloc_for_dog);
	real_t alloc_for_frisbee = min(x - Tf, sqrt(2 * Hf));
	real_t frisbee_pos = Hf - 0.5 * alloc_for_frisbee * alloc_for_frisbee;
	return can_run >= frisbee_pos;
}

real_t get_pos(real_t x){
	return (x - Tf) * Vf;
}

int main(){
	cin >> Tf >> Vf >> Hf;
	cin >> Td >> Vd >> Hd;
	if((int)round(Vf) >= (int)round(Vd)){
		printf("%.10Lf\n", joobjoob());
		return 0;
	}
	real_t minimum_meet = (Tf * Vf - Td * Vd) / (Vf - Vd);
	real_t maximum_meet = sqrt(2 * Hf) + Tf;
	if(minimum_meet > maximum_meet){
		printf("%.10Lf\n", joobjoob());
		return 0;
	}
	real_t s = minimum_meet;
	real_t e = maximum_meet;
	for(int i=0; i<100; i++){
		real_t m = (s + e) / 2;
		if(trial(m)) e = m;
		else s = m;
	}
	printf("%.10Lf\n", s + get_pos(s) / Vd);
}
