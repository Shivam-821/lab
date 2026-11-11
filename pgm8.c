#include <stdio.h>
#include <string.h>

#define N 14
#define FEATURES 4
#define CLASSES 2

char *weather[N][FEATURES] = {
    {"Sunny", "Hot", "High", "Weak"},
    {"Sunny", "Hot", "High", "Strong"},
    {"Overcast", "Hot", "High", "Weak"},
    {"Rain", "Mild", "High", "Weak"},
    {"Rain", "Cool", "Normal", "Weak"},
    {"Rain", "Cool", "Normal", "Strong"},
    {"Overcast", "Cool", "Normal", "Strong"},
    {"Sunny", "Mild", "High", "Weak"},
    {"Sunny", "Cool", "Normal", "Weak"},
    {"Rain", "Mild", "Normal", "Weak"},
    {"Sunny", "Mild", "Normal", "Strong"},
    {"Overcast", "Mild", "High", "Strong"},
    {"Overcast", "Hot", "Normal", "Weak"},
    {"Rain", "Mild", "High", "Strong"}
};

int label[N] = {
    0, 0, 1, 1, 1, 0, 1,
    0, 1, 1, 1, 1, 1, 0
};

char *className[CLASSES] = {"No", "Yes"};

int valueCount[FEATURES] = {3, 3, 2, 2};

int predict(int testIndex) {
    double probability[CLASSES] = {0};
    int classCount[CLASSES] = {0};
    int i, j, c;

    for (i = 0; i < N; i++) {
        if (i != testIndex)
            classCount[label[i]]++;
    }

    int trainSize = N - 1;

    for (c = 0; c < CLASSES; c++) {
        probability[c] = (double)classCount[c] / trainSize;

        for (j = 0; j < FEATURES; j++) {
            int matches = 0;

            for (i = 0; i < N; i++) {
                if (i != testIndex && label[i] == c &&
                    strcmp(weather[i][j], weather[testIndex][j]) == 0) {
                    matches++;
                }
            }

            probability[c] *= (double)(matches + 1) / (classCount[c] + valueCount[j]);
        }
    }

    return probability[1] > probability[0] ? 1 : 0;
}

int main() {
    int i;
    int TP = 0, TN = 0, FP = 0, FN = 0;

    printf("Weather Forecasting Using Naive Bayes\n\n");
    printf("%-10s %-10s %-10s\n", "Record", "Actual", "Predicted");

    for (i = 0; i < N; i++) {
        int predicted = predict(i);

        printf("%-10d %-10s %-10s\n", i + 1, className[label[i]], className[predicted]);

        if (label[i] == 1 && predicted == 1)
            TP++;
        else if (label[i] == 0 && predicted == 0)
            TN++;
        else if (label[i] == 0 && predicted == 1)
            FP++;
        else
            FN++;
    }

    double accuracy = (double)(TP + TN) / N * 100;

    double precision = (TP + FP) ? (double)TP / (TP + FP) * 100 : 0;

    double recall = (TP + FN) ? (double)TP / (TP + FN) * 100 : 0;

    printf("\nAccuracy  = %.2f%%\n", accuracy);
    printf("Precision = %.2f%%\n", precision);
    printf("Recall    = %.2f%%\n", recall);

    return 0;
}