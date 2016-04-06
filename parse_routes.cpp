#include <iostream>
using std::cout;
using std::endl;

#include <fstream>
using std::ifstream;

#include <sstream>
#include <string>
using std::string;
using std::istringstream;

#include <cstdint>
#include <bitset>
using std::bitset;

const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const char* const DELIMITER = " /";

int main() {
	// create a file-reading object
  	ifstream fin;
  	fin.open("routes1.txt"); // open a file
  	if (!fin.good()) 
    	return 1; // exit if file not found


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

	    cout << "destination = " << destination << endl;
	    cout << "cidr = " << cidr << endl;
	    cout << "gateway = " << gateway << endl;
	    cout << "interface = " << interface << endl;
	    
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
	    
	    cout << "IP address of the destination in binary: " << ip_addr_in_bit << endl;
	    cout << endl;

	}

	fin.close();

   	return 0;

}