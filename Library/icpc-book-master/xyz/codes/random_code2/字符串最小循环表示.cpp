#include <cstdio>
#include <cstring>
using namespace std;
int l1, l2, i, k1, k2;
char s1[1000002], s2[1000002];
int Min_represent(char *s, int l){
	int i=0, j=1, k=0, t;
	while (i < l && j < l && k < l){
		t = s[i + k >= l ? i + k - l : i + k] - s[j + k >= l ? j + k - l : j + k];
		if (!t)	k++;
		else{
			if (t > 0)	i = i + k + 1;
			else	j = j + k + 1;
			if (i == j)	j++;
			k = 0;
		}
	}
	return i < j ? i : j;
}
bool Ok(int k1, int k2, int l, bool wr){
	int i, t1, t2;
	for (i = 0; i < l; i++){
		t1 = s1[i + k1 >= l ? i + k1 - l : i + k1];
		t2 = s2[i + k2 >= l ? i + k2 - l : i + k2];
		if (t1 != t2)	return false;
		if (wr)	printf("%c",t1);
	}
	return true;
}
int main()
{
	scanf("%s%s", s1, s2);
	l1 = strlen(s1);
	l2 = strlen(s2);
	if (l1 != l2){
		printf("No\n");
		return 0;
	}
	k1 = Min_represent(s1, l1);
	k2 = Min_represent(s2, l2);
	if (!Ok(k1, k2, l1, 0)){
		printf("No\n");
		return 0;
	}
	printf("Yes\n");
	Ok(k1, k2, l1, 1);
	printf("\n");
	return 0;
}