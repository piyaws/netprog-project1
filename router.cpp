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

/* @Yu: mac address lookup 
	put your code here
*/
string getMAC(string gateway) {
	return "aa:bb:cc:dd:ee:ff";
}

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

	// loop for each line of routes.txt
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

	// 2. PARSING ARP.TXT AND CREATE A MAP TO LOOKUP MAP ADDRESS
	// @Yu: your code here

	// 3. PARSING PDU.TXT AND ROUTE

	// 3.1. Parse pdu.txt

	// 3.2. route
	string source_addr = "1.2.3.4";
	string source_port = "11";
	string dest_addr = "5.6.7.8";
	string dest_addr_bin = "00000101000001100000011100001000";
	string dest_port = "22";
	int ttl = 11;

	/*for (int i = 0 ; i < dest_addr_bin.length(); i++) {
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
	}*/
}