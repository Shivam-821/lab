#include <stdio.h>

#define N 4
#define FEATURES 2
#define EPOCHS 100
#define LEARNING_RATE 0.1

typedef struct {
    float x1;
    float x2;
    int label;
} Data;

float dotProduct(float w[], float x[]) {
    float sum = 0;
    for (int i = 0; i < FEATURES; i++) {
        sum += w[i] * x[i];
    }
    return sum;
}

int predict(float w[], float b, float x[]) {
    float result = dotProduct(w, x) + b;
    return (result >= 0) ? 1 : -1;
}

int main() {
    Data trainingData[N] = {
        {2, 3, 1},
        {3, 3, 1},
        {1, 1, -1},
        {2, 1, -1}
    };

    float w[FEATURES] = {0.0, 0.0};
    float b = 0.0;
    float learningRate = LEARNING_RATE;

    float x[FEATURES];
    int prediction;

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        for (int i = 0; i < N; i++) {
            x[0] = trainingData[i].x1;
            x[1] = trainingData[i].x2;

            prediction = predict(w, b, x);

            if (prediction != trainingData[i].label) {
                w[0] += learningRate * trainingData[i].label * x[0];
                w[1] += learningRate * trainingData[i].label * x[1];
                b += learningRate * trainingData[i].label;
            }
        }
    }

    printf("Trained SVM weights:\n");
    printf("w1 = %f, w2 = %f, b = %f\n", w[0], w[1], b);

    printf("\nPredictions on training data:\n");
    for (int i = 0; i < N; i++) {
        x[0] = trainingData[i].x1;
        x[1] = trainingData[i].x2;

        prediction = predict(w, b, x);

        printf("(%.6f, %.6f) -> %d\n",
               x[0], x[1], prediction);
    }

    float testData[][2] = {
        {1.5, 2.0},
        {3.0, 2.0}
    };

    int testSize = sizeof(testData) / sizeof(testData[0]);

    printf("\nPredictions on new points:\n");
    for (int i = 0; i < testSize; i++) {
        prediction = predict(w, b, testData[i]);

        printf("(%.6f, %.6f) -> %d\n",
               testData[i][0], testData[i][1], prediction);
    }

    return 0;
}