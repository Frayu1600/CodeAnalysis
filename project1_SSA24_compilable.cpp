#include <stdlib.h> // added 
#include <string.h>
#include <stdio.h>
#include <ctype.h>  // added 
#include <unistd.h> // added 

void func1(char *src) {
    char dst[(strlen(src) + 1) * sizeof(char)];
    strncpy(dst, src, strlen(src) + sizeof(char));
    dst[strlen(dst)] = 0;
}

void func2(int fd) {
    char* buf;
    size_t len;
    read(fd, &len, sizeof(len));

    if (len > 1024) 
        return;

    buf = (char*)malloc(len+1);     // made this (char*) to make it compilable
    read(fd, buf, len); 
    buf[len] = '\0';
}

void func3() {	
    char buffer[1024];
    printf("Please enter your user id :");
    fgets(buffer, 1024, stdin);

    if (!isalpha(buffer[0])) {   
        char errormsg[1044]; 
        strncpy(errormsg, buffer,1024);   
        strcat(errormsg, " is not  a valid ID");
        throw errormsg;                             // added otherwise doesnt make sense
    }
}

void func4(char *foo) {
    char *buffer = (char *)malloc(10 * sizeof(char));
    strcpy(buffer, foo);    // 1. easy heap BoF!
}

int main() {
    int y=10;
    int a[10];

    // this causes malloc to explode
    //func4("fooooooooooooooooooooooooooooooooooooooooooooooooooo");

    func2(0);

    try { 
        func3();
    }
    catch(char *message){	
        fprintf(stderr, message);       // 2. easy format string!
    }
    
    // aFile not declared
    //fprintf(aFile, "%s", "hello world");

    while (y>=0) {  
        a[y]=y;     
        y=y-1;
    }
    return 0;
}