all: testmem_child mapintsfile genintsfile2  

CFLAGS= -g -Wall 
 

mapintsfile: mapintsfile.c
	gcc -o mapintsfile $(CFLAGS) mapintsfile.c 


testmem_child: testmem_child.c
	gcc -o testmem_child $(CFLAGS) -no-pie testmem_child.c 


genintsfile2: genintsfile2.c
	gcc -o genintsfile2 $(CFLAGS) genintsfile2.c 	

 
	
clean:
	rm -rf  testmem_child mapintsfile genintsfile2  

