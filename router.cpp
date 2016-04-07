#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include <typeinfo>

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " /";

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

	// reading routes.txt
  	ifstream fin;
  	fin.open("routes.txt");
  	if (!fin.good())
    	return 1;

    // PARSING destination cidr gateway interface
    string destination, cidr, gateway, interface;

	// read each line of the file
  	while (!fin.eof()) {
    	// read an entire line into memory
	    char buf[MAX_CHARS_PER_LINE];
	    fin.getline(buf, MAX_CHARS_PER_LINE);

	    // parse the line into blank-delimited tokens
	    int n = 0; // a for-loop index

	    // array to store memory addresses of the tokens in buf
	    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0

	    // parse the line
	    token[0] = strtok(buf, DELIMITER); // first token
	    if (token[0]) { // zero if line is blank
	      	for (n = 1; n < MAX_TOKENS_PER_LINE; n++) {
	        	token[n] = strtok(0, DELIMITER); // subsequent tokens
	        	if (!token[n]) break; // no more tokens
	      	}
	    }

	    destination = token[0];
	    cidr = token[1];
	    gateway = token[2];
	    interface = token[3];

	    int bit;
	    char *pch;
	    string ip_addr_in_bit = "";
	    pch = strtok((char*)token[0],".");
	    while (pch != NULL) {
	    	//cout << pch << endl;
	    	bit = atoi(pch);
	    	bitset<8> bin(bit);
	    	ip_addr_in_bit += bin.to_string();

	    	pch = strtok(NULL,".");
	    }

	    /*cout << "IP address of the destination in binary: " << ip_addr_in_bit << endl;
	    cout << "destination = " << destination << endl;
	    cout << "cidr = " << cidr << endl;
	    cout << "gateway = " << gateway << endl;
	    cout << "interface = " << interface << endl;*/

		int cidr = 7;
		cur = root;

		// loop for each line of routes.txt
		for (int i = 0 ; i < cidr; i++) {
	        if (ip_addr_in_bit[i] == '0') {
	        	if (cur->left == NULL) {
	        		cur->left = (struct node*) malloc( sizeof( struct node ) );
	        		cur->left->left = NULL;
                    cur->left->right = NULL;
	        	}
				cur = cur->left;
	        }
	        else {
	        	if (cur->right == NULL) {
	        		cur->right = (struct node*) malloc( sizeof( struct node ) );
	        		cur->right->left = NULL;
                    cur->right->right = NULL;
	        	}
	        	cur = cur->right;
	        }
		}

		cur->gateway = new string(gateway);
		cur->interface = new string(interface);
		cur = root;
        cout << "Done for this entry" << endl;
	}
	fin.close();

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
