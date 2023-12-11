#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LINE 1000

int find_sum(char *input_file_name);
int extract_digits(char *line);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sum_digits <input_file_name>\n");
        exit(EXIT_FAILURE);
    }

    int sum_of_digits_in_file = find_sum(argv[1]);
    printf("The sum of all the first and last digits from each line in the file is %i\n", sum_of_digits_in_file);

    return EXIT_SUCCESS;
}

int extract_digits(char *line) {
    int first_digit = -1;
    int last_digit = -1;

    for (size_t i = 0; i < strlen(line); i++) {
        char current = line[i];
        if (isdigit(current)) {
            if (first_digit < 0) {
                first_digit = current;
            }

            last_digit = current;
        }
    }

    char first_and_last_digits[2] = {first_digit, last_digit};

    return atoi(first_and_last_digits);
}

int find_sum(char *input_file_name) {
    FILE *file_ptr = fopen(input_file_name, "r");

    if (file_ptr == NULL) {
        printf("Unable to open %s", input_file_name);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LINE];
    int sum_of_digits = 0;

    while(fgets(buf, MAX_LINE, file_ptr) != NULL) {
        sum_of_digits += extract_digits(buf);
    }

    fclose(file_ptr);

    return sum_of_digits;
}
