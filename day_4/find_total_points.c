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
int build_winning_numbers(char * winning_numbers_line, int *winning_numbers);
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
        printf("%s", buf);
    }

    return sum;
}

// int find_card_points(char *input_file_line) {
//     size_t current_offset = 0;
//     size_t line_length = strlen(input_file_line);

//     // advance offset past the game number
//     for (; current_offset < line_length; current_offset++) {
//         if (input_file_line[current_offset] == ':') {
//             break;
//         }
//     }

//     current_offset++; // advance past the ':'

//     for (; current_offset < line_length;) {
//         char digit[2];
//         char color[6];
//         int digit_offset = 0;
//         int color_offset = 0;

//         // loop until you meet a ',' or a ';'.
//         // That is, we are treating each cube color at a time
//         for (; current_offset < line_length && (input_file_line[current_offset] != ',' && input_file_line[current_offset] != ';'); current_offset++) {
//             if (isspace(input_file_line[current_offset])) continue;
//             else if (isdigit(input_file_line[current_offset]))
//                 digit[digit_offset++] = input_file_line[current_offset];
//             else
//                 color[color_offset++] = input_file_line[current_offset];
//         }

//         current_offset++; // advance past the ',' or ';'

//         color[color_offset] = '\0'; // add string terminating null character

//         int num = digit_offset == 1 ? digit[0] - '0' : atoi(digit); // digit can be 1 or two characters. Could be more, but our configuration is two character, so nothing else matters

//         if (strcmp("red", color) == 0) {
//             if (CONFIGURATION.red < num) return false;
//         } else if (strcmp("blue", color) == 0) {
//             if (CONFIGURATION.blue < num) return false;
//         } else
//             if (CONFIGURATION.green < num) return false;
//     }

//     return true;
// }
