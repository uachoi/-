#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct alphabet {
    char apb;
    int count;
};

void swap(struct alphabet* a, struct alphabet* b) {
    char tempApb = a->apb;
    int tempCount = a->count;

    a->apb = b->apb;
    a->count = b->count;

    b->apb = tempApb;
    b->count = tempCount;
}

void bubblesort(struct alphabet arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j].count > arr[j + 1].count) {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

int main() {
    FILE* fp;
    FILE* cntfile;
    FILE* sortedfile;
    char fname[100];
    char fsorted[100];
    char ch;
    int alphabetcnt[26] = { 0 };

    struct alphabet alphabet0[26];

    fp = fopen("C:\\Users\\uacho\\source\\repos\\prog_hw\\alphabet.txt", "rt");

    if (fp == NULL) {
        printf("파일 오픈 실패\n");
        return 1;
    }

    while ((ch = fgetc(fp)) != EOF) {
        if (ch >= 'a' && ch <= 'z') {
            alphabetcnt[ch - 'a']++;
        }
        else if (ch >= 'A' && ch <= 'Z') {
            alphabetcnt[ch - 'A']++;
        }
    }

    for (int i = 0; i < 26; i++) {
        alphabet0[i].apb = 'A' + i;
        alphabet0[i].count = alphabetcnt[i];
    }

    printf("알파벳 카운트 결과 파일명: ");
    scanf("%s", fname);

    cntfile = fopen(fname, "w");

    if (cntfile == NULL) {
        printf("파일 오픈 실패\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        fprintf(cntfile, "%c:%d\n", alphabet0[i].apb, alphabet0[i].count);
    }
    fclose(cntfile);

    bubblesort(alphabet0, 26);
    printf("알파벳 카운트 버블 정렬 결과 파일명: ");
    scanf("%s", fsorted);

    sortedfile = fopen(fsorted, "w");

    if (sortedfile == NULL) {
        printf("파일 오픈 실패\n");
        return 1;
    }

    for (int i = 0; i < 26; i++) {
        fprintf(sortedfile, "%c:%d <- %c\n", alphabet0[i].apb, alphabet0[i].count, 'a' + i);
    }

    char enc_name[100];
    FILE* enc_file;

    printf("암호화 파일명: ");
    scanf("%s", enc_name);
    enc_file = fopen(enc_name, "w+");

    if (enc_file == NULL) {
        printf("파일 오픈 실패\n");
        return 1;
    }

    rewind(fp);

    while (fscanf(fp, "%c", &ch) != EOF) {
        int upper = (ch >= 'A' && ch <= 'Z');
        int lower = (ch >= 'a' && ch <= 'z');
        if (upper || lower) {
            int i;
            int n = 26;
            for (i = 0; i < n; i++) {
                if (lower && ch == 'a' + i) {
                    ch = alphabet0[i].apb + 'a' - 'A';
                    break;
                }
                else if (upper && ch == 'A' + i) {
                    ch = alphabet0[i].apb + 'a' - 'A';
                    break;
                }
            }        
        }
        fprintf(enc_file, "%c", ch);
    }

    char dec_name[100];
    FILE* dec_file;

    printf("복호화 파일명: ");
    scanf("%s", dec_name);
    dec_file = fopen(dec_name, "w");

    if (dec_file == NULL) {
        printf("파일 오픈 실패\n");
        return 1;
    }

    rewind(enc_file);

    while (fscanf(enc_file, "%c", &ch) != EOF) {
        int lower = (ch >= 'a' && ch <= 'z');
        if (lower) {
            int i;
            int n = 26;
            for (i = 0; i < n; i++) {
                if (ch == alphabet0[i].apb + 'a' - 'A') {
                    ch = 'a' + i;
                    break;
                }
            }
            if (i == n) {
                continue;
            }
        }
        fprintf(dec_file, "%c", ch);
    }

    fclose(fp);
    fclose(sortedfile);
    fclose(enc_file);
    fclose(dec_file);

    return 0;
}
