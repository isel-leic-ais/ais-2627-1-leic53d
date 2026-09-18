all: child_msg launch

launch: launch.c
	gcc -o launch -Wall launch.c

child_msg: child_msg.c
	gcc -o child_msg -Wall child_msg.c

clean:
	rm -rf child_msg launch

