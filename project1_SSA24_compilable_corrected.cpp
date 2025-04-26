#include <stdlib.h> // added 
#include <string.h>
#include <stdio.h>
#include <ctype.h>  // added 
#include <unistd.h> // added 

void func1(char *src) {
    // checking if null 
    if(!src) {
        return;
    }

    // added maximum length for security 
    const size_t MAX_SIZE = 1024;       
    // function assumes src is null terminated
    size_t len = strlen(src);           // Flawfinder: ignore

    // check on maximum length 
    if(len > MAX_SIZE) {
        len = MAX_SIZE;
        src[MAX_SIZE-1] = '\0';
    }

    // added +1 for more clarity and removed char
    char dst[len+1];                    // Flawfinder: ignore
    // removed "+ sizeof(char)"
    strncpy(dst, src, len);             // Flawfinder: ignore
    dst[len] = '\0';                    // instead of strlen(dst)
}

// changed "int fd" into "size_t fd"
void func2(size_t fd) { 
    // added maximum length for security
    const size_t MAX_SIZE = 1024;       
    char* buf;
    size_t len;

    // checking partial read
    size_t n = read(fd, &len, sizeof(len));     // Flawfinder: ignore
    if (n != sizeof(len)) {
        return;
    }
    if (len > MAX_SIZE) {
        return;
    }

    buf = (char*)malloc(len+1);     // (char*) to make it compilable
    // checking malloc failure 
    if(!buf) {
        return;
    }

    // checking partial read
    n = read(fd, buf, len);         // Flawfinder: ignore
    if (n != len) {
        free(buf);
        return;
    }
    buf[len] = '\0';
    free(buf);
}

void func3() {	
    // added size variable to make couting easier and more reliable
    const size_t BUF_SIZE = 1024;
    char buffer[BUF_SIZE];                          // Flawfinder: ignore
    
    printf("Please enter your user id :");
    if(!fgets(buffer, BUF_SIZE, stdin)) {
        // in case of error
        exit(1);
    }
    // buffer is already string terminated 
    // here we substitute \n with string terminator instead
    buffer[strlen(buffer)-1] = '\0';                // Flawfinder: ignore        

    if (!isalpha(buffer[0])) {   
        // added to be sure of not failing the count 
        const char* is_not_valid_ID = " is not  a valid ID"; 

        // changed into malloc() to allow for variable length array
        // it is to avoid counting strlen(is_not_valid_ID) manually
        // not actually a vulnerability, it is to avoid a bad practice 
        char *errormsg = (char *)malloc(BUF_SIZE + strlen(is_not_valid_ID) + 1);    // Flawfinder: ignore 
        if(!errormsg) {
            exit(1);
        }

        // may not copy string terminator, added for good practice
        strncpy(errormsg, buffer, BUF_SIZE-1);        // Flawfinder: ignore
        errormsg[BUF_SIZE-1] = '\0';
        // this is fine because is_not_valid_ID is null terminated and strcat attaches it
        strcat(errormsg, is_not_valid_ID);            // Flawfinder: ignore
        // added otherwise function doesnt make sense
        throw errormsg;                             

        free(errormsg);
    }
}

void func4(char *foo) {
    // checking if null 
    if(!foo) {
        return;
    }

    // added size variable to make couting easier and more reliable
    const size_t BUF_SIZE = 10;
    char *buffer = (char *)malloc(BUF_SIZE * sizeof(char));
    // checking malloc failure 
    if(!buffer) {
        return;
    }

    // copies at most 10 bytes
    strncpy(buffer, foo, BUF_SIZE-1);   // Flawfinder: ignore
    buffer[BUF_SIZE-1] = '\0';          // added string terminator

    free(buffer);
}

int main() {
    int i=10;       // renamed into i for better understanding
    int a[10];

    // does not cause malloc to crash anymore
    func4("fooooooooooooooooooooooooooooooooooooooooooooooooooo");

    try { 
        func3();
    }
    catch(char* message){	
        fprintf(stderr, "%s\n", message);       // added "%s" string modifier 
    }
    
    // aFile not declared
    //fprintf(aFile, "%s", "hello world");
 
    // added predecrement
    while (--i>=0) {  
        a[i]=i;
    }
    return 0;
}