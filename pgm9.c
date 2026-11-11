#include <stdio.h>

int main() {
    int actual[] = {1, 0, 1, 1, 0, 1, 0, 0, 1, 0};
    int predicted[] = {1, 0, 0, 1, 1, 1, 0, 0, 1, 0};

    int n = sizeof(actual) / sizeof(actual[0]);

    int TP = 0, TN = 0, FP = 0, FN = 0;

    for (int i = 0; i < n; i++) {
        if (actual[i] == 1 && predicted[i] == 1)
            TP++;
        else if (actual[i] == 0 && predicted[i] == 0)
            TN++;
        else if (actual[i] == 0 && predicted[i] == 1)
            FP++;
        else if (actual[i] == 1 && predicted[i] == 0)
            FN++;
    }

    float accuracy = ((float)(TP + TN) / n) * 100;

    printf("Confusion Matrix:\n");
    printf("                 Predicted\n");
    printf("                 0      1\n");
    printf("Actual     0     %d      %d\n", TN, FP);
    printf("           1     %d      %d\n", FN, TP);

    printf("\nTrue Positive (TP): %d\n", TP);
    printf("True Negative (TN): %d\n", TN);
    printf("False Positive (FP): %d\n", FP);
    printf("False Negative (FN): %d\n", FN);
    printf("Accuracy: %.2f%%\n", accuracy);

    return 0;
}