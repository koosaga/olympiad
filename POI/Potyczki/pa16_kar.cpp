#include <stdio.h>
#include <stdio.h>
#include <algorithm>
#include <bits/stdc++.h>

int arr1[100001];
int arr2[100001];
int arr3[100001];

void f()
{

	memset(arr1, 0, sizeof(arr1));
	memset(arr2, 0, sizeof(arr2));
	memset(arr3, 0, sizeof(arr3));

	int n, m, r, x, y, i;
	char c;
	scanf("%d%d", &n, &m);

	r = n;

	for(i=0;i<m;i++)
	{
		scanf("%d %c%d", &x, &c, &y);
		if(c == '>')
		{
			arr1[x]++;
			arr3[y]++;
		}
		else
		{
			arr2[y] = 1;
		}
	}
	bool u;

	u = 1;
	for(i=1;i<=n;i++)
	{
		if(!arr2[i])
		{
			u=0;
			break;
		}
	}
	if(u)
	{

			printf("LOSS\n");
			return;
	}
	if(n!=1)
    {
	u = 1;
	for(i=1;i<=n;i++)
	{
		if(arr1[i]!=1 || arr3[i]!=1)
		{
			u=0;
			break;
		}
	}
	if(u)
	{

			printf("DRAW\n");
			return;
	}
    }
	for(i=1;i<=n;i++)
	{
		if(!arr1[i])
		{
			printf("DRAW\n");
			return;
		}
	}
for(i=1;i<=n;i++)
	{
		if(arr3[i] == n)
		{
			printf("WIN\n");
			return;
		}
	}
		
			printf("DRAW\n");
			return;

}


int main()
{
	int t, i;
	scanf("%d", &t);
	for(i=0;i<t;i++)
		f();
	return 0;
}
