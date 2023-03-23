#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#define COLOR_RED     "\033[31m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_MAGENTA "\033[35m"
#define COLOR_YELLOW  "\033[33m"
#define COLOR_RESET   "\033[0m"

typedef struct Set {
    char **strArray;
    int size;
} Set_t;

Set_t add(Set_t, char str[]);
Set_t rm(Set_t set, char str[]);
void printSet(Set_t set);
void printHelp();

int main() {
    Set_t set1;
    set1.size = 0;
    set1.strArray = malloc(set1.size * sizeof (char*));
    Set_t set2;
    set2.size = 0;
    set2.strArray = malloc(set2.size * sizeof (char*));
    printHelp();
    while (1) {
        printf(">>");
        char *cmd = calloc(5, sizeof (char));
        char *arg = calloc(30, sizeof (char));
        int a = 0;

        scanf("%4s", cmd);
        if (strcmp(cmd, "quit") == 0) return 0;
        if (strcmp(cmd, "help") == 0) {printHelp(); continue;}

        scanf("%d", &a);

        if ((strcmp(cmd, "prnt") == 0) && (a == 1)){printSet(set1); continue;}
        if ((strcmp(cmd, "prnt") == 0) && (a == 2)){printSet(set2); continue;}

        scanf("%30s", arg);

        if ((strcmp(cmd, "add") == 0) && (a == 1)) {set1 = add(set1, arg); continue;}
        if ((strcmp(cmd, "add") == 0) && (a == 2)) {set2 = add(set2, arg); continue;}

        if ((strcmp(cmd, "rm") == 0) && (a == 1)) {set1 = rm(set1, arg); continue;}
        if ((strcmp(cmd, "rm") == 0) && (a == 2)) {set2 = rm(set2, arg); continue;}
        printf(COLOR_RED"ehh??\n"COLOR_RESET);
    }
    return 0;
}

Set_t add(Set_t set, char str[]) {
    for (int i = 0; i < set.size; ++i) {
        if (strcmp(set.strArray[i], str) == 0) {
            printf(COLOR_RED"The %s is already in the set\n"COLOR_RESET, str);
            return set;
        }
    }
    int numberOfLetters = (int)strlen(str);
    set.size += 1;
    set.strArray = realloc(set.strArray, set.size * sizeof(char *));
    set.strArray[set.size-1] = malloc(numberOfLetters * sizeof(char));
    set.strArray[set.size-1] = str;
    printf("success\n");
    return set;
}
Set_t rm(Set_t set, char str[]) {
    bool found = false;
    for (int i = 0; i < set.size; ++i) {
        if (strcmp(set.strArray[i], str) == 0) {
            for (int j = i; j < set.size-1; j++) {
                //for some yet unknown reason both realloc() and free() refer the program to a forbidden segment of memory
                //but idc as long as it works with just malloc()
                set.strArray[j] = malloc(strlen(set.strArray[j+1]) * sizeof(char));
                set.strArray[j] = set.strArray[j+1];
            }
            found = true;
            break;
        }
    }
    if (found) {
        set.size--;
        set.strArray = realloc(set.strArray, set.size * sizeof(char*));
        printf("success\n");
    }
    else printf(COLOR_RED"%s is not found; cannot rm\n"COLOR_RESET, str);
    return set;

}
void printSet(Set_t set) {
    printf(COLOR_MAGENTA"The elements of the set are: "COLOR_RESET);
    for (int i = 0; i < set.size; i++) printf(COLOR_GREEN"%s; "COLOR_RESET, set.strArray[i]);
    printf("\n");
}

void printHelp() {
    printf(COLOR_YELLOW);
    printf("USAGE: [cmd] [arg1] [arg2]\n");
    printf("add [set No.] [element]\n");
    printf("rm [set No.] [element]\n");
    printf("prnt [set No.]\n");
    printf("help\n");
    printf("quit\n");
    printf(COLOR_RESET);
}