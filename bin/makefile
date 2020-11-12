
shell_group26:main.c cmds.o ps.o ls.o
	gcc main.c -lreadline cmds.o ps.o ls.o -o shell_group26

cmds.o: cmds.c
	gcc -c cmds.c 

ps.o: ps.c
	gcc -c ps.c

ls.o: ls.c
	gcc -c ls.c

clean:
	rm *.o
