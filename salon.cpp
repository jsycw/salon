#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<time.h>

int totalData = 0;

struct Node{
	char name[30];
	int price;
	char care[30];
	char avail[30];
	
	int height, bf;
	Node *left, *right;
};

Node *createNewNode(const char*name, int price, const char *care, const char *avail){
	Node *newNode = (Node*)malloc(sizeof(Node));
	
	strcpy(newNode->name, name);
	newNode->price = price;
	strcpy(newNode->care, care);
	strcpy(newNode->avail, avail);
	
	newNode->height = 1;
	newNode->bf = 0;
	newNode->left = newNode->right = NULL;
	
	return newNode;
}

int getHeight(Node *root){
	if(root==NULL) return 0;
	else return root->height;
}


int maxHeight(int a, int b){
	return (a>b) ? a:b;
}

int computeNewHeight(Node *root){
	return maxHeight(getHeight(root->left), getHeight(root->right)) + 1;
}

Node *updateNode(Node *root){
	root->height = computeNewHeight(root);
	root->bf = getHeight(root->left) - getHeight(root->right);
	
	return root;
}

Node *leftRotate(Node *root){
	Node *pivot = root->right;
	Node *temp = pivot->left;
	
	pivot->left = root;
	root->right = temp;
	
	root = updateNode(root);
	pivot = updateNode(pivot);
	
	return pivot;
}

Node *rightRotate(Node *root){
	Node *pivot = root->left;
	Node *temp = pivot->right;
	
	pivot->right = root;
	root->left = temp;
	
	root = updateNode(root);
	pivot = updateNode(pivot);
	
	return pivot;
}

