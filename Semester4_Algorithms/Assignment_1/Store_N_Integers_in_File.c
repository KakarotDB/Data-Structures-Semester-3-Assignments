#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main() {
    // variable declaration zone
    int value;
    int n = 0;
    int max = INT_MIN;
    int min = INT_MAX;
    FILE *file = NULL;
    printf("Enter value of n : ");
    scanf("%d", &n);
    srand(time(NULL));
    file = fopen("numbers.txt", "w");
    if (file == NULL) {
        printf("[ERROR] Couldn't write to file!");
        fclose(file);
        return -2;
    }
    for (int i = 0; i < n; i++) {
        value = rand();
        fprintf(file, "%d ", value);
        max = max > value ? max : value;
        min = min < value ? min : value;
    }
    fprintf(file, "\n");
    printf("Successfully wrote to file numbers.txt!\n");
    fclose(file);
    file = fopen("numbers.txt", "r");
    if (file == NULL) {
        printf("[ERROR] Couldn't read file!");
        fclose(file);
        return -3;
    }
    printf("Reading from file numbers.txt : \n");
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%d ", &value) == 1) {
            printf("%d ", value);
        } else {
            printf("\n");
        }
    }
    printf("\n");
    printf("Maximum value = %d\nMinimum value = %d\n", max, min);
    fclose(file);
    return 0;
}
