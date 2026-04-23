#include <stdio.h>
#include <stdlib.h>
#include <math.h>

float EPSILON = 1e-6;

typedef struct {
    float x, y;
} Coords;

void deleteCoordsArray(Coords arr[], int *n, Coords coord, int index[], int *k);

int main() {
    int n;
    printf("Enter size of coordinate array: ");
    scanf("%d", &n);
    Coords *arr = (Coords *) malloc(n * sizeof(Coords));
    printf("Enter elements of coordinate array: (x, y)\n");
    for (int i = 0; i < n; i++) {
        scanf("%f%f", &arr[i].x, &arr[i].y);
    }
    Coords coord;
    printf("Enter coordinate (x, y) to delete: ");
    scanf("%f%f", &coord.x, &coord.y);
    int k = n;
    int *index = (int *) calloc(k, sizeof(int));
    deleteCoordsArray(arr, &n, coord, index, &k);
    printf("Coordinate array after deleting:\n");
    for (int i = 0; i < n; i++) {
        printf("%g %g\n", arr[i].x, arr[i].y);
    }
    if (k == 0) {
        printf("Can not delete %g %g from the array!", coord.x, coord.y);
    } else {
        printf("Delete %g %g at %d", coord.x, coord.y, index[0]);
        for (int i = 1; i < k; i++) {
            printf(", %d", index[i]);
        }
    }
    free(arr);
    free(index);
    return 0;
}

void deleteCoordsArray(Coords arr[], int *n, Coords coord, int index[], int *k) {
    *k = 0;
    int read = 0, write = 0;
    while (read < *n) {
        if (fabs(arr[read].x - coord.x) < EPSILON && fabs(arr[read].y - coord.y) < EPSILON) index[(*k)++] = read;
        else arr[write++] = arr[read];
        read++;
    }
    *n = write;
}