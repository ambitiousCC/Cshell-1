G = gcc
CFLAGS1 = -lreadline

shell_group26:main.o cmds.o ps.o ls.o
	$(G) -fPIC $(CFLAGS1) -o shell_group26 main.o cmds.o ps.o ls.o

main.o: main.c cmds.h ps.h ls.h
	$(G) -c main.c

cmds.o: cmds.c cmds.h ps.h ls.h
	$(G) -shared -fPIC -c cmds.c

ps.o: ps.c ps.h
	$(G) -fPIC -c ps.c

ls.o: ls.c ls.h
	$(G) -fPIC -c ls.c

clean:
	*.o