Node *rotation(Node *root){
	if(root->bf < -1 && root->right->bf < 0){
		return leftRotate(root);
	} else if(root->bf < -1 && root->right->bf < 0){
		root->right = rightRotate(root->right);
		return leftRotate(root);
	} else if(root->bf > 1 && root->left->bf > 0){
		return rightRotate(root);
	} else if(root->bf > 1 && root->left->bf < 0){
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	return root;
}

Node *insert(Node *root, const char*name, int price, const char *care, const char *avail){
	if(root==NULL){
		return createNewNode(name, price, care, avail);
	} else if(strcmp(name, root->name) < 0){
		root->left = insert(root->left, name, price, care, avail);
	} else if(strcmp(name, root->name) > 0){
		root->right = insert(root->right, name, price, care, avail);
	}
	return rotation(updateNode(root));
}

Node *predecessor(Node *root){
	Node *temp = root;
	
	if(temp && temp->right != 0){
		temp = temp->right;
	}
	return temp;
}

Node *del(Node *root, const char *name){
	if(root==NULL){
		printf("Data not found\n");
		printf("Press enter to continue ...");
		return NULL;
	} else if(strcmp(name, root->name) < 0){
		root->left = del(root->left, name);
	} else if(strcmp(name, root->name) > 0){
		root->right = del(root->right, name);
	} else{
		if(root->left==NULL && root->right==NULL){
			free(root);
			root=NULL;
			printf("[Delete sucessfully]\n");
			printf("Press enter to continue ...");
			return root;
		} else if(!root->left || !root->right){
			Node *temp = (!root->left) ? root->right : root->left;
			free(root);
			printf("[Delete sucessfully]\n");
			printf("Press enter to continue ...");
			return temp;
		} else{
			Node *temp = predecessor(root->left);
			strcpy(root->name, temp->name);
			root->left = del(root->left, temp->name);
			printf("[Delete sucessfully]\n");
			printf("Press enter to continue ...");
		}
	}
}

void preOrder(Node *root){
	if(root==NULL){
		return;
	}
	
	printf("||%-20s||%-12s||%-9d||%-21s||\n", root->name, root->care, root->price, root->avail);
	preOrder(root->left);
	preOrder(root->right);
}

void inOrder(Node *root){
	if(root==NULL){
		return;
	}
	
	inOrder(root->left);
	printf("||%-20s||%-12s||%-9d||%-21s||\n", root->name, root->care, root->price, root->avail);
	inOrder(root->right);
}

void postOrder(Node *root){
	if(root==NULL){
		return;
	}
	
	postOrder(root->left);
	postOrder(root->right);
	printf("||%-20s||%-12s||%-9d||%-21s||\n", root->name, root->care, root->price, root->avail);
}

int main(){
	Node *root = NULL;
	srand(time(NULL));
	int opt, len;
	
	do{
		system("cls");
		puts("Sally Salon");
		puts("===========");
		puts("Menu: ");
		puts("1. View Available Treatment");
		puts("2. Insert New Treatment");
		puts("3. Delete Treatment");
		puts("4. Exit");
		puts("[1-4]");
		printf(">> ");
	
		scanf("%d", &opt); getchar();
		
		switch(opt){
			case 1:{
				char view[10];
				if(totalData == 0){
					puts("no data");
					puts("Press enter to continue...");
				} else{
					do{
						printf("Input view order [pre | in | post]: ");
						scanf("%[^\n]", view); getchar();
					} while(!(strcmp(view, "pre") == 0 || strcmp(view, "in") == 0 || strcmp(view, "post") == 0));
					
					puts("========================================================================");
					puts("|| Treatment          || Category   || Price   || Home Service        ||");
					puts("========================================================================");
					
					if(strcmp(view, "pre") == 0){
						preOrder(root);
					} else if(strcmp(view, "in") == 0){
						inOrder(root);
					} else if(strcmp(view, "post") == 0){
						postOrder(root);
					}
					puts("========================================================================");	
					puts("");
				}
				break;
			}
			case 2:{
				puts("INSERT NEW TREATMENT");
				
				char treatment[30];
				do{
					printf("Input new treatment name: ");
					scanf("%[^\n]", treatment); getchar();
					
					len = strlen(treatment);
				} while(!(tolower(treatment[0]) == 's' && tolower(treatment[1]) == 'a' && tolower(treatment[2]) == 'l' && tolower(treatment[3]) == 'l' && tolower(treatment[4]) == 'y' && treatment[5] == ' ' && len >= 5 && len <= 20));
				
				int harga;
				do{
					printf("Input treatment price: ");
					scanf("%d", &harga); getchar();
				} while(!(harga>=50000 && harga <=1000000));
				
				char category[30];
				do{
					printf("Input treatment category [Hair Care | Nail Care | Body Care]: ");
					scanf("%[^\n]", category); getchar();
				} while(!(strcmp(category, "Hair Care") == 0 || strcmp(category, "Nail Care") == 0 || strcmp(category, "Body Care") == 0 ));
				
				char service[30];
				do{
					printf("Input treatment availability for home service [Available | Unavailable]: ");
					scanf("%[^\n]", service); getchar();
				} while(!(strcmp(service, "Available") == 0 || strcmp(service, "Unvailable") == 0));
				
				root = insert(root, treatment, harga, category, service);
				puts("[New treatment is successfully inserted!]");
				puts("Press enter to continue...");
				
				totalData++;
				break;
			}
			case 3:{
				if(totalData == 0){
					puts("no data");
					puts("Press enter to continue...");
				} else{
					char hapus[30];
					puts("========================================================================");
					puts("||     Treatment      ||  Category  ||  Price  ||     Home Service    ||");
					puts("========================================================================");
					inOrder(root);
					puts("========================================================================");
					
					puts("DELETE TREATMENT");
					printf("Input treatment name to be deleted: ");
					scanf("%[^\n]", hapus); getchar();
					
					root = del(root, hapus);
					totalData--;	
				}
				break;
			}
			case 4:{
				puts("THANK YOU");
				break;
			}
		}
		getchar();
	} while(opt != 4);
	return 0;
}
