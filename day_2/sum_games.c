#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


#define MAX_LINE 1000


typedef struct game_set {
    int red;
    int blue;
    int green;
} game_s_t;


int find_game_sum(char *input_file);
game_s_t *build_game_sets(char *input_file_line);
bool is_possible(game_s_t *combination, game_s_t *game_sets);


int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: ./sum_games <input_file>\n");
        exit(EXIT_FAILURE);
    }

    find_game_sum(argv[1]);

    return EXIT_SUCCESS;
}

int find_game_sum(char *input_file) {
    FILE* file_ptr = fopen(input_file, "r");

    if (file_ptr == NULL) {
        printf("Unable to open %s\n", input_file);
        exit(EXIT_FAILURE);
    }

    char buf[MAX_LINE];

    while((fgets(buf, MAX_LINE, file_ptr)) != NULL) {
        printf("%s", buf);
    }

    return 1;
}
