#include<stdio.h>
#include<string.h>    //strlen
#include<stdlib.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write
#include<pthread.h> //for threading , link with lpthread
#include <errno.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <mysql/mysql.h>

#include "reservation.h"
#include "bookingsuccessful.h"
#include "movieshows.h"

//for MYSQL connection

static char *host = "localhost";
static char *user = "root";
static char *pass = "welcome123#";
static char *dbname = "test";

unsigned int port = 3306;
static char *unix_socket = NULL;
unsigned int flag = 0; //ODBC connnection

MYSQL *conn;

//global username
// char username[50];
char movie[20];
char password[20];


static int count = 0; 


//the thread function

char root[50];
#include "movieshows.h"
struct container{

		char *hold;

};

void *connection_handler(void *);
pthread_mutex_t lock1;
pthread_mutex_t lock2;
pthread_mutex_t lock3;
pthread_mutex_t lock4;
pthread_mutex_t lock5;
pthread_mutex_t lock6;

//get file size

int http_get_filesize(FILE *fp)
{
	
	int fsize;
	fseek(fp, 0, SEEK_END);
	fsize = ftell(fp);
	rewind(fp);
	
	return fsize;
}


//get file extension!
const char * http_get_mime(const char *fname)
{
	
	const char *extf = strrchr(fname, '.');
	if (extf == NULL) {
	return "application/octet-stream";
	} else if (strcmp(extf, ".html") == 0) {
	return "text/html";
	} else if (strcmp(extf, ".jpg") == 0) {
	return "image/jpeg";
	} else if (strcmp(extf, ".gif") == 0) {
	return "image/gif";
	}else if (strcmp(extf, ".png") == 0) {
	return "image/png";
	} else if (strcmp(extf, ".ico") == 0) {
	return "text/html";		
	} else {
	return "application/octet-stream";

	
	}
}

//readline() function

int http_readline(int sock, char *buf, int maxlen)
{
		int	n = 0;
		char *p = buf;
			while (n < maxlen - 1) {
				char c;
				int rc = read(sock, &c, 1);
				if (rc == 1) {
				/* Stop at \n and strip away \r and \n. */
					if (c == '\n') {
					*p = 0; /* null-terminated */
					return n;
					} else if (c != '\r') {
						*p++ = c;
						n++;
					}
				} else if (rc == 0) {
					return -1;
					/* EOF */
				} else if (errno == EINTR) {
					continue;
					/* retry */
				} else {
					return -1;
					/* error */
				}
			}
	return -1; /* buffer too small */
}
 
