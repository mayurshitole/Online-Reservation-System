#include <stdio.h>

#include "movieshows.h"

void movieshows(int sock,char *username){

		char size[1000]={};

		write(sock, "HTTP/1.1 200 OK\n", strlen("HTTP/1.1 200 OK\n"));
		write(sock,"close\n",6);
		write(sock,"Content-Length: 900\n",19);
		write(sock, "Content-Type: text/html\n\n", 25);
		// sprintf(size,"<html><body><H1>The name is %s and surname is %s</H1></body></html>",username,password);  
		
		sprintf(size,"<html><head></head><body><form name=\"myform\" action=\"reservation.html\" target=\"result\" method=\"get\" onchange=\"this.form.submit()\"><P ALIGN=\"CENTER\"><font size=\"+2\">HI %s PICK YOUR SHOW</font></p><P ALIGN=\"CENTER\"><A NAME=\"name\"><img src=\"http://ecx.images-amazon.com/images/I/414iolbpjfL._AC_UL320_SR220,320_.jpg\" alt=\"Superman\" style=\"width:304px;height:228px;\"></a></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"superman\">SUPERMAN</p><br><br><P ALIGN=\"CENTER\"><img src=\"http://i.imgur.com/jNQAp.jpg\" alt=\"Batman\" style=\"width:304px;height:228px;\"><br></p><br><P ALIGN=\"CENTER\"><input type=\"radio\" name=\"movie\" value=\"batman\">BATMAN</p><br><br><P ALIGN=\"CENTER\"><input type=\"submit\" value=\"Submit\"></p></form></body></html>",username);
			write(sock, size,900);

}