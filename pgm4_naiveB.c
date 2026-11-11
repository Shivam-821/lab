#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <math.h>

#define MAX 1000
#define LEN 50

char words[MAX][LEN];
int sc[MAX], nsc[MAX], n = 0, ts = 0, tns = 0;

void lower(char *s) { 
    for (int i = 0; s[i]; i++) 
        s[i] = tolower(s[i]); 
}

int find(char *w) {
    for (int i = 0; i < n; i++) 
        if (!strcmp(words[i], w)) return i;
    return -1;
}

void addWord(char *w, int spam) {
    int i = find(w);
    if (i == -1) { 
        strcpy(words[n], w); 
        sc[n] = nsc[n] = 0; 
        i = n++; 
    }
    if (spam) { 
        sc[i]++; 
        ts++; 
    } else { 
        nsc[i]++; 
        tns++; 
    }
}

void process(char *msg, int spam) {
    char t[500]; 
    strcpy(t, msg); 
    lower(t);
    char *tok = strtok(t, " .,!?;:()\"'");
    while (tok) { 
        if (strlen(tok)) 
            addWord(tok, spam); 
        tok = strtok(NULL, " .,!?;:()\"'"); 
    }
}

double condProb(char *w, int spam) {
    int i = find(w), c = 0;
    if (i != -1) c = spam ? sc[i] : nsc[i];

    return (double)(c + 1) / ((spam ? ts : tns) + n);
}

void calc(char *msg, double *sp, double *nsp) {
    char t[500]; 
    strcpy(t, msg); 
    lower(t);
    double ls = log((double)ts / (ts + tns));
    double ln = log((double)tns / (ts + tns));
    
    char *tok = strtok(t, " .,!?;:()\"'");
    while (tok) {
        if (strlen(tok)) { 
            ls += log(condProb(tok, 1)); 
            ln += log(condProb(tok, 0)); 
        }
        tok = strtok(NULL, " .,!?;:()\"'");
    }
    double m = ls > ln ? ls : ln;
    *sp = exp(ls - m); 
    *nsp = exp(ln - m);
    double s = *sp + *nsp; 
    *sp /= s; 
    *nsp /= s;
}

int main() {
    char *spam[] = {
        "Congratulations you won a free prize", 
        "Claim your free prize now",
        "You have won a million dollars", 
        "Free money waiting for you",
        "Congratulations you are the winner"
    };
    char *ham[] = {
        "Meeting at 3 PM tomorrow", 
        "Please submit your report",
        "Your appointment is confirmed", 
        "Team lunch on Friday",
        "Project deadline extended"
    };
    
    for (int i = 0; i < 5; i++) { 
        process(spam[i], 1); 
        process(ham[i], 0); 
    }
    
    char msg[500];
    printf("Enter a message: ");
    fgets(msg, 500, stdin);
    msg[strcspn(msg, "\n")] = 0;
    
    double sp, nsp;
    calc(msg, &sp, &nsp);
    
    printf("\nSpam Probability : %.6f\n", sp);
    printf("Non-Spam Probability : %.6f\n", nsp);
    printf("\nResult: %s\n", sp > nsp ? "SPAM" : "NON-SPAM");
    
    return 0;
}