int main(int argc , char *argv[])
{
    int sd , client_sock , c;
    struct sockaddr_in server , client;
    //char buffer[10];
	     
    if (argc <3){
		printf("Please enter valid port number and Document root where your Index file and other files are kept!");
		return -1;
		} 
	bzero(root,50);
	strcpy(root,argv[2]);
	//printf("root is : %s",root);

	//MYSQL *conn;
	conn = mysql_init(NULL);
	if (!(mysql_real_connect(conn,host,user,pass,dbname,port,unix_socket,flag))){
		fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
		exit(1);
	}

	printf("Database connection sucessful\n");

	//Create socket
    sd = socket(AF_INET , SOCK_STREAM , 0);
    if (sd == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
    
    // make socket port resuable
    
		int enable = 1;
		if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR,&enable, sizeof(enable)) < 0) {
		printf("Failed to set sock option SO_REUSEADDR");
		}
		
    int port = atoi(argv[1]); 
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(port);
     
    //Bind
    if( bind(sd,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(sd , 10);
     
         
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);


	//thread creation
	pthread_t thread_id;
	pthread_attr_t ta;
	pthread_attr_init(&ta);
	pthread_attr_setdetachstate(&ta, PTHREAD_CREATE_DETACHED);

	if (pthread_mutex_init(&lock1, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&lock2, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&lock3, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&lock4, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
    if (pthread_mutex_init(&lock5, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }
     if (pthread_mutex_init(&lock6, NULL) != 0)
    {
        printf("\n mutex init failed\n");
        return 1;
    }

	int i=1;
    while( (client_sock = accept(sd, (struct sockaddr *)&client, (socklen_t*)&c)) )
    {
        puts("Connection accepted\n");
     	printf("client_sock : %d\n",client_sock);   
         
        if( pthread_create( &thread_id , &ta ,  connection_handler , (void*) &client_sock) < 0)
        {
            perror("could not create thread");
            close(client_sock);
            continue;
        }

         
        //Now join the thread , so that we dont terminate before the thread
        //pthread_join( thread_id , NULL);
        printf("Handler assigned to client %d\n",i);

      fprintf(stderr,"clinet %d IP address : %s and port no. is : %d\n",i, inet_ntoa(client.sin_addr),ntohs(client.sin_port));
        i++;        
    }
     
    if (client_sock < 0)
    {
        perror("accept failed");
        return 1;
    }
    
    pthread_attr_destroy(&ta); 
    pthread_mutex_destroy(&lock1);
	pthread_mutex_destroy(&lock2);
	pthread_mutex_destroy(&lock3);
	pthread_mutex_destroy(&lock4);
	pthread_mutex_destroy(&lock5); 
	close(sd);
    return 0;
}
 

void *connection_handler(void *sd)
{
    //Get the socket descriptor
    int sock = *(int*)sd;
    char buffer[50000]={};
	char input_get[100]={};		// buffer for get request input!
    struct stat stat_buf;  
	char filename[500]={};
	char *s;
    char path[500]={};
    FILE *fd;
    FILE *input_file;
   	int seat;
   	char username[50];
   	

    int file_size;
    char size[9999]={};
    char send_buf[1000];

    char file_extn[50]={};			// buffer for file extension!
	char type[50];
    bzero(buffer,50000);

    struct container value[10];

    //MYSQL variables
    MYSQL_ROW row;
    MYSQL_RES *result;

	

	//read(sock,buffer,sizeof(buffer));
	//printf("%s\n",buffer);

	//get entire GET reuest in filename
	bzero(path,500);
	// pthread_mutex_lock(&lock1);
	http_readline(sock,path,500);
	// pthread_mutex_unlock(&lock1);
	printf("%s\n",path);


	if (strstr(path,"HTTP/1.1")== "NULL" || strstr(path,"HTTP/1.0")== "NULL"){
		write(sock, "HTTP/1.0 400 Bad Request\n", 25);
		}

	int j;

	// pthread_mutex_lock(&lock2);
	// for (j=0;j<4;j++){
		
	// 	http_readline(sock,input_get,100);
	// 	//printf("%s\n",input_get);
	// 	bzero(input_get,sizeof(input_get));
	// }
	// pthread_mutex_unlock(&lock2);

	s=strchr(path,'/');			
	s = strtok(s," ");
	strcpy(filename,s);
	
	if (strlen(filename)==1){
		strcpy(filename,"/username.html");
		}
	else if (strcmp(filename,"/favicon.ico")==0){
		strcpy(filename,"/username.html");
		}
	
	//append file path!
	char path1[500]={};
	bzero(path1,500);

	strcat(path1,root);
	strcat(path1,filename);
		
	input_file = fopen(path1, "r");

		if (strstr(filename,"login")!=NULL){
		
		
		char *data = (char*) malloc (sizeof(char));
		char *name;
				

		s=strchr(path,'?');
		s++;
		//printf("s : %s\n",s);
		
		name = strtok(s,"&");
		int count = 0;
		
		while(name!=NULL){
		s = strchr(name,'=');
		s++;
		value[count].hold = s;
		//printf("%s\n",value[count].hold);
		count++;
		name = strtok(NULL,"&");
		}
				
		// pthread_mutex_lock(&lock5);
		strcpy(username,value[0].hold);
		// pthread_mutex_unlock(&lock5);
		printf("username : %s\n",username);

		// pthread_mutex_lock(&lock6);
		strcpy(password,value[1].hold);
		// pthread_mutex_unlock(&lock6);
		printf("password : %s\n",password);

		char temp_buf[100];
		bzero(temp_buf,100);
		sprintf(temp_buf,"SELECT * FROM users where name='%s' and password='%s'",username,password); 

		printf("%s\n",temp_buf);
		//printf("%s\n\n",movie_buf);

				if (mysql_query(conn,temp_buf)) 
				{
			      fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
				}

				// /printf("after query");
				MYSQL_RES *result = mysql_store_result(conn);

							  
				if (result == NULL) 
				{
			      fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
				}
							
				// printf("after result");
				MYSQL_ROW row = mysql_fetch_row(result);
				// printf("sql query sucessful");
				

				if(row != NULL){
					if(movieshows(sock,username)){

						//printf("movieshow worked!\n");
					}
					//printf("here");
					// printf("after movieshows");
					//pthread_exit(NULL);
					 // close(sock);
					// return 0;
					
				}else{
					//printf("invalid username or password");
					write(sock, "HTTP/1.1 404 Not Found\n", 23);
					write(sock,"close\n",6);
					write(sock,"Content-Length: 172\n",19);
					write(sock, "Content-Type: text/html\n\n", 25);
					write(sock, "<html><title>Error</title><body><H1>Invald Username and/or Password! Please follow below link to go back<br><br><a href=\"/username.html\">Click here!</a></H1></body></html>",172);
					close(sock);
					//return 0;
				}
				 printf("closing sock : %d\n",sock);
				 pthread_exit(NULL);
				 close(sock);
				 return 0;
			}
		
		if (strstr(filename,"reservation.html")!=NULL){

			if(strstr(path,"movie")!=NULL){
			
			
		char *name;
		s=strchr(path,'?');
		s++;
		//printf("s : %s\n",s);
		
		name = strtok(s,"&");
		count = 0;
		
		while(name!=NULL){
		s = strchr(name,'=');
		s++;
		value[count].hold = s;
		//printf("%s\n",value[count].hold);
		count++;
		name = strtok(NULL,"&");
		}

		// pthread_mutex_lock(&lock5);
		strcpy(username,value[0].hold);
		// pthread_mutex_unlock(&lock5);
		printf("username : %s\n",username);

		// pthread_mutex_lock(&lock6);
		strcpy(movie,value[1].hold);
		// pthread_mutex_unlock(&lock6);
		printf("movie : %s\n",movie);





			//now to check how many seats are available from mysql!
				char movie_buf[100];
				bzero(movie_buf,100);
				sprintf(movie_buf,"SELECT * FROM %s where name=\"\"",movie); 
				printf("%s\n\n",movie_buf);

				if (mysql_query(conn,movie_buf)) 
				{
			      fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
				}
			  
				MYSQL_RES *result = mysql_store_result(conn);
			  
				if (result == NULL) 
				{
			      fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
				}

				int num_fields = mysql_num_fields(result);
				
				MYSQL_ROW row;
				int count=0;
				char temp_buf[100];
				int rowArr[10];
				while ((row = mysql_fetch_row(result))) 
				{ 
					
			     		bzero(temp_buf,100);
						sprintf(temp_buf,"%s ",row[0]);
						strcat(send_buf,temp_buf);
						rowArr[count] = atoi(row[0]);
						count++;	
						//printf("rowArr :%d\n",atoi(row[i]));
					 
			     } 
			          
			    if(count>0){
				
				if(reservation(sock,username,count,rowArr)){
					printf("closing sock : %d\n",sock);
				 	pthread_exit(NULL);
					 close(sock);
					 return 0;				
				}
				
				} else{

					write(sock, "HTTP/1.1 404 Not Found\n", 23);
					write(sock,"close\n",6);
					write(sock,"Content-Length: 224\n",21);
					write(sock, "Content-Type: text/html\n\n", 25);
					bzero(send_buf,1000);
					sprintf(send_buf,"<html><title>Housefull</title><body><h1>Sorry! The show is Housefull! If you would like to continue with another booking please click below link!<br><br><a href=\"/login.html?username=%s&password=%s\">Click here!</a></h1></body></html>",username,password);
					write(sock, send_buf,224);
					close(sock);
					return 0;

				}
				 printf("closing sock : %d\n",sock);
				 pthread_exit(NULL);
				 close(sock);
				 return 0;
		} else{
				// printf("show not selected\n");
					s=strchr(path,'?');
					s++;
					//printf("s : %s\n",s);
					
					char *t = strtok(s,"&");

					s = strchr(t,'=');
					s++;
					strcpy(username,s);
					bzero(send_buf,1000);
					write(sock, "HTTP/1.1 404 Not Found\n", 23);
					write(sock,"close\n",6);
					write(sock,"Content-Length: 220\n",21);
					write(sock, "Content-Type: text/html\n\n", 25);
					bzero(send_buf,1000);
					sprintf(send_buf,"<html><title>Error</title><body><h1>You haven't selected any movie! Please click below link to go back!<br><br><a href=\"/login.html?username=%s&password=%s\">Click here!</a></h1></body></html>",username,password);
					write(sock, send_buf,220);
					close(sock);
					return 0;
		}
	}
		
		 if (strstr(filename,"reservation_conf.html")!=NULL){
			
			if(strstr(path,"seat")!=NULL){
			// printf("in reservation_conf\n");
			
		
			int seat_no[10];
			s=strchr(path,'?');
			s++;
			//printf("s : %s\n",s);
			
			char *t = strtok(s,"&");

			s = strchr(t,'=');
			s++;
			strcpy(username,s);
			// printf("%s\n",username);

			//printf("%s\n",t);
			int count = 0;
			t = strtok(NULL,"&");
			// printf("here : %s\n",t);
			
			
			while(t!=NULL){

			s = strchr(t,'=');
			s++;
			// printf("seat = %s\n",s);
			seat_no[count] = atoi(s);
			
			
			count++;
			// if(++t !=NULL){
			// t = strtok(NULL,"&");}
			// else{break;}			
			t = strtok(NULL,"&");
			// printf("t : %s\n",t);
			}

			
		char buf[50];
		bzero(buf,50);
		
		//printf("no. of seats : %d\n",count);

		int i;
		for (i=0;i<count;i++){

		sprintf(buf,"select name from %s where seat = %d",movie,seat_no[i]);

		//sprintf(buf,"select name from ticket where seat = %d",seatno);
		//printf("%s\n",buf);
		if (mysql_query(conn,buf)) {
	      //finish_with_error(conn);
	      fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
		}
		result = 0;
		result = mysql_store_result(conn);
		row = mysql_fetch_row(result);
	

		if(strlen(row[0])>0){
			//printf("here");
			// printf("seat already booked!\n");
			// bzero(send_buf,1000);
			// strcpy(send_buf,"This ticket is already booked! please select another seat!");
			bzero(send_buf,1000);
					write(sock, "HTTP/1.1 404 Not Found\n", 23);
					write(sock,"close\n",6);
					write(sock,"Content-Length: 250\n",21);
					write(sock, "Content-Type: text/html\n\n", 25);
					bzero(send_buf,1000);
					sprintf(send_buf,"<html><title>Error</title><body><h1>This ticket is already booked! Please select another seat!! <br><br> Please click below link to go back!<br><br><a href=\"/reservation.html?username=%s&movie=%s\">Click here!</a></h1></body></html>",username,movie);
					write(sock, send_buf,250);
					close(sock);
					return 0;
		}
		else {
		bzero(buf,50);
		//printf("username : %s\n",username);
		sprintf(buf,"update %s set name = \"%s\" where seat = %d",movie,username,seat_no[i]);
		
		if (mysql_query(conn,buf)) {
	      //finish_with_error(conn);
	      fprintf(stderr,"\nError : %s [%d]\n",mysql_error(conn),mysql_errno(conn));
		}


		printf("%s selected %d seat from %s movie\n",username,seat_no[i],movie);
	}

	}
		
		print_success(sock,username,password);	
					
		printf("closing sock : %d\n",sock);
		pthread_exit(NULL);
		close(sock);
		return 0;

	}else{

					s=strchr(path,'?');
					s++;
					//printf("s : %s\n",s);
					
					char *t = strtok(s,"&");

					s = strchr(t,'=');
					s++;
					strcpy(username,s);

					bzero(send_buf,1000);
					write(sock, "HTTP/1.1 404 Not Found\n", 23);
					write(sock,"close\n",6);
					write(sock,"Content-Length: 220\n",21);
					write(sock, "Content-Type: text/html\n\n", 25);
					bzero(send_buf,1000);
					sprintf(send_buf,"<html><title>Error</title><body><h1>You haven't selected any seat! Please click below link to go back!<br><br><a href=\"/reservation.html?username=%s&movie=%s\">Click here!</a></h1></body></html>",username,movie);
					write(sock, send_buf,220);
					close(sock);
					return 0;

	}
	
	}

	

	else if (input_file == NULL) {
      fprintf(stderr, "unable to open '%s': %s\n", (char*)path1, strerror(errno));

		write(sock, "HTTP/1.1 404 Not Found\n", 23);
		write(sock,"close\n",6);
		write(sock,"Content-Length: 54\n",19);
		write(sock, "Content-Type: text/html\n\n", 25);
		write(sock, "<html><body><H1>404 File not Found!</H1></body></html>",54);
		printf("closing sock : %d\n",sock);
		pthread_exit(NULL);
		close(sock);
		return 0;
    }

   

	//get file size!
	// pthread_mutex_lock(&lock3);
	file_size = http_get_filesize(input_file);
	// pthread_mutex_unlock(&lock3);

	// pthread_mutex_lock(&lock4);
	strcpy(file_extn,http_get_mime(filename));
	// pthread_mutex_unlock(&lock4);
					
    write(sock, "HTTP/1.1 200 OK\n", strlen("HTTP/1.1 200 OK\n"));

	write(sock,"207httpd/0.0.1\n",15);
	//printf("file_size:%d\n",file_size);
	write(sock,"close\r\n",strlen("close\r\n"));
	sprintf(size, "Content-Length: %d\n", file_size);
	write(sock,size, strlen(size)+1);
	
	bzero(type,50);
	
	strncpy(type,"Content-Type: ",14);
	strcat(type,file_extn);
	strcat(type,"\n\n");
	write(sock,type,strlen(type));

	//close and reopen file to avoid malfunction!
	fclose(input_file);
	input_file = fopen(path1, "r");


	bzero(buffer,sizeof(buffer));
	int check1 = 0;
	while(check1 = fread(buffer,(file_size)+1,1, input_file)){

		if (check1==0){
			break;
		}
	}

	int check = write(sock,buffer,sizeof(buffer)+1);
	//bzero(buffer,sizeof(buffer));
	
	if (check <0){
		printf("erorr in writing!\n");
		return 0;
		fclose(input_file);
		}
	else {
		// fclose(input_file);
		}	
	
	fclose(input_file);
	printf("closing sock : %d\n",sock);
	pthread_exit(NULL);
	close(sock);
	return 0;

} 	
	
	
	
   

