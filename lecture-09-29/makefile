all: segvtest launch2 test_abort launch3

FLAGS=-Wall -g

segvtest: segvtest.c print_utils.c
	gcc -o segvtest $(FLAGS) segvtest.c print_utils.c

launch2: launch2.c
	gcc -o launch2 $(FLAGS)  launch2.c

launch3: launch3.c
	gcc -o launch3 $(FLAGS)  launch3.c print_utils.c

test_abort: test_abort.c
	gcc -o test_abort $(FLAGS)  test_abort.c

clean:
	rm -rf segvtest launch2 test_abort launch3