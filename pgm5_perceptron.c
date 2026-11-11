#include <stdio.h>

int main() {

    // NAND gate training data
    float input[4][3] = {
        {1, 0, 0},
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 1}
    };

    int target[4] = {1, 1, 1, 0};

    // Initial weights
    float weight[3] = {0.3, 0.1, 0.1};

    // Learning rate
    float learning_rate = 0.1;

    // Threshold
    float threshold = 0.5;

    // Number of epochs
    int epochs = 8;

    int i, j;

    // Training
    for (i = 0; i < epochs; i++) {

        printf("Number of count is %d\n", i);

        for (j = 0; j < 4; j++) {

            // Calculate weighted sum
            float sum = 0;

            sum = input[j][0] * weight[0]
                + input[j][1] * weight[1]
                + input[j][2] * weight[2];

            printf("Sum is %f\n", sum);

            // Threshold activation function
            int output;

            if (sum >= threshold)
                output = 1;
            else
                output = 0;

            // Calculate error
            int error = target[j] - output;

            printf("Error is %d\n", error);

            // Perceptron learning rule
            for (int k = 0; k < 3; k++) {
                weight[k] = weight[k] + learning_rate * error * input[j][k];
            }

            // Display updated weights
            printf("Weight 0 = %f Weight 1 = %f Weight 2 = %f\n",
                   weight[0], weight[1], weight[2]);
        }
    }

    // Testing
    printf("\nTesting the NAND gate:\n");

    for (i = 0; i < 4; i++) {

        float sum = 0;

        sum = input[i][0] * weight[0]
            + input[i][1] * weight[1]
            + input[i][2] * weight[2];

        int output;

        if (sum >= threshold)
            output = 1;
        else
            output = 0;

        printf("Sum is %f\n", sum);
        printf("The output for test data %d is: %d\n", i, output);
    }

    return 0;
}
