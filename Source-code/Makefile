##****************************************************************************
## CMPE 207 (Network Programming and Applications) Sample Program.
##
## San Jose State University, Copyright (2016) Reserved.
##
## DO NOT REDISTRIBUTE WITHOUT THE PERMISSION OF THE INSTRUCTOR.
##****************************************************************************

CC=gcc


TARGETS=movieserver2

all: $(TARGETS)

movieserver2: movieserver2.c
	$(CC) movieserver2.c reservation.c bookingsuccessful.c movieshows.c -o movieserver2 `mysql_config --cflags --libs` -lpthread

clean:
	rm -f *.o $(TARGETS)

