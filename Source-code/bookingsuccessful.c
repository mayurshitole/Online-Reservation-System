#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bookingsuccessful.h"

void print_success(int sock,char *username,char* password){

		char buffer[1000]={};

		write(sock, "HTTP/1.1 200 OK\n", strlen("HTTP/1.1 200 OK\n"));
		write(sock,"close\n",6);
		write(sock,"Content-Length: 999\n",19);
		write(sock, "Content-Type: text/html\n\n", 25);
		sprintf(buffer,"<html><title>Congratulations!</title><body><h1>Congratulations %s! Your ticket has been booked successfully! <br> If you want to make another booking please click below!</h1><br><br><a href=\"/login.html?username=%s&password=%s\">Click here!</a></body></html>",username,username,password);  
		// strcpy(buffer,"<html><body><img src=\"http://vignette2.wikia.nocookie.net/glee/images/1/14/Yippee-1.gif/revision/latest?cb=20110713130918\" alt=\"Superman\" style=\"width:304px;height:228px;\"></body></html>");  
		
		// //<img src=\"http://vignette2.wikia.nocookie.net/glee/images/1/14/Yippee-1.gif/revision/latest?cb=20110713130918\" alt=\"Superman\" style=\"width:304px;height:228px;\">


		
		write(sock, buffer,999);



		close(sock);



}