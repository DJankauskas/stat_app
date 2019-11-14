#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <math.h>

void print_file_size(long int size) {
    if (size >= 1000000000) {
        printf("%.2lfGB", size / 1000000000.0);
    }
    else if(size >= 1000000) {
        printf("%.2lfMB", size / 1000000.0);
    }
    else if(size >= 1000) {
        printf("%.2lfKB", size / 1000.0);
    }
    else {
        printf("%ldB", size);
    }
}

void terminate_at_newline(char *str) {
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '\n') {
            str[i] = '\0';
            return;
        }
    }
}

void print_perms(int perms) {
    printf("%c%c%c", perms & 4 ? 'r' : '-', perms & 2 ? 'w' : '-', perms & 1 ? 'x' : '-');
}

int main() {
    struct stat file_info;
    printf("Enter file path: ");
    char input[10000];
    fgets(input, sizeof input, stdin);

    //ensure null termination
    input[9999] = '\0';
    terminate_at_newline(input);

    printf("Get %s file info:\n", input);
    if (stat(input, &file_info) < 0) {
        printf("Encountered error %d: %s.\n", errno, strerror(errno));
        return 1;
    }

    printf("Size: ");
    print_file_size(file_info.st_size);

    int others_perms = file_info.st_mode & 7; //7 == 0b000000111
    int group_perms = (file_info.st_mode & 56) >> 3; //56 == 0b000111000
    int owner_perms = (file_info.st_mode & 448) >> 6; //448 == 0b111000000

    printf("\nPermissions: -");
    print_perms(owner_perms);
    print_perms(group_perms);
    print_perms(others_perms);

    printf("\nTime last accessed: %s\n", ctime(&file_info.st_atime));

}