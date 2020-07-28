// Ivan Carvalho
// Solution to https://dmoj.ca/problem/aplusb2
#include <bits/stdc++.h>
using namespace std;
const int MAXN = 1e5 + 10;
typedef vector<int> vi;
char entrada1[MAXN],entrada2[MAXN];
vi soma(vi A,vi B){
	while(A.size() < B.size()) A.push_back(0);
	while(B.size() < A.size()) B.push_back(0);
	vi C;
	C.assign(A.size() + 5,0);
	for(int i = 0;i<A.size();i++){
		C[i] += A[i] + B[i];
	}
	for(int i = 0;i<C.size();i++){
		int t_val = C[i] % 10;
		int passa = (C[i] - t_val)/10;
		if(i + 1 < C.size()){
			C[i] = t_val;
			C[i+1] += passa;
		}
	}
	while(!C.empty() && C.back() == 0) C.pop_back();
	if(C.empty()) C.push_back(0);
	return C;
}
vi subtrai(vi A,vi B){
	while(A.size() < B.size()) A.push_back(0);
	while(B.size() < A.size()) B.push_back(0);
	vi C;
	C.assign(A.size() + 5,0);
	for(int i = 0;i<A.size();i++){
		C[i] += A[i] - B[i];
		if(C[i] < 0){
			C[i] += 10;
			C[i+1] -= 1;
		}
	}
	for(int i = 0;i<C.size();i++){
		int t_val = C[i] % 10;
		int passa = (C[i] - t_val)/10;
		if(i + 1 < C.size()){
			C[i] = t_val;
			C[i+1] += passa;
		}
	}
	while(!C.empty() && C.back() == 0) C.pop_back();
	if(C.empty()) C.push_back(0);
	return C;
}
int main(){
	int TC;
	scanf("%d",&TC);
	while(TC--){
		scanf("%s %s",entrada1,entrada2);
		string s1 = entrada1, s2 = entrada2;
		int flag1 = (s1[0] == '-'), flag2 = (s2[0] == '-');
		vi A,B;
		for(int i =0;i<s1.size();i++){
			if(s1[i] == '-') continue;
			A.push_back(s1[i] - '0');
		}
		for(int i =0;i<s2.size();i++){
			if(s2[i] == '-') continue;
			B.push_back(s2[i] - '0');
		}
		reverse(A.begin(),A.end());
		while(!A.empty() && A.back() == 0) A.pop_back();
		if(A.empty()) A.push_back(0);
		reverse(B.begin(),B.end());
		while(!B.empty() && B.back() == 0) B.pop_back();
		if(B.empty()) B.push_back(0);
		reverse(A.begin(),A.end());
		reverse(B.begin(),B.end());
		if(B.size() > A.size() || (B.size() == A.size() && B > A)){
			swap(A,B);
			swap(flag1,flag2);
		}
		reverse(A.begin(),A.end());
		reverse(B.begin(),B.end());
		if(flag1 == 0 && flag2 == 0){
			vi C = soma(A,B);
			reverse(C.begin(),C.end());
			for(int i = 0;i<C.size();i++) printf("%d",C[i]);
			printf("\n");
		}
		else if(flag1 == 0 && flag2 == 1){
			vi C = subtrai(A,B);
			reverse(C.begin(),C.end());
			for(int i = 0;i<C.size();i++) printf("%d",C[i]);
			printf("\n");
		}
		else if(flag1 == 1 && flag2 == 0){
			vi C = subtrai(A,B);
			reverse(C.begin(),C.end());
			if(C[0] != 0) printf("-");
			for(int i = 0;i<C.size();i++) printf("%d",C[i]);
			printf("\n");
		}
		else{
			vi C = soma(A,B);
			reverse(C.begin(),C.end());
			if(C[0] != 0) printf("-");
			for(int i = 0;i<C.size();i++) printf("%d",C[i]);
			printf("\n");
		}
	}
	return 0;
};
			printf("\n");
		}
	}
	return 0;
}