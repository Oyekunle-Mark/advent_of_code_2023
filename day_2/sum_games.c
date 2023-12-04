#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#define MAX_LINE 1000


typedef struct game_set {
    int red;
    int blue;
    int green;
} game_s_t;

game_s_t CONFIGURATION = {
    .red = 12,
    .green = 13,
    .blue = 14
};


int find_game_sum(char *input_file);
bool game_is_valid(char *input_file_line);
bool is_possible(game_s_t **game_sets);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sum_games <input_file>\n");
        exit(EXIT_FAILURE);
    }

    int sum = find_game_sum(argv[1]);
    printf("Sum of all valid game numbers is %i\n", sum);

    return EXIT_SUCCESS;
}

int find_game_sum(char *input_file) {
    FILE* file_ptr = fopen(input_file, "r");

    if (file_ptr == NULL) {
        printf("Unable to open %s\n", input_file);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LINE];
    int game_num = 1;
    int sum = 0;

    while((fgets(buf, MAX_LINE, file_ptr)) != NULL) {
        if (game_is_valid(buf)) {
            // printf("Game %lu is possible\n", game_num);
            sum += game_num;
        }
        game_num++;
        // break;
    }

    return sum;
}

bool game_is_valid(char *input_file_line) {
    size_t current_offset = 0;
    size_t line_length = strlen(input_file_line);

    for (; current_offset < line_length; current_offset++) {
        if (input_file_line[current_offset] == ':') {
            break;
        }
    }

    current_offset++; // advance past the ':'

    for (; current_offset < line_length;) {
        char digit[2];
        char color[6];
        int digit_offset = 0;
        int color_offset = 0;

       for (; current_offset < line_length && (input_file_line[current_offset] != ',' && input_file_line[current_offset] != ';'); current_offset++) {
            if (isspace(input_file_line[current_offset])) continue;
            else if (isdigit(input_file_line[current_offset])) {
                digit[digit_offset++] = input_file_line[current_offset];
            } else {
                color[color_offset++] = input_file_line[current_offset];
            }
        }

        current_offset++; // advance past the ',' or ';'

        color[color_offset] = '\0';

        int num = digit_offset == 1 ? digit[0] - '0' : atoi(digit);

        // printf("color is %s, number is %i\n", color, num);

        if (strcmp("red", color) == 0) {
            if (CONFIGURATION.red < num) return false;
        } else if (strcmp("blue", color) == 0) {
            if (CONFIGURATION.blue < num) return false;
        } else {
            if (CONFIGURATION.green < num) return false;
        }
    }

    return true;
}
