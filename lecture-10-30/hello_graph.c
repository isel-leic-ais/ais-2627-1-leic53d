#include <pg/pglib.h>
#include <stdio.h>

void  suspend(char *msg) {
	printf("%s: press return to  continue...", msg);
	getchar();
}

int main() {
    printf("mypid = %d\n", getpid());
    suspend("start");
    graph_init2("Hello From AIS", 800, 600);

    graph_start();
    return 0;
}
