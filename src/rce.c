// Host remote debug port
#include <stdio.h>
#include <stdlib.h>

void shell() {
    puts("Write debug command to execute.");
    getchar();
    
    char buffer[512];
    beginning:
    printf("> ");
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] == '\n' || buffer[0] == '\r') return;
    system(buffer);
    goto beginning;
}
