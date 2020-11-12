
shell_group26:main.c cmds.o ps.o ls.o tree.o copy.o
	gcc main.c -lreadline cmds.o ps.o ls.o tree.o copy.o -o shell_group26

cmds.o: cmds.c
	gcc -c cmds.c 

ps.o: ps.c
	gcc -c ps.c

ls.o: ls.c
	gcc -c ls.c

tree.o: tree.c
	gcc -c tree.c

copy.o: copy.c
	gcc -c copy.c

clean:
	rm *.o
