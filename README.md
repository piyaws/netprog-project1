PROJECT 1 SUBMISSION

- Student 1: PHAN HUY NGUYEN - 661672819
- Student 2: SAKAWKARN PIYAWITWANICH - 661109013
- Student 3: YU QIAO - 661058508

1. SUBMISSION PACKAGE:
- router.cpp: source code, router: executable file
- to compile: g++ -std=c++11 -o router router.cpp
- to run: ./router
- tested on Ubuntu 14.04
- compiler: g++ (Ubuntu 4.8.4-2ubuntu1~14.04.1) 4.8.4

2. BINARY SEARCH TREE IMPLEMENTATION

2.1. Node struct:
- Each node in the tree represents one entry in the routing table.
- Each node has (a) gateway (b) interface (c) pointer to left and right node
- The depth of the node in the tree corresponding to the cidr of the routing entry

2.2. Building the tree:
- For each entry in routes.txt, parse the ip address and translate into binary
- For each bit, go left/right depending on the value of the bit, stop when we are 
as deep as indicated by the cidr.
- Insert the value of (gateway, interface) to the current node

2.3. Searching the tree:
- For each entry in PDU, parse the destination ip address and convert to binary
- For each bit, go left/right depending on the value of the bit, stop when we read a NULL node.
- While traversing, if there is a non-empty node, we updated the current value of the most
specific path possible

3. explain the sample output
Output:
  192.168.1.99:9999->10.3.0.1:22 via 192.168.1.3 (eth0-01:23:45:67:89:01) ttl 8
  192.168.1.99:9999->10.3.0.1:22 discarded (TTL expired)
  192.168.1.99:10000->10.4.0.1:22 via 192.168.1.4 (eth0-01:23:45:67:89:02) ttl 8
  10.4.0.1:22->192.168.1.99:10000 directly connected (eth0-192.168.3.2) ttl 8
  192.168.1.99:10001->10.5.0.1:22 via 192.168.3.2 (ppp0) ttl 8 (No path found, hence using default gateway)
  192.168.1.98:10001->10.5.0.1:22 via 192.168.3.2 (ppp0) ttl 8 (No path found, hence using default gateway)

PDU 1: This is the case when the gateway address is found.
PDU 2: This is the case when TTL expired before finding the gateway address.
PDU 3: This is the case when the gateway address is found.
PDU 4: This is the case when it is connected directly to the default gateway.
PDU 5: This is the case when the gateway is not found so it uses default gateway.
PDU 6: This is the case when the gateway is not found so it uses default gateway.

-- how we get the result for each of the pdu
