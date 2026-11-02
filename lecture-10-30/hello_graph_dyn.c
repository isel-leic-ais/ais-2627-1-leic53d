#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>
#include <pg/pglib.h>


void  suspend(char *msg) {
	printf("%s: press return to  continue...", msg);
	getchar();
}

typedef int (*graph_init_ptr)(const char *title, int width, int height);
typedef void (*graph_start_ptr)();
typedef void (*mouse_event_handler_t)();
typedef void (*graph_exit_ptr)();
typedef int (*graph_regist_mouse_handler_ptr)( mouse_event_handler_t handler);

graph_exit_ptr graph_exit_impl;

void mouse_handler(MouseEvent me) {
     
    if (me.type == MOUSE_BUTTON_EVENT) {
        graph_exit_impl();
    }
}

int main() {
    printf("my pid is %d\n", getpid());
	suspend("start");
    
	void *pglib = dlopen("libpg.so", RTLD_LAZY);
    if (pglib == NULL) {
		perror("error loading library");
		return 1;
	}

    printf("pglib loaded at %p\n", pglib);

    suspend("after dl_open");
	
	graph_init_ptr graph_init  = (graph_init_ptr) dlsym(pglib, "graph_init2");
    graph_start_ptr graph_start = (graph_start_ptr) dlsym(pglib, "graph_start");
    graph_regist_mouse_handler_ptr graph_regist_mouse_handler = (graph_regist_mouse_handler_ptr) dlsym(pglib, "graph_regist_mouse_handler");
    graph_exit_impl = (graph_exit_ptr) dlsym(pglib, "graph_exit");
    graph_init("Hello_From_AIS", 800, 600);
    graph_regist_mouse_handler(mouse_handler);

    graph_start();
    	
	dlclose(pglib);
    suspend("after dlclose");
    return 0;

}
