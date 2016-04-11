#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
#include <typeinfo>
#include <map>

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

/* Lookup physical address from ip address
*/
string getMAC(string gateway, map<string,string>* arp_map) {
    map<string,string>::iterator it = arp_map->begin();
    for (it = arp_map->begin(); it != arp_map->end(); ++it){
        if (it->first == gateway){
            return it->second;
        }
    }
    if (gateway == "0.0.0.0"){
        return "default gateway";
    }
    return "no MAC address found";
}


int main() {

	// 1. BUILDING THE BINARY TREE FOR THE ROUTING

	struct node *root; // root of our tree
	root = (struct node*) malloc( sizeof( struct node ) );
	struct node *cur; // use to traverse
	string *default_gateway;

	// reading routes.txt
  	ifstream fin;
  	fin.open("routes.txt");
  	if (!fin.good())
    	return 1;

    // PARSING destination cidr gateway interface


	// read each line of the file
  	while (!fin.eof()) {
  		string destination, gateway, interface;
    	int cidr;

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
	    cidr = atoi(token[1]);
	    gateway = token[2];
	    interface = token[3];

	    // default gateway
	    if (destination.compare("0.0.0.0") == 0 && cidr == 0) {
	    	default_gateway = new string (gateway);
	    	cout << "default gateway: " << *default_gateway << endl;
	    }

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

	    /* traversing tree */
		cur = root;
		for (int i = 0 ; i < cidr; i++) {
	        if (ip_addr_in_bit[i] == '0') {
	        	if (cur->left == NULL) {
	        		cur->left = (struct node*) malloc( sizeof( struct node ) );
	        		cur->left->left = NULL;
                    cur->left->right = NULL;
                    cur->left->gateway = NULL;
                    cur->left->interface = NULL;
	        	}
				cur = cur->left;
				//cout << "Go left" << endl;
	        }
	        else {
	        	if (cur->right == NULL) {
	        		cur->right = (struct node*) malloc( sizeof( struct node ) );
	        		cur->right->left = NULL;
                    cur->right->right = NULL;
                    cur->right->gateway = NULL;
                    cur->right->interface = NULL;
	        	}
	        	cur = cur->right;
	        	//cout << "Go right" << endl;
	        }
		}

		cur->gateway = new string(gateway);
		cur->interface = new string(interface);
		cur = root;
        //cout << "Done for this entry" << endl;
	}
	fin.close();

	// 2. PARSING ARP.TXT AND CREATE A MAP TO LOOKUP MAP ADDRESS
	// open the file to be parsed
    fin.open("arp.txt"); // open a file
    if (!fin.good()){
        fprintf(stderr, "File not found\n");
        return 1; // exit if file not found
    }

    // PARSING
    string ip_addr, eth_addr;
    map<string,string> arp_map;
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
        
        ip_addr = token[0];
        eth_addr = token[1];

        arp_map.insert ( pair<string,string>(ip_addr,eth_addr) );
        
    }
    fin.close();

	// 3. PARSING PDU.TXT AND ROUTE

	// Parse pdu.txt
	fin.open("PDU.txt"); // open a file
  	if (!fin.good()) 
    	return 1; // exit if file not found
  	while (!fin.eof()) {
		string source_addr, source_port, dest_addr, dest_addr_bin, dest_port;
		int ttl;
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

	    source_addr = token[1];
	    dest_addr = token[2];
	    ttl = atoi(token[4]);
	    source_port = token[5];
	    dest_port = token[6];
	    
	    int bit;
	    char *pch;
	    dest_addr_bin = "";
	    pch = strtok((char*)token[2],".");
	    while (pch != NULL) {
	    	bit = atoi(pch);
	    	bitset<8> bin(bit);
	    	dest_addr_bin += bin.to_string();

	    	pch = strtok(NULL,".");
	    }

	    /*cout << "source_addr = " << source_addr << endl;
	    cout << "dest_addr = " << dest_addr << endl;
	    cout << "source_port = " << source_port << endl;
	    cout << "dest_port = " << dest_port << endl;
	    cout << "dest_addr_bin = " << dest_addr_bin << endl;
	    cout << "ttl = " << ttl << endl;
	    cout << endl;*/

	    cout << source_addr << ":" << source_port << "->" << dest_addr << ":"<<dest_port;
	    if (ttl <= 1) {
	    	cout << " discarded (TTL expired)" << endl;
	    } else {
	    	string *gateway = NULL;
	    	string *interface = NULL;
	    	cur = root;
			for (int i =0 ; i < dest_addr_bin.length(); i++) {
		        if (dest_addr_bin[i] == '0') {
		        	if (cur->left == NULL) {
		        		break;
		        	} else {
		        		cur = cur->left;
		        	}
		        }
		        else {
		        	if (cur->right == NULL) {
		        		break;
		        	} else {
		        		cur = cur->right;
		        	}
		        }
		        if (cur->gateway != NULL) {
		        	gateway = new string (*(cur->gateway));
		        	interface = new string (*(cur->interface));
		        }
			}
			if (gateway == NULL) {
				if (default_gateway == NULL) {
					cout << " destination unreachable, and there is no default gateway!" << endl;
				} else {
					cout << " via " << *default_gateway << " (ppp0) ttl " << ttl-1 << " (No path found, hence using default gateway)" << endl;
				}

			} else if ((*gateway).compare("0.0.0.0") == 0) {
				cout << " directly connected (" << *interface << "-" << *default_gateway << ") ttl " << ttl-1 << endl;
			} 
			else {
				cout << " via " << *gateway << " (" << *interface << "-" << getMAC(*gateway, &arp_map) << ") ttl " << ttl-1 << endl;
			}
	    }

	 }

	fin.close();
}
