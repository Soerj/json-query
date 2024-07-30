#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <path_to_json_file>\n", argv[0]);
        return 1;
    }

    const char *json_file_path = argv[1];
    printf("JSON file path: %s\n", json_file_path);

    return 0;
}
