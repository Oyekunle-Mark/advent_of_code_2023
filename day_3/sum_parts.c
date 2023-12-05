#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE_LENGTH 1000
#define SQUARE_MATRIX_SIZE 140

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

    for (size_t row = 0; row < SQUARE_MATRIX_SIZE; row++) {
        int digit_index = 0;
        char current_parts_number[3];
        bool is_adjacent_to_a_symbol = false;

        for (size_t col = 0; col < SQUARE_MATRIX_SIZE; col++) {
            if (isdigit(schematic[row][col])) {
                current_parts_number[digit_index++] = schematic[row][col];

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
                    if (digit_index == 3)
                        sum += atoi(current_parts_number);
                    else if (digit_index == 2) {
                        char temp[2] = {current_parts_number[0], current_parts_number[1]};
                        sum += atoi(temp);
                    }
                    else
                        sum += (current_parts_number[0] - '0');
                }
                digit_index = 0;
                is_adjacent_to_a_symbol = false;
            }
        }
    }

    return sum;
}
