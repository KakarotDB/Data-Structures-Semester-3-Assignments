#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int *findMatches(char *source, char *pattern, int *match_count) {
    int n = strlen(source);
    int m = strlen(pattern);

    *match_count = 0;

    if (m > n || m == 0)
        return NULL;

    int *results = (int *)malloc(n * sizeof(int));
    // maximum number of matches is n (source = ...., pattern = *, all
    // characters match)

    if (results == NULL) {
        printf("Memory allocation failed");
        return NULL;
    }

    // Sliding window approach
    // iterating upto index n - m

    for (int i = 0; i <= n - m; i++) {
        bool is_match = true;

        for (int j = 0; j < m; j++) {
            char source_Character = source[i + j];
            char pattern_Character = pattern[j];

            if (pattern_Character != '*' &&
                pattern_Character != source_Character) {
                is_match = false;
                break;
            }
        }

        if (is_match) {
            results[*match_count] = i;
            (*match_count)++;
        }
    }
    return results;
}

void printArray(int *a, int n) {
    printf("Array = [");

    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("]");
    printf("\n");
}

int main() {
    char *source = "cdcddcd";
    char *pattern = "cd*";

    printf("Source : %s\n", source);
    printf("Pattern: %s\n", pattern);

    int count = 0;

    int *matches = findMatches(source, pattern, &count);

    if (matches != NULL) {
        printArray(matches, count);
    } else {
        printf("No matches found or invalid input\n");
    }

    free(matches);
    return 0;
}
