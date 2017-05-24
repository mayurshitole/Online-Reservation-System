#include <stdio.h>
// #include <mysql/mysql.h>
#include <stdlib.h>
#include <string.h>

#include "reservation.h"

int reservation(int sock,char *username,int num_fields,int row[]){

		// printf("in function num_fields :%d\n",num_fields);

		char size[2000]={};
		char temp_buf[2000]={};
		int i;

		// sprintf(size,"<html><body><H1>The name is %s and surname is %s</H1></body></html>",username,password);  
		sprintf(size,"<html><body><form action=\"reservation_conf.html\" method=\"get\" accept-charset=\"ISO-8859-1\"><title>Booking</title><p><font size=\"+2\">Welcome %s Please book your seat!</font></p>",username);  
		
		//printf("here");
		for(i=0;i<num_fields;i++){

			sprintf(temp_buf,"<input type=\"checkbox\" name=\"seat\" value=\"%d\">%d",row[i],row[i]);
			strcat(size,temp_buf);

		}
		//printf("%s\n",size);
		//strcat(size,temp_buf);
		strcat(size,"<p><input type=\"submit\" value=\"submit\"></p></form></body></html>");
		
		printf("%d\nXXXXXXXXXXXXXXXXx\n",strlen(size));

		write(sock, "HTTP/1.1 200 OK\n", strlen("HTTP/1.1 200 OK\n"));
		write(sock,"close\n",6);
		write(sock,"Content-Length: 900\n",19);
		write(sock, "Content-Type: text/html\n\n", 25);
		write(sock, size,1000);
		//printf("reservation done!\n");
		// close(sock);
		return 1;
		//
		
		
}