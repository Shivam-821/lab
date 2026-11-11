#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define K 16
#define SIZE 256
#define ROWS 3
#define COLS 3

int main() {
    int image[ROWS][COLS];
    int centroid[K];
    int oldCentroid[K];
    int cluster[SIZE];
    int sum[K], count[K];
    int i, j, iter, changed;
    int value, minDist, dist, nearest;

    printf("Enter 3x3 grayscale image values (0-255):\n");

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            scanf("%d", &image[i][j]);

            if (image[i][j] < 0 || image[i][j] > 255) {
                printf("Invalid grayscale value!\n");
                return 1;
            }
        }
    }

    for (i = 0; i < K; i++) {
        centroid[i] = 2 + i * 16;
    }

    printf("\nInitial centroids:\n");
    for (i = 0; i < K; i++) {
        printf("%d ", centroid[i]);
    }
    printf("\n");

    do {
        changed = 0;

        for (i = 0; i < K; i++) {
            oldCentroid[i] = centroid[i];
            sum[i] = 0;
            count[i] = 0;
        }

        for (value = 0; value < SIZE; value++) {
            minDist = abs(value - centroid[0]);
            nearest = 0;

            for (i = 1; i < K; i++) {
                dist = abs(value - centroid[i]);

                if (dist < minDist) {
                    minDist = dist;
                    nearest = i;
                }
            }

            cluster[value] = nearest;
            sum[nearest] += value;
            count[nearest]++;
        }

        for (i = 0; i < K; i++) {
            if (count[i] > 0) {
                centroid[i] = (int)round((double)sum[i] / count[i]);
            }

            if (centroid[i] != oldCentroid[i]) {
                changed = 1;
            }
        }

        printf("\n");
        for (i = 0; i < K; i++) {
            printf("%d ", centroid[i]);
        }
        printf("\n");

    } while (changed);

    printf("\nQuantized color (cluster indices 0-15):\n");

    for (i = 0; i < ROWS; i++) {
        for (j = 0; j < COLS; j++) {
            value = image[i][j];

            minDist = abs(value - centroid[0]);
            nearest = 0;

            for (int c = 1; c < K; c++) {
                dist = abs(value - centroid[c]);

                if (dist < minDist) {
                    minDist = dist;
                    nearest = c;
                }
            }

            printf("%d ", nearest);
        }
        printf("\n");
    }

    return 0;
}