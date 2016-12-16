
OBJS := main.o student.o hash.o queue.o list.o

a.out: $(OBJS)
	gcc -o a.out $(OBJS)

main.o:list.h queue.h hash.h student.h

student.o:hash.h student.h

hash.o:list.h hash.h

list.o:list.h

queue.o:queue.h

clean: 
	rm -rf *.o
