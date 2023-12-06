#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 1000
#define WINNING_NUMBERS_SIZE 5
#define PREDICTED_NUMBERS_SIZE 8


int find_total_points(char *input_file);
int find_card_points(char *input_file_line);
void build_winning_numbers(char * winning_numbers_line, int start_index, int end_index, int *winning_numbers);
bool arr_contains(int *numbers, int num, int num_of_ele);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./find_total_points <input_file>\n");
        exit(EXIT_FAILURE);
    }

    int sum = find_total_points(argv[1]);
    printf("Sum of all valid game numbers is %i\n", sum);

    return EXIT_SUCCESS;
}

int find_total_points(char *input_file) {
    FILE* file_ptr = fopen(input_file, "r");

    if (file_ptr == NULL) {
        printf("Unable to open %s\n", input_file);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LINE];
    int sum = 0;

    while((fgets(buf, MAX_LINE, file_ptr)) != NULL) {
        // printf("%s", buf);
        find_card_points(buf);
    }

    return sum;
}

bool arr_contains(int *numbers, int num, int num_of_ele) {
    for (int i = 0; i < num_of_ele; i++)
        if (numbers[i] == num)
            return true;

    return false;
}

void build_winning_numbers(char *winning_numbers_line, int start_index, int end_pos, int *winning_numbers) {
    char digit[2];
    int digit_offset = 0;
    int w_n_offset = 0;

    for (int i = start_index; i < end_pos; i++) {
        if (isspace(winning_numbers_line[i]) || i == end_pos - 1) {
            if (digit_offset > 0) {
                winning_numbers[w_n_offset++] = digit_offset == 1 ? digit[0] - '0' : atoi(digit);
                digit_offset = 0;
            }
        } else {
            digit[digit_offset++] = winning_numbers_line[i];
        }
    }

    // // reap the last number, if it isn't followed by a space
    // if (digit_offset > 0) {
    //     winning_numbers[w_n_offset++] = digit_offset == 1 ? digit[0] - '0' : atoi(digit);
    //     digit_offset = 0;
    // }
}

int find_card_points(char *input_file_line) {
    size_t current_offset = 0;
    size_t line_length = strlen(input_file_line);

    // advance offset past the card number infomation up to ':'
    for (; current_offset < line_length; current_offset++) {
        if (input_file_line[current_offset] == ':') {
            break;
        }
    }
    current_offset++; // advance past the ':'

    // find '|'
    for (; current_offset < line_length; current_offset++) {
        if (input_file_line[current_offset] == '|') {
            break;
        }
    }

    int winning_numbers[WINNING_NUMBERS_SIZE];
    build_winning_numbers(input_file_line, 0, current_offset, winning_numbers);

    int predictions[PREDICTED_NUMBERS_SIZE];
    build_winning_numbers(input_file_line, current_offset + 1, line_length, predictions);

    printf("winning number");
    for (int i = 0; i < WINNING_NUMBERS_SIZE; i++)
        printf("%i ", winning_numbers[i]);

    printf("predictions");
    for (int i = 0; i < PREDICTED_NUMBERS_SIZE; i++)
        printf("%i ", predictions[i]);

    return true;
}
