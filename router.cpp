#include <iostream>
#include <string.h>   
#include <stdlib.h> 

using namespace std;

struct node
{
  string *gateway;
  string *interface;
  struct node *left;
  struct node *right;
};

int main() {
	
	// 1. BUILDING THE BINARY TREE FOR THE ROUTING

	struct node *root; // root of our tree
	root = (struct node*) malloc( sizeof( struct node ) );
	struct node *cur; // use to traverse

	string address_binary = "00110001001000010001000101100001";
	int cidr = 7;
	string gateway = "1.2.3.4";
	string interface = "eth1";
	cur = root;

	for (int i = 0 ; i < cidr; i++) {
        if (address_binary[i] == '0') {
        	if (cur->left == NULL) {
        		cur->left = (struct node*) malloc( sizeof( struct node ) );
        	}
    		cout << "Go left" << endl;
			cur = cur->left;
        }
        else {
        	if (cur->right == NULL) {
        		cur->right = (struct node*) malloc( sizeof( struct node ) );
        	}
        	cout << "Go right" << endl;
        	cur = cur->right;
        }
	}
	if (cur == NULL) {
		cur = (struct node*) malloc( sizeof( struct node ) );
	}
	cur->gateway = new string(gateway);
	cur->interface = new string(interface);
	cur = root;
	cout << "our main source code file" << endl;
}

/* Fill BST with empty node at current height
void fill_tree(struct node *root, int height){
	count++;
	if (count%10000 == 0) {
		cout << count << endl;
	}
	if (height == 32) return;
	root->left = (struct node*) malloc( sizeof( struct node ) );
	root->right = (struct node*) malloc( sizeof( struct node ) );
	fill_tree(root->left, height +1);
	fill_tree(root->right, height+1);
}*/