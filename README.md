Pseudo code 
1.	Initiate system definitions, functions, status
	Players: customers A, B, C, D, miners E1 and E2.
	A linked list (blockchain) generated and maintained by miners contains the ledger. 
	Each list item is a block of at most 4 valid transactions, one per customer
	Each customer has an initial balance of D Dollars and B Bitcoins
	Each customer maintains its own current ledger, which is open for miners’ inspection  
	Transactions: T0 – customer u buys x Bitcoins for the price of y Dollars from customer z, T1 - null (no) transaction. 
	Set a limit on number of events (large number), where an event is that a transaction, defined above, occurs.
	 Transaction is generated using the C++ uniform PRNG, where the probability of the events T0, T1, for each customer is 0.25, and 0.75. If customer x is initiating a buy transaction, then customer y (different that x) is randomly selected.
	 Generate random numbers between 0 and ‘f’, for the relevant  x, and y. 
2.	Generate events { // initial time is 0
	Randomly, choose the time increment for the next event (a value between 1 and 10)
	For each selected new time and for each customer, 
	Generate events for customers and Queue  the events in an Event Queue (Q) 
	Allow only one transaction request per customer per timed-event
	E1 Record the transaction request and its time in a .csv event-file
3.	Infinite loop on events { // in this case it looks like the miners represents the system
	Each miner read the next [set of events] of the next time unit from the event-queue
	For each request, where it is assumed that each request is broadcasted 
	The miners check the validity of the request, where valid means that the parties have enough Dollars and/or Bitcoins for the transaction.
	If valid, the miners adds this request to a current tentative block (simple data structure)
	E1 records the transaction request in a .csv requests-file
	The miners compete using PoET on the right to add the (non-empty) valid blocks to the blockchain (no cryptographic hash nor anonymity).  The winning miner adds its block to the chain
	E1 records the new chain status (only the “delta”) in a .csv chain-file
	E1 checks for termination condition (empty event file)	}
	E1 Evaluates and record statistics
	Average number of transaction attempts, average number of successful chain construction per miner per time unit.
Assignment Instructions:
1)	Set the system and the number of events so that each customer is performing numerous different transactions.
2)	Induce innocent errors into transactions.
3)	Produce the java code for the above pseudo code. 
4)	Deliverables: 1) program code, 2) CSV files, and 3) execution screenshot (‘1’ - red-flag).
