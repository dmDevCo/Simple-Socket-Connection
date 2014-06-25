

    /* ===========================================================> server.c 
     * Simple server process to test the use of the Unix socket support
     * using the TCP protocol.
     *
     * =====================================================================
     */

    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h> 
    #include <stdio.h>

    void main()
    {
       int                sock, clientsock, mlen=1, addrsize, msgct, chc, chct,i=0;
       struct sockaddr_in addr;
       char               ch, buf[80];

       /*
        * Create a socket to use.
        */

       sock = socket(AF_INET, SOCK_STREAM,0);   
       if (sock == -1)
       {   
          perror("opening socket");
          exit(-1);
       }

       /*
        * Bind a name to the socket.  Since the server will bind with
        * any client, the machine address is zero or INADDR_ANY.  The
        * bind call sets up the socket-port pair, where the socket specifies
        * the protocol and the port is used by the operating system to direct
        * messages to this program.
        */

       addr.sin_family = AF_INET;
       addr.sin_port = htons (32351);
       addr.sin_addr.s_addr = htonl (INADDR_ANY);

       if (bind(sock, (struct sockaddr *)&addr, sizeof (struct sockaddr_in)) == -1) 
       {  
          perror ("on bind");
          exit (-1);
       }

       /*
        * Make the socket available.  The listen call causes the operating
        * system to make the socket available for connections.
        */


       if (listen(sock,1) == -1)
       {  
          perror("on listen");
          exit(-1);
       }

       /*
        * Wait for a client to connect.  When this happens, print out a 
        * message.  Note that clientsock is a brand new socket just for this
        * client.
        */

       addrsize = sizeof(struct sockaddr_in);

       clientsock = accept(sock, (struct sockaddr *)&addr, &addrsize);
       if (clientsock == -1)
       {  
          perror("on accept");
          exit(-1);
       }

       printf("connection made with client %s", inet_ntoa (addr . sin_addr));

       /*
        * Receive and print a client message where a null character terminates.
        * Note that a single receive may not work in some cases, but is OK for
        * a simple example.
        */
	/* while(mlen==1)
	{
		mlen = recv (clientsock, buf, 80, 0);
		i++;
		if(i>10){
		break;
		}
	} */
	
		mlen = recv (clientsock, buf, 80, 0);
		
       send (clientsock, "Got your message \n\n", 17, 0);
	   printf("%s \n\n", &buf);
       printf(" Server - all messages read - connection being closed\n");

       /*  
        * Close the client socket and also the server socket 
        */

       close(clientsock);
       close(sock);
    }

