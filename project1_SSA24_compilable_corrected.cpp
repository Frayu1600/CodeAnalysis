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
    size_t MAX_SIZE = 1024;      // can be adjusted
    size_t len = strlen(src);

    // check on maximum length 
    if(len > MAX_SIZE) {
        len = MAX_SIZE;
        src[len] = '\0';
    }

    char dst[len * sizeof(char) + 1];   // put +1 at the end for more clarity
    strncpy(dst, src, strlen(src));     // removed "+ sizeof(char)"
    dst[len] = '\0';                    // instead of strlen(dst)
}

// changed int fd into size_t fd
void func2(size_t fd) { 
    char* buf;
    size_t len;
    // checking partial read
    size_t n = read(fd, &len, sizeof(len)); 
    if (n != sizeof(len)) {
        return;
    }

    if (len > 1024) {
        return;
    }

    buf = (char*)malloc(len+1);     // (char*) to make it compilable
    // checking malloc failure 
    if(!buf) {
        return;
    }

    // checking partial read
    n = read(fd, buf, len); 
    if (n != len) {
        free(buf);
        return;
    }
    buf[len] = '\0';

    // added heap free
    free(buf);
}

void func3() {	
    // added size variable to make couting easier and more reliable
    const size_t BUF_SIZE = 1024;
    char buffer[BUF_SIZE];
    
    printf("Please enter your user id :");
    fgets(buffer, BUF_SIZE-1, stdin);
    buffer[BUF_SIZE-1] = '\0';

    if (!isalpha(buffer[0])) {   
        // added to be sure of not failing the count 
        const char* is_not_valid_ID = " is not  a valid ID";
        const size_t errormsg_len = BUF_SIZE + strlen(is_not_valid_ID) + 1;

        printf("%ld\n", errormsg_len);
        char errormsg[1044];  // does not need +1

        strncpy(errormsg, buffer, BUF_SIZE);   
        strcat(errormsg, is_not_valid_ID);          // is fine because is null-terminated
        throw errormsg;                             // added otherwise doesnt make sense
    }
}

void func4(char *foo) {
    // added this variable 
    const size_t BUF_SIZE = 10;
    char *buffer = (char *)malloc(BUF_SIZE * sizeof(char));

    // copies at most 10 bytes
    strncpy(buffer, foo, BUF_SIZE);   
    buffer[BUF_SIZE-1] = '\0';        // added string terminator 
    printf("%s\n", buffer); 
}

int main() {
    int i=10;       // renamed into i for better understanding
    int a[10];

    // this does not cause malloc to crash anymore
    func4("fooooooooooooooooooooooooooooooooooooooooooooooooooo");

    try { 
        func3();
    }
    catch(char* message){	
        fprintf(stderr, "%s", message);       // added "%s" string modifier 
    }
    
    // aFile not declared
    //fprintf(aFile, "%s", "hello world");
 
    while (i>=0) {  
        a[i--]=i;   // removed y=y-1 and added postdecrement     
    }
    return 0;
}