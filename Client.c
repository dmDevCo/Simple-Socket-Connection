

    /* =============================================================> simple.c 
     * Simple example of a network program for the Unix environment using TCP.
     *
     * This client program simply accesses a server socket and writes a message
     * gets a response and terminates.
     * 
     * ==================================================================
     */

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <stdio.h>


	
    void main() 
    { 
       int                  sock, addrsize, i=0; 
       struct sockaddr_in   addr; 
       char                 buffer [81]; 
     
       /* 
        * Open a socket for the Internet address family and stream 
        * communication. 
        */ 

       sock = socket(AF_INET, SOCK_STREAM,0); 
       if (sock == -1) 
       {
          perror("opening socket"); 
          exit(-1); 
       } 
     


       /* 
        * Connect the socket to a server process as specified by a known IP 
        * address and port. 
        */ 
     
       addr.sin_family = AF_INET; 

       addr.sin_port = htons (32351); 
       addr.sin_addr.s_addr = inet_network ("130.191.166.3");  
       if (connect(sock,(struct sockaddr *)&addr,sizeof (struct sockaddr_in)) == -1) 
       {    
          perror("on connect"); 
          exit(-1); 
       }  
     
       /*  
        * Write a message and get the response. 
        */ 

        send (sock, "client calling server, do you read me \n\n", 38, 0); 
        recv (sock, buffer, 80, 0); 
     
	 
		printf(" %s \n\n", &buffer);
       /*  
        * Do a shutdown to gracefully terminate by saying - "no more data" 
        * and then close the socket -- the shutdown is optional  
        */ 
     
       if (shutdown(sock, 1) == -1) 
       {   
          perror("on shutdown"); 
          exit(-1); 
       } 
     
       close(sock); 
    } 



