#include <stdio.h>
#include <stdlib.h>

#define MAX_LINE 1000

int find_sum(char *input_file_name);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sum_digits <input_file_name>\n"); // TODO: Add a make file for easily building the executable
        exit(EXIT_FAILURE);
    }

    find_sum(argv[1]);

    return EXIT_SUCCESS;
}

int find_sum(char *input_file_name) {
    FILE *file_ptr = fopen(input_file_name, "r");

    if (file_ptr == NULL) {
        printf("Unable to open %s", input_file_name);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LINE];

    while(fgets(buf, MAX_LINE, file_ptr) != NULL) {
        printf("%s", buf);
    }

    fclose(file_ptr);
    return 1;
}
