#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define SQUARE_MATRIX_SIZE 10

bool is_symbol(char c);
void build_schematic(char *input_file_name, char schematic[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE]);
int part_sum(char schematic[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE]);

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sum_parts <input_file>\n");
        exit(EXIT_FAILURE);
    }

    char schematic[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE];
    build_schematic(argv[1], schematic);

    // int i,j,row,col;

    for (int i = 0; i < SQUARE_MATRIX_SIZE; i++) {
        for (int j = 0; j < SQUARE_MATRIX_SIZE; j++) {
            // schematic[i][j] = '.';
            printf("%c ", schematic[i][j]);
        }
        printf("\n");
    }


    int result = part_sum(schematic);

    printf("The sum of the parts numbers in the schematic is %i\n", result);

    return EXIT_SUCCESS;
}

bool is_symbol(char c) {
    if (isdigit(c) || c == '.') return false;

    return true;
}

void build_schematic(char *input_file_name, char schematic[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE]) {
    FILE *file_ptr = fopen(input_file_name, "r");

    if (file_ptr == NULL) {
        printf("Cannot open %s\n", input_file_name);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LINE_LENGTH];
    size_t index = 0;

    while((fgets(buf, MAX_LINE_LENGTH, file_ptr)) != NULL) {
        strcpy(schematic[index++], buf);
    }

    // printf("Schematic has length %lu\n", index);
    // printf("line 1 is %c\n", schematic[139][141]);
}

int part_sum(char schematic[SQUARE_MATRIX_SIZE][SQUARE_MATRIX_SIZE]) {
    int sum = 0;

    for (int row = 0; row < SQUARE_MATRIX_SIZE; row++) {
        int digit_index = 0;
        char current_parts_number[4];
        bool is_adjacent_to_a_symbol = false;

        for (int col = 0; col < SQUARE_MATRIX_SIZE; col++) {
            if (isdigit(schematic[row][col])) {
                current_parts_number[digit_index++] = schematic[row][col];
                printf("current part number is %c\n", schematic[row][col]);

                // we want to check in all adjacent direction for a symbol. We conditionally  only set is_adjacent_to_a_symbol
                // to true only if is_symbol returns true to prevent overwriting a previous check with false
                if (row > 0) {
                    is_adjacent_to_a_symbol = is_symbol(schematic[row - 1][col]) ? true : is_adjacent_to_a_symbol; // up
                    if (col > 0)
                        is_adjacent_to_a_symbol = is_symbol(schematic[row - 1][col - 1]) ? true : is_adjacent_to_a_symbol; // upper left diagonal
                    if (col < SQUARE_MATRIX_SIZE - 1)
                        is_adjacent_to_a_symbol = is_symbol(schematic[row - 1][col + 1]) ? true : is_adjacent_to_a_symbol; // upper right diagonal
                }
                if (row < SQUARE_MATRIX_SIZE - 1) {
                    is_adjacent_to_a_symbol = is_symbol(schematic[row + 1][col]) ? true : is_adjacent_to_a_symbol; // down
                    if (col > 0)
                        is_adjacent_to_a_symbol = is_symbol(schematic[row + 1][col - 1]) ? true : is_adjacent_to_a_symbol; // lower left diagonal
                    if (col < SQUARE_MATRIX_SIZE - 1)
                        is_adjacent_to_a_symbol = is_symbol(schematic[row + 1][col + 1]) ? true : is_adjacent_to_a_symbol; // lower right diagonal
                }
                if (col > 0) {
                    is_adjacent_to_a_symbol = is_symbol(schematic[row][col - 1]) ? true : is_adjacent_to_a_symbol; // left
                }
                if (col < SQUARE_MATRIX_SIZE - 1) {
                    is_adjacent_to_a_symbol = is_symbol(schematic[row][col + 1]) ? true : is_adjacent_to_a_symbol; // right
                }
            } else {
                if (digit_index > 0 && is_adjacent_to_a_symbol) {
                    int previous_num = -1;

                    if (digit_index == 3) {
                        // char temp[3] = {current_parts_number[0], current_parts_number[1], current_parts_number[2]};
                        current_parts_number[3] = '\0';
                        previous_num = atoi(current_parts_number);
                    }
                    else if (digit_index == 2) {
                        char temp[3] = {current_parts_number[0], current_parts_number[1], '\0'};
                        previous_num = atoi(temp);
                    }
                    else if (digit_index == 1)
                        previous_num = (current_parts_number[0] - '0');
                    // else
                    //     printf("digit index is %i\n", digit_index);

                    printf("digit index is %i, previous num is %i\n", digit_index, previous_num);
                    sum += previous_num;
                }

                digit_index = 0;
                is_adjacent_to_a_symbol = false;
            }
        }
    }

    return sum;
}
