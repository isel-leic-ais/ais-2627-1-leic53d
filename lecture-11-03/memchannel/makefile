all:  ring_buffer_test anonymous_pipe_test mc_test

UTILS=../utils
INCLUDES = -I $(UTILS)



ring_buffer_test : ring_buffer_test.c $(UTILS)/utils.c ring_buffer.c $(UTILS)/chrono.c
	gcc -o ring_buffer_test $(INCLUDES) -Wall ring_buffer_test.c ring_buffer.c $(UTILS)/utils.c $(UTILS)/chrono.c

anonymous_pipe_test : anonymous_pipe_test.c $(UTILS)/utils.c $(UTILS)/chrono.c
	gcc -o anonymous_pipe_test $(INCLUDES) -Wall anonymous_pipe_test.c $(UTILS)/utils.c $(UTILS)/chrono.c

mc_test : mc_test.c $(UTILS)/utils.c $(UTILS)/memutils.c mem_channel.c ring_buffer.c  $(UTILS)/chrono.c
	gcc -o mc_test $(INCLUDES) -Wall mc_test.c $(UTILS)/memutils.c mem_channel.c ring_buffer.c $(UTILS)/utils.c $(UTILS)/chrono.c

clean:
	rm -rf anonymous_pipe_test ring_buffer_test  mc_test
