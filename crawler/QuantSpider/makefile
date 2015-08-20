CC = g++
#CFLAGS = -march=core2 -Wall -O3 -g -gstabs+
CFLAGS = -march=core2 -Wall -g -gstabs+
spider: spider.o
	$(CC) $(CFLAGS) -o $@ $< -levent -lpthread
spider.o: spider.c bloom.h dns.h url.h http.h
clean: 
	-rm spider.o spider downpage/*
