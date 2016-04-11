PROJECT 1 SUBMISSION

- Student 1: PHAN HUY NGUYEN - 661672819
- Student 2: SAKAWKARN PIYAWITWANICH - 661109013
- Student 3:

1. Introduce the directory, how to compile, how to run the file


2. how to implement the tree

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
