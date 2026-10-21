all : scall_demo scallint_demo tst_scall 

scall_demo: scall_demo.c 
	gcc -o scall_demo  -g -Wall scall_demo.c mywrite.s  
	
scallint_demo: scallint_demo.c mywrite32.s 
	gcc -o scallint_demo  -g -Wall scallint_demo.c  mywrite32.s

tst_scall: tst_scall.c  mygetpid32.s
	gcc -o tst_scall -g -Wall tst_scall.c  mygetpid32.s chrono.c  
	
clean:
	rm -rf scall_demo scallint_demo tst_scall *.o
