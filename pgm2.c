#include <stdio.h>

int main() {
    int n, epochs;
    double learningRate;

    printf("Weighted Linear Regression using Gradient Descent\n");
    printf("--------------------------------------------------\n");

    printf("Enter number of data points: ");
    scanf("%d", &n);

    double X[n], Y[n], W[n];

    printf("Enter X, Y and Weight values:\n");

    for (int i = 0; i < n; i++) {
        printf("Data %d (X Y Weight): ", i + 1);
        scanf("%lf %lf %lf", &X[i], &Y[i], &W[i]);
    }

    printf("Enter Learning Rate: ");
    scanf("%lf", &learningRate);

    printf("Enter Number of Epochs: ");
    scanf("%d", &epochs);

    // Model parameters
    double slope = 0.0;
    double bias = 0.0;

    printf("\nTraining Started...\n");

    for (int epoch = 1; epoch <= epochs; epoch++) {

        double dw = 0.0;
        double db = 0.0;
        double wmse = 0.0;
        double totalWeight = 0.0;

        // Calculate gradients and WMSE
        for (int i = 0; i < n; i++) {

            double predicted = slope * X[i] + bias;
            double error = predicted - Y[i];

            // Weighted gradients
            dw += W[i] * error * X[i];
            db += W[i] * error;

            // Weighted squared error
            wmse += W[i] * error * error;
            totalWeight += W[i];
        }

        // Average gradients
        dw = (2.0 / totalWeight) * dw;
        db = (2.0 / totalWeight) * db;

        // Update parameters
        slope -= learningRate * dw;
        bias -= learningRate * db;

        // Calculate WMSE
        wmse = wmse / totalWeight;

        printf("Epoch %d WMSE = %.6f\n", epoch, wmse);
    }

    printf("----------------------------------------\n");
    printf("Training Completed Successfully\n");
    printf("----------------------------------------\n");

    printf("Final Weight (Slope) = %.4f\n", slope);
    printf("Final Bias (Intercept) = %.4f\n", bias);

    printf("Regression Equation:\n");
    printf("Y = %.4fX + %.4f\n", slope, bias);

    printf("--------------------------------------------------\n");
    printf("X\tActual Y\tWeight\tPredicted Y\n");
    printf("--------------------------------------------------\n");

    double finalWMSE = 0.0;
    double totalWeight = 0.0;

    for (int i = 0; i < n; i++) {

        double predicted = slope * X[i] + bias;
        double error = predicted - Y[i];

        finalWMSE += W[i] * error * error;
        totalWeight += W[i];

        printf("%.2f\t%.2f\t\t%.2f\t%.2f\n",
               X[i], Y[i], W[i], predicted);
    }

    finalWMSE /= totalWeight;

    printf("--------------------------------------------------\n");
    printf("Final Weighted Mean Squared Error (WMSE) = %.6f\n",
           finalWMSE);

    return 0;
}
