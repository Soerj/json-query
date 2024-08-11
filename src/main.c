#include <stdio.h>
#include <string.h>
#include <json-c/json.h>
#include <sys/stat.h>

void add(json_object *root, const char *jsonPath, const char *value) {
    json_object *obj = json_object_new_object();
    json_object_object_add(obj, "new_key", json_object_new_string(value));
    json_object_object_add(root, jsonPath, obj);
}

void update(json_object *root, const char *jsonPath, const char *value) {
    json_object *obj = json_object_object_get(root, jsonPath);
    printf("input Json: %p \n", (void*)root);
    if (!obj) {
        fprintf(stderr, "Error: JSONPath not found: %s\n", jsonPath);
        return;
    }

    enum json_type type = json_object_get_type(obj);
    switch (type) {
        case json_type_string:
            json_object_set_string(obj, value);
            break;
        case json_type_int:
            json_object_set_int(obj, atoi(value));
            break;
        case json_type_double:
            json_object_set_double(obj, atof(value));
            break;
        case json_type_boolean:
            json_object_set_boolean(obj, strcmp(value, "true") == 0);
            break;
        default:
            fprintf(stderr, "Error: Unsupported type for update\n");
    }
}

void delete(json_object *root, const char *jsonPath) {
    json_object *obj = json_object_object_get(root, jsonPath);

    if (!obj) {
        fprintf(stderr, "Error: JSONPath not found: %s\n", jsonPath);
        return;
    }

    json_object_object_del(root, jsonPath);
}

int main(int argc, char *argv[]) {
    if (argc < 4 || argc > 5) {
        fprintf(stderr, "Usage: %s path command jsonPath [value]\n", argv[0]);
        return 1;
    }

    const char *path = argv[1];
    const char *command = argv[2];
    const char *jsonPath = argv[3];
    const char *value = argc == 5 ? argv[4] : NULL;

    printf("Command: %p/n", path);

    // Read Json File
    struct stat st;
    stat(path, &st);
    char *file_contents = (char*)malloc(st.st_size + 1);
    FILE *fp = fopen(path, "r");
    fread(file_contents, st.st_size, 1, fp);
    fclose(fp);
    file_contents[st.st_size] = '\0';

    // Parse Json
    struct json_object *root = json_tokener_parse(file_contents);
    free(file_contents);

    // Execute Command
    if (strcmp(command, "add") == 0) {
        add(root, jsonPath, value);
    } else if (strcmp(command, "update") == 0) {
        update(root, jsonPath, value);
    } else if (strcmp(command, "delete") == 0) {
        delete(root, jsonPath);
    } else {
        fprintf(stderr, "Invalid command: %s\n", command);
        return 1;
    }

    // Save
    char *new_json = json_object_to_json_string(root);
    fp = fopen(path, "w");
    fwrite(new_json, strlen(new_json), 1, fp);
    fclose(fp);
    free(new_json);

    json_object_put(root);
    return 0;
}
