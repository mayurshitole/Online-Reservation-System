#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "movieshows.h"

int movieshows(int sock,char *username){		

		char size[1000]={};
		bzero(size,1000);
		write(sock, "HTTP/1.1 200 OK\n", strlen("HTTP/1.1 200 OK\n"));
		// write(sock,"close\n",6);
		write(sock,"Content-Length: 999\n",19);
		write(sock, "Content-Type: text/html\n\n", 25);
		//sprintf(size,"<html><body><H1>The name is %s and surname is %s</H1></body></html>",username,password);  
		
		// sprintf(size,"<html><body><form action=\"reservation.html\" method=\"get\"><title>Shows</title><P ALIGN=\"CENTER\"><font size=\"+2\">HI %s PICK YOUR SHOW</font></p><P ALIGN=\"CENTER\"><A NAME=\"name\"><img src=\"http://ecx.images-amazon.com/images/I/414iolbpjfL._AC_UL320_SR220,320_.jpg\" alt=\"Superman\" style=\"width:304px;height:228px;\"></a></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"superman\">SUPERMAN</p><br><br><P ALIGN=\"CENTER\"><img src=\"http://i.imgur.com/jNQAp.jpg\" alt=\"Batman\" style=\"width:304px;height:228px;\"><br></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"batman\">BATMAN</p><br><br><P ALIGN=\"CENTER\"><input type=\"submit\" value=\"Submit\"></p></form></body></html>",username);
			
		// sprintf(size,"<html><body><form action=\"reservation.html\" method=\"get\"><title>Shows</title><P ALIGN=\"CENTER\"><font size=\"+2\">HI %s PICK YOUR SHOW</font></p><P ALIGN=\"CENTER\"><A NAME=\"name\"><img src=\"/image/superman.gif\" alt=\"Superman\" style=\"width:304px;height:228px;\"></a></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"superman\">SUPERMAN</p><br><br><P ALIGN=\"CENTER\"><img src=\"/image/batman.jpg\" alt=\"Batman\" style=\"width:304px;height:228px;\"><br></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"batman\">BATMAN</p><br><br><P ALIGN=\"CENTER\"><input type=\"submit\" value=\"Submit\"></p></form></body></html>",username);

		sprintf(size,"<html><body><form action=\"reservation.html\" method=\"get\"><title>Movie Selection</title><P ALIGN=\"CENTER\"><font size=\"+2\">HI %s PICK YOUR SHOW</font></p><P ALIGN=\"CENTER\"><A NAME=\"name\"><img src=\"/image/superman.jpg\" alt=\"Superman\" style=\"width:304px;height:228px;\"></a></p><br><P ALIGN=\"CENTER\"><input type =\"hidden\" name=\"username\" value=\"%s\"><input type=\"radio\" name=\"movie\" value=\"superman\">SUPERMAN</p><br><br><P ALIGN=\"CENTER\"><img src=\"/image/batman.jpg\" alt=\"Batman\" style=\"width:304px;height:228px;\"><br></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"batman\">BATMAN</p><br><br><P ALIGN=\"CENTER\"><input type=\"submit\" value=\"Submit\"></p></form></body></html>",username,username);
		

			write(sock, size,999);
			//printf("%s\n", size);
			return 1;

		// pthread_exit(NULL);
		//close(sock);


}
