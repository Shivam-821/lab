#include <stdio.h>
#include <math.h>

#define N 10
#define FEATURES 3
#define MAX_ITER 100000

// Training dataset
// Features: Height, Weight, Foot Size
// Label: 1 = Male, 0 = Female

double X[N][FEATURES] = {
    {6.0, 77, 12},
    {5.9, 75, 11},
    {5.8, 70, 10},
    {5.7, 68, 10},
    {5.5, 65, 9},
    {5.4, 60, 8},
    {5.3, 58, 8},
    {5.2, 55, 7},
    {5.1, 52, 7},
    {5.0, 50, 6}
};

int Y[N] = {
    1, 1, 1, 1, 1,
    0, 0, 0, 0, 0
};


// Sigmoid function
double sigmoid(double z) {
    return 1.0 / (1.0 + exp(-z));
}


// Calculate cost
double calculateCost(double weights[], double bias) {
    double cost = 0.0;

    for (int i = 0; i < N; i++) {

        double z = bias;

        for (int j = 0; j < FEATURES; j++) {
            z += weights[j] * X[i][j];
        }

        double prediction = sigmoid(z);

        // Avoid log(0)
        if (prediction < 1e-15)
            prediction = 1e-15;

        if (prediction > 1 - 1e-15)
            prediction = 1 - 1e-15;

        cost += - (Y[i] * log(prediction) + (1 - Y[i]) * log(1 - prediction));
    }

    return cost / N;
}


int main() {
    double weights[FEATURES] = {0.0, 0.0, 0.0};
    double bias = 0.0;

    double learningRate = 0.0001;

    printf("============================================\n");
    printf(" LOGISTIC REGRESSION TRAINING\n");
    printf("============================================\n");

    printf("Learning Rate: %f\n", learningRate);

    // -------------------------------
    // Gradient Descent
    // -------------------------------

    for (int iteration = 0; iteration < MAX_ITER; iteration++) {

        double dw[FEATURES] = {0.0, 0.0, 0.0};
        double db = 0.0;

        for (int i = 0; i < N; i++) {

            // Calculate z
            double z = bias;

            for (int j = 0; j < FEATURES; j++) {
                z += weights[j] * X[i][j];
            }

            // Prediction
            double prediction = sigmoid(z);

            // Error
            double error = prediction - Y[i];

            // Gradient for weights
            for (int j = 0; j < FEATURES; j++) {
                dw[j] += error * X[i][j];
            }

            // Gradient for bias
            db += error;
        }

        // Average gradients
        for (int j = 0; j < FEATURES; j++) {
            dw[j] /= N;
        }

        db /= N;

        // Update weights
        for (int j = 0; j < FEATURES; j++) {
            weights[j] -= learningRate * dw[j];
        }

        // Update bias
        bias -= learningRate * db;
    }

    printf("Training Complete.\n");

    printf("Optimal Weights:\n");
    printf("Bias = %.6f\n", bias);
    printf("Height = %.6f\n", weights[0]);
    printf("Weight = %.6f\n", weights[1]);
    printf("Foot Size = %.6f\n", weights[2]);

    // -------------------------------
    // Prediction
    // -------------------------------

    double height, weight, footSize;

    printf("\nEnter details for prediction:\n");

    printf("Enter Height (feet): ");
    scanf("%lf", &height);

    printf("Enter Weight (kg): ");
    scanf("%lf", &weight);

    printf("Enter Foot Size: ");
    scanf("%lf", &footSize);

    // Calculate linear combination
    double z = bias
             + weights[0] * height
             + weights[1] * weight
             + weights[2] * footSize;

    // Probability
    double probability = sigmoid(z);

    printf("Probability of Male: %.6f\n", probability);

    // Threshold = 0.5
    if (probability >= 0.5) {
        printf("Predicted Gender: Male\n");
    } else {
        printf("Predicted Gender: Female\n");
    }

    return 0;
}
