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
  	fin.open("PDU.txt"); // open a file
  	if (!fin.good()) 
    	return 1; // exit if file not found


    // PARSING
    string source_addr, source_port, dest_addr, dest_addr_bin, dest_port;
    int ttl;

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

	    cout << "source_addr = " << source_addr << endl;
	    cout << "dest_addr = " << dest_addr << endl;
	    cout << "source_port = " << source_port << endl;
	    cout << "dest_port = " << dest_port << endl;
	    cout << "dest_addr_bin = " << dest_addr_bin << endl;
	    cout << "ttl = " << ttl << endl;

	    cout << endl;

	    }

	fin.close();

   	return 0;

}