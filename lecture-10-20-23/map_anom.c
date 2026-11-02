#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/mman.h>

#define MAP_SIZE 8*1024


bool zeroed(int *vals, int size) {
    for(int i=0; i < size; ++i) {
        if (vals[0] != 0) return false;
    }
    return true;
}

int main() {
    int *nums = (int *) mmap(NULL, MAP_SIZE, PROT_READ | PROT_WRITE, 
            MAP_ANONYMOUS | MAP_SHARED, -1, 0);
  
    if (nums == MAP_FAILED) {
        perror("error creating anonymous region");
        return 1;
    }
    
    printf("parent: nums is zeroed? %s\n",  zeroed(nums, MAP_SIZE)? "yes" : "no");
    nums[0] = 1;
    printf("parent: nums[0] before child = %d\n", nums[0]);
 
    if (fork() == 0) {
          printf("child: nums[0] before write = %d\n", nums[0]);
          nums[0] = 2;
          munmap(nums, MAP_SIZE);
          exit(0);
    }
    else {
        wait(NULL);
        printf("parent: nums[0] after child = %d\n", nums[0]);
 
    }
    
    munmap(nums, MAP_SIZE);
    return 0;
}
