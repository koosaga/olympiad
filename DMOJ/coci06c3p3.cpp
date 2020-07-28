// Ivan Carvalho
// Solution to https://dmoj.ca/problem/coci06c3p3
#include <cstdio>
int X[1000],Y[1000],existe[1000];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			char c;
			scanf(" %c",&c);
			if('A' <= c && c <= 'Z'){
				existe[c]++;
				X[c] = i;
				Y[c] = j;
			}
		}
	}
	int resp = 0;
	for(char c1 = 'A';c1<='Z';c1++){
		if(!existe[c1]) continue;
		for(char c2 = c1 + 1;c2 <= 'Z';c2++){
			if(!existe[c2]) continue;
			int cofa = Y[c1] - Y[c2];
			int cofb = -(X[c1] - X[c2]);
			int cofc = X[c1]*Y[c2] - X[c2]*Y[c1];
			for(char c3 = c2 + 1;c3 <= 'Z';c3++){
				if(!existe[c3]) continue;
				if(cofa*X[c3] + cofb*Y[c3] + cofc == 0) resp++;
			}
		}
	}
	printf("%d\n",resp);
	return 0;
}