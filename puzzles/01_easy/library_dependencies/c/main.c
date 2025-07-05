#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_DEP 10

typedef struct Data {
    char *lib;
    char **dep;
    int number_dep;
} Data;

int n_imp;
int n_dep;
char **imports;
Data *dependencies;
int deps_len;

void init();
void solve();
int search_lib(char *lib);
void fix();
int cmp(const void *a, const void *b);
void clean();
void debug_imports();
void debug_dependencies();

int main() {
    init();
    solve();
    clean();

    return 0;
}

void init() {
    deps_len = 0;

    // read the imports and save into the imports array
    scanf("%d%*c", &n_imp); 
    imports = (char **)malloc(sizeof(char *) * n_imp);
    
    for (int i = 0; i < n_imp; i++) {
        char import[1025];
        imports[i] = (char *)malloc(sizeof(char) * 1025);

        scanf("%[^\n]%*c", import);

        char *token = strtok(import, " ");
        token = strtok(NULL, " ");
        strcpy(imports[i], token);
    }

    // read the dependencies
    scanf("%d%*c", &n_dep);
    dependencies = (Data *)malloc(sizeof(Data) * n_dep);

    for (int i = 0; i < n_dep; i++) {
        char dependency[1025];

        Data d;
        d.lib = (char *)malloc(sizeof(char) * 1025);
        d.dep = (char **)malloc(sizeof(char *) * MAX_DEP);
        d.number_dep = 0;

        scanf("%[^\n]%*c", dependency);

        char *token = strtok(dependency, " ");
        strcpy(d.lib, token);

        token = strtok(NULL, " ");
        token = strtok(NULL, ",");

        while (token != NULL) {
            char pre[1025];
            
            int j = 0;
            int k = 0;
            if (token[0] == ' ')
                j = 1;
            for (; j < strlen(token); j++)
                pre[k++] = token[j];
            pre[k] = '\0';

            d.dep[d.number_dep] = (char *)malloc(sizeof(char *) * 1025);
            strcpy(d.dep[d.number_dep++], pre);

            token = strtok(NULL, ",");
        }
        dependencies[deps_len++] = d;
    }
}

void solve() {
    bool success = true;
    int index_lib, index_dep;

    for (int i = 0; i < n_imp && success; i++) {
        index_lib = i;
        for (int j = 0; j < deps_len && success; j++) {
            if (strcmp(imports[i], dependencies[j].lib) == 0) {
                for (int k = 0; k < dependencies[j].number_dep && success; k++) {
                    index_dep = search_lib(dependencies[j].dep[k]);
                    if (index_lib < index_dep)
                        success = false;
                }
            }
        }
    }

    if (success) {
        printf("Compiled successfully!\n");
    } else {
        printf("Import error: tried to import %s but %s is required.\n",
            imports[index_lib], imports[index_dep]);
        fix();
    }
}

// returns the index of the library, -1 if not found
int search_lib(char *lib) {
    for (int i = 0; i < n_imp; i++) {
        if (strcmp(lib, imports[i]) == 0)
            return i;
    }
    return -1;
}

// try to fix the import order to satisfy the dependencies
void fix() {
    char **imports_fixed = (char **)malloc(sizeof(char *) * n_imp);
    bool imported[n_imp];
    int index = 0;
    
    for (int i = 0; i < n_imp; i++)
        imported[i] = false;

    qsort(imports, n_imp, sizeof(imports[0]), cmp);

    for (int i = 0; i < n_imp; i++) {
        if (imported[i])
            continue;

        bool success = true;
        for (int j = 0; j < deps_len; j++) {
            if (strcmp(imports[i], dependencies[j].lib) == 0) {
                for (int k = 0; k < dependencies[j].number_dep && success; k++) {
                    int index_dep = search_lib(dependencies[j].dep[k]); 

                    if (!imported[index_dep])
                        success = false;
                }
            }
        }
        if (success) {
            imports_fixed[index] = (char *)malloc(sizeof(char) * 1025);
            strcpy(imports_fixed[index++], imports[i]);
            imported[i] = true;
            i = -1;
        }
    }

    for (int i = 0; i < n_imp; i++) {
        if (!imported[i]) {
            printf("Fatal error: interdependencies.\n");
            return;
        }
    }

    printf("Suggest to change import order:\n");

    for (int i = 0; i < n_imp; i++)
        printf("import %s\n", imports_fixed[i]);
}

int cmp(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void clean() {
    for (int i = 0; i < n_imp; i++)
        free(imports[i]);
    free(imports);

    for (int i = 0; i < deps_len; i++) {
        Data d = dependencies[i];
        free(d.lib);

        for (int j = 0; j < d.number_dep; j++)
            free(d.dep[j]);
        free(d.dep);
    }
    free(dependencies);
}

void debug_imports() {
    fprintf(stderr, "[DEBUG] [ ");

    for (int i = 0; i < n_imp; i++) {
        fprintf(stderr, "%s", imports[i]);

        if (i < n_imp - 1)
            fprintf(stderr, ", ");
    }

    fprintf(stderr, " ]\n");
}

void debug_dependencies() {
    fprintf(stderr, "[DEBUG] {\n");

    for (int i = 0; i < deps_len; i++) {
        Data d = dependencies[i];
        fprintf(stderr, "[DEBUG] \t%s requires [", d.lib);

        for (int j = 0; j < d.number_dep; j++) {
            fprintf(stderr, " %s", d.dep[j]);

            if (j < d.number_dep - 1)
                fprintf(stderr, ", ");
        }
        fprintf(stderr, " ]\n");
    }
    fprintf(stderr, "[DEBUG] }\n");
}
