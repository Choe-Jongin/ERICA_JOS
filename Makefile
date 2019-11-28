EXEC = jos.out
CC = g++
CFLAGS = -g

OBJECT = JOS.o Desktop.o Window.o Box.o
$(EXEC):
	$(OBJS) $(CC)  $(CFLAGS) -o $(EXEC)  $(OBJECT)

$(OBJS):
	$(CC)  $(CFLAGS) -c $*.cpp

relink:
	$(CC)  $(CFLAGS)  -o $(EXEC)  $(OBJECT)
