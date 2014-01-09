This project is for communication between linux in two different PC, A and B.

File description

client_cmd.c:
		a client called "clietn_cmd" running in A to send command to the server running in B.
		
server_cmd.c:
		a server  called "server_cmd"in B for waitting for recieving command frome the client in A.
		
client_data.c:
		a client process calle "client_data" for transmitting data from A to B is created by server_cmd when client_cmd recieves the command,"start".
		
server_data.c:
		a server process called "server_data" running in B for recieving data from A.

sock_core.c:
		some function called for socket communication is packaged in this file.

data_generator.c:
		generate data for transmitting by client_data


Other
		The daemon is not used in this project and must be added in future.
			 
		