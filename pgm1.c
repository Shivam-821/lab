#include <stdio.h>

int main() {
    int n, epochs;
    double learningRate;

    printf("Linear Regression using Gradient Descent\n");
    printf("----------------------------------------\n");

    // Input number of data points
    printf("Enter number of data points: ");
    scanf("%d", &n);

    double X[n], Y[n];

    // Input data
    printf("Enter X and Y values:\n");
    for (int i = 0; i < n; i++) {
        printf("Data %d (X Y): ", i + 1);
        scanf("%lf %lf", &X[i], &Y[i]);
    }

    // Input learning rate and epochs
    printf("Enter Learning Rate: ");
    scanf("%lf", &learningRate);

    printf("Enter Number of Epochs: ");
    scanf("%d", &epochs);

    // Initialize weight and bias to zero
    double weight = 0.0;
    double bias = 0.0;

    // Batch Gradient Descent
    for (int epoch = 1; epoch <= epochs; epoch++) {

        double dw = 0.0;
        double db = 0.0;
        double mse = 0.0;

        // Calculate gradients using the complete dataset
        for (int i = 0; i < n; i++) {

            // Prediction
            double yPred = weight * X[i] + bias;

            // Error
            double error = yPred - Y[i];

            // Accumulate gradients
            dw += error * X[i];
            db += error;

            // MSE
            mse += error * error;
        }

        // Average gradients
        dw = (2.0 / n) * dw;
        db = (2.0 / n) * db;

        mse = mse / n;

        // Update weight and bias
        weight = weight - learningRate * dw;
        bias = bias - learningRate * db;

        // Display MSE
        printf("Epoch %d MSE = %.6f\n", epoch, mse);
    }

    // Final results
    printf("----------------------------------------\n");
    printf("Training Completed Successfully\n");
    printf("----------------------------------------\n");

    printf("Final Weight (Slope) = %.4f\n", weight);
    printf("Final Bias (Intercept) = %.4f\n", bias);

    printf("Regression Equation:\n");
    printf("Y = %.4fX + %.4f\n", weight, bias);

    printf("---------------------------------------------\n");
    printf("X Actual Y Predicted Y\n");
    printf("---------------------------------------------\n");

    double finalMSE = 0.0;

    // Display predictions
    for (int i = 0; i < n; i++) {
        double yPred = weight * X[i] + bias;
        double error = yPred - Y[i];

        finalMSE += error * error;

        printf("%.2f %.2f %.2f\n", X[i], Y[i], yPred);
    }

    // Calculate final MSE
    finalMSE = finalMSE / n;

    printf("---------------------------------------------\n");
    printf("Final Mean Squared Error (MSE) = %.6f\n", finalMSE);

    return 0;
}
