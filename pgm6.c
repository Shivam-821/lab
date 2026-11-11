#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define INPUT 3
#define HIDDEN 4
#define OUTPUT 1
#define N 8
#define EPOCHS 10000
#define LR 0.5

double sigmoid(double x) {
    return 1.0 / (1.0 + exp(-x));
}

double dsigmoid(double x) {
    return x * (1.0 - x);
}

int main() {
    double X[N][INPUT] = {
        {0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
        {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}
    };

    double Y[N] = {0,1,1,0,1,0,0,1};

    double w1[INPUT][HIDDEN], b1[HIDDEN];
    double w2[HIDDEN], b2;
    double h[HIDDEN], out;
    double dh[HIDDEN], do_, error, total_error;

    srand(time(NULL));

    for (int i = 0; i < INPUT; i++)
        for (int j = 0; j < HIDDEN; j++)
            w1[i][j] = ((double)rand() / RAND_MAX) * 2 - 1;

    for (int j = 0; j < HIDDEN; j++)
        b1[j] = ((double)rand() / RAND_MAX) * 2 - 1;

    for (int j = 0; j < HIDDEN; j++)
        w2[j] = ((double)rand() / RAND_MAX) * 2 - 1;

    b2 = ((double)rand() / RAND_MAX) * 2 - 1;

    for (int epoch = 0; epoch < EPOCHS; epoch++) {
        total_error = 0;

        for (int n = 0; n < N; n++) {

            for (int j = 0; j < HIDDEN; j++) {
                double sum = b1[j];

                for (int i = 0; i < INPUT; i++)
                    sum += X[n][i] * w1[i][j];

                h[j] = sigmoid(sum);
            }

            double sum = b2;

            for (int j = 0; j < HIDDEN; j++)
                sum += h[j] * w2[j];

            out = sigmoid(sum);

            error = Y[n] - out;
            total_error += 0.5 * error * error;

            do_ = error * dsigmoid(out);

            for (int j = 0; j < HIDDEN; j++)
                dh[j] = do_ * w2[j] * dsigmoid(h[j]);

            for (int j = 0; j < HIDDEN; j++)
                w2[j] += LR * do_ * h[j];

            b2 += LR * do_;

            for (int i = 0; i < INPUT; i++)
                for (int j = 0; j < HIDDEN; j++)
                    w1[i][j] += LR * dh[j] * X[n][i];

            for (int j = 0; j < HIDDEN; j++)
                b1[j] += LR * dh[j];
        }

        if (epoch % 1000 == 0)
            printf("Epoch %d, Error=%.6f\n", epoch, total_error);
    }

    printf("\nTesting trained MLP on parity problem:\n");

    for (int n = 0; n < N; n++) {

        for (int j = 0; j < HIDDEN; j++) {
            double sum = b1[j];

            for (int i = 0; i < INPUT; i++)
                sum += X[n][i] * w1[i][j];

            h[j] = sigmoid(sum);
        }

        double sum = b2;

        for (int j = 0; j < HIDDEN; j++)
            sum += h[j] * w2[j];

        out = sigmoid(sum);

        printf("Input: %d%d%d -> Output: %.4f (Target=%d)\n",
               (int)X[n][0], (int)X[n][1], (int)X[n][2],
               out, (int)Y[n]);
    }

    return 0;
}
