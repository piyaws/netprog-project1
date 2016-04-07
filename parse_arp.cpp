#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdint>
#include <bitset>
using namespace std;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " /";

int main() {
	// create a file-reading object
  	ifstream fin;
  	fin.open("arp.txt"); // open a file
  	if (!fin.good()) 
    	return 1; // exit if file not found


    // PARSING
    string ip_addr, eth_addr;

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

	    cout << "ip_addr = " << ip_addr << endl;
	    cout << "eth_addr = " << eth_addr << endl;

	    map<string,string> arp_map;
	    arp_map.insert ( pair<string,string>(ip_addr,eth_addr) );

	    // showing contents:
	  	cout << "arp_map contains:\n";
	  	map<string,string>::iterator it = arp_map.begin();
	  	for (it=arp_map.begin(); it!=arp_map.end(); ++it)
	    	cout << it->first << " => " << it->second << endl;

	    cout << endl;

	}

	fin.close();

   	return 0;
}