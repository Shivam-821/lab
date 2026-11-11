#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX 1000
#define LEN 50

typedef struct {
    char word[LEN];
    int spam, nonspam;
} Word;

Word v[MAX];
int n = 0, spamMsg = 0, nonspamMsg = 0;

int find(char *w) {
    int i;
    for(i = 0; i < n; i++)
        if(strcmp(v[i].word, w) == 0)
            return i;
    return -1;
}

int add(char *w) {
    int i = find(w);
    if(i != -1) return i;

    strcpy(v[n].word, w);
    v[n].spam = v[n].nonspam = 0;
    return n++;
}

void clean(char *w) {
    int i, j = 0;
    char t[LEN];

    for(i = 0; w[i]; i++)
        if(isalnum((unsigned char)w[i]))
            t[j++] = tolower((unsigned char)w[i]);

    t[j] = '\0';
    strcpy(w, t);
}

void train(char *msg, int isSpam) {
    char *w = strtok(msg, " \t\n");

    while(w) {
        clean(w);

        if(strlen(w) > 0) {
            int i = add(w);

            if(isSpam)
                v[i].spam++;
            else
                v[i].nonspam++;
        }

        w = strtok(NULL, " \t\n");
    }
}

void classify(char *msg) {
    int i, ts = 0, tn = 0;
    double ps, pn;
    char *w;

    for(i = 0; i < n; i++) {
        ts += v[i].spam;
        tn += v[i].nonspam;
    }

    ps = (double)spamMsg / (spamMsg + nonspamMsg);
    pn = (double)nonspamMsg / (spamMsg + nonspamMsg);

    w = strtok(msg, " \t\n");

    while(w) {
        clean(w);
        i = find(w);

        if(i != -1) {
            ps *= (double)(v[i].spam + 1) / (ts + n);
            pn *= (double)(v[i].nonspam + 1) / (tn + n);
        } else {
            ps *= 1.0 / (ts + n);
            pn *= 1.0 / (tn + n);
        }

        w = strtok(NULL, " \t\n");
    }

    printf("\nSpam Probability : %.10f", ps);
    printf("\nNon-Spam Probability : %.10f", pn);

    if(ps > pn)
        printf("\nResult: SPAM\n");
    else
        printf("\nResult: NON-SPAM\n");
}

int main() {
    int m, i, type;
    char msg[1000];

    printf("Enter number of training messages: ");
    scanf("%d", &m);
    getchar();

    for(i = 0; i < m; i++) {
        printf("Enter message: ");
        fgets(msg, sizeof(msg), stdin);

        printf("Enter class (1=SPAM, 0=NON-SPAM): ");
        scanf("%d", &type);
        getchar();

        if(type)
            spamMsg++;
        else
            nonspamMsg++;

        train(msg, type);
    }

    printf("\nEnter a message: ");
    fgets(msg, sizeof(msg), stdin);

    classify(msg);

    return 0;
}

