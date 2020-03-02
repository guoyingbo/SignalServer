CC = gcc
XX = g++
TARGET = SignalServer
CFLAGS = -Wall -O -g
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@
%.o : %.cpp
	$(XX) $(CFLAGS) -c $< -o $@
SOURCES = $(wildcard  *.c  *.cc)
OBJS = $(patsubst %.c,%.o,$(patsubst %.cc,%.o,$(SOURCES)))

$(TARGET) : $(OBJS)
	$(XX) $(OBJS) -o $(TARGET)
clean:
	rm -rf *.o SignalServer

install:
	cp ./SignalServer /usr/local/bin/SignalServer
	cp ./SignalServer.conf /usr/local/etc/SignalServer.conf
	cp ./service.sh /etc/init.d/SignalServer
	chmod +x /etc/init.d/SignalServer
