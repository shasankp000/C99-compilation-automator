
#include<stdio.h>
#include<stdlib.h>
#include<Windows.h>

#define MAX_OUTPUT_LENGTH 1024 // error output buffer

int main() {
    char filename[101]; // filename buffer
    char command1[201]; // command1 buffer
    char command2[101]; // command2 buffer

    printf("Enter filename(without extension) to compile: ");
    scanf("%s", &filename);

    sprintf(command1, "gcc -std=c99 %s.c -o %s", filename, filename);
    sprintf(command2, "%s.exe", filename);

    // printf("%s \n", command1);
    // printf("%s \n", command2);

    int status1 = system(command1);

    if (status1 == 1) {

        int error_printed = 0;

        FILE *fp = popen(command1, "r"); //opens a pipe to the process and returns a FILE pointer which can be used to read or write to the process.
        char buffer[MAX_OUTPUT_LENGTH];
        while (fgets(buffer, sizeof(buffer), fp) != NULL) { // fgets is used to read text from a file stream (pipe in this case.). It checks whether the output buffer is empty or not.
            if (error_printed == 0 && strstr(buffer, "error")) {
                printf("%s", buffer);
                error_printed = 1;

                // prevents from printing the error more than once.
            }
        }
        pclose(fp); // closes the pipe.

        printf("Compilation failed. Please check your code.");

        return 1;
        
    }

    else {
        system("cls");

        printf("Compilation Successful! \n");

        Sleep(3000); // delay for 3 seconds so as to read the message.

        printf("Running program.....\n");

        Sleep(2000); // delay for 3 seconds so as to read the message.

        system("cls");

        system(command2);


        return 0;
    }
    
    
}