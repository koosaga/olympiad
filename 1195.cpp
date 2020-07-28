// Ivan Carvalho
// Solution to https://www.urionlinejudge.com.br/judge/problems/view/1195
#include <cstdio>
#include <cstdlib>
#include <queue>
using namespace std;
struct node{
	int key;
	struct node *left, *right;
};
struct node *newNode(int item){
	struct node *temp = new node;
	temp->key = item;
	temp->left = temp->right = NULL;
	return temp;
}
struct node* insert(struct node* node, int key){
	if (node == NULL) return newNode(key);
	if (key < node-> key) node->left = insert(node->left, key);
	else if (key > node->key) node->right = insert(node->right, key);
	return node;
}
void prefixa(node *root){
	if (root != NULL){
		printf(" %d",root->key);
		prefixa(root->left);
		prefixa(root->right);
	}
}
void posfixa(node *root){
	if (root != NULL){
		posfixa(root->left);
		posfixa(root->right);
		printf(" %d",root->key);
	}
}
int main(){
	int casos;
	scanf("%d",&casos);
	for(int caso = 1;caso <= casos;caso++){
		int n;
		scanf("%d",&n);
		priority_queue<int, vector<int>, greater<int> > infixa;
		struct node *raiz = NULL;
		int davez;
		scanf("%d",&davez);
		raiz = insert(raiz,davez);
		infixa.push(davez);
		for(int i=1;i<n;i++){
			scanf("%d",&davez);
			insert(raiz,davez);
			infixa.push(davez);
		}
		printf("Case %d:",caso);
		printf("\nPre.:");
		prefixa(raiz);
		printf("\nIn..:");
		while(!infixa.empty()){
			printf(" %d",infixa.top());
			infixa.pop();
		}
		printf("\nPost:");
		posfixa(raiz);
		printf("\n\n");
	}
	return 0;
}
