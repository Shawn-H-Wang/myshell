//
//  hist.c
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#include "hist.h"

void init_hist(history *hist)
{
    if (hist == NULL)
        hist = (history*)malloc(sizeof(history));
    hist->length = 0;
    int i;
    for (i=0; i<MAX_HIS; i++) {
        hist->his[i] = NULL;
    }
}

void add_hist(history *hist, const char *in_line)
{
    if (hist == NULL || in_line == NULL || strlen(in_line)==0) {
        return;
    }
    if (hist->length == MAX_HIS) {
        int i;
        for (i=0; i<hist->length-1; i++) {
            hist->his[i] = hist->his[i+1];
        }
        hist->length -= 1;
    }
    hist->his[hist->length++] = (char*)malloc(strlen(in_line)+1);
    strcpy(hist->his[hist->length-1], in_line);
}

// Default print the newest ten cmd_lines.
void print_hist(const history *hist)
{
    if (hist == NULL)
        return;
    int i;
    if (hist->length < 10) {
        i=0;
    } else {
        i = hist->length-10;
    }
    for (; i<hist->length; i++) {
        printf("%4d\t%s\n", i+1, hist->his[i]);
    }
}

// Command with arguments
void print_hist_arg(const history *hist, const char *args)
{
    if (hist == NULL)
        return;
    if (args == NULL) {
        print_hist(hist);
        return;
    }
    int i;
    if (strcmp(args, "-t")==0) {
        print_hist(hist);
        return;
    }
    else if (strcmp(args, "-h")==0) {
        for (i=0;i<10 && i<hist->length; i++) {
            printf("%4d\t%s\n", i+1, hist->his[i]);
        }
        return;
    }
    else if (strcmp(args, "-a")==0) {
        for (i=0; i<hist->length; i++) {
            printf("%4d\t%s\n", i+1, hist->his[i]);
        }
    }
    else {
        printf("Wrong Arguments!! Please check your input!\n");
        return;
    }
}

char *p_hist(const history *hist)
{
    if (hist == NULL)
        return NULL;
    char *HIS = NULL;
    int i, len=0;
    if (hist->length < 10) {
        i=0;
    } else {
        i = hist->length-10;
    }
    for (; i<hist->length; i++) {
        len += strlen(hist->his[i]);
    }
    HIS = (char*)malloc(len+i);
    int k=0;
    for (i=0; i<hist->length; i++) {
        int j;
        for (j=0; j<strlen(hist->his[i]); j++) {
            HIS[k++] = hist->his[i][j];
        }
        HIS[k++]='\n';
    }
    HIS[len+i-1]='\0';
    return HIS;
}

char *p_hist_arg(const history *hist, const char *args)
{
    if (hist == NULL)
        return NULL;
    if (args == NULL) {
        return p_hist(hist);
    }
    char *HIS=NULL;
    int i;
    if (strcmp(args, "-t")==0) {
        return p_hist(hist);
    }
    else if (strcmp(args, "-h")==0) {
        int len=0;
        for (i=0; i<hist->length; i++) {
            len += strlen(hist->his[i]);
        }
        HIS = (char*)malloc(len+i);
        int k=0;
        for (i=0;i<10 && i<hist->length; i++) {
            int j;
            for (j=0; j<strlen(hist->his[i]); j++) {
                HIS[k++] = hist->his[i][j];
            }
            HIS[k++]='\n';
        }
        HIS[len+i-1]='\0';
    }
    else if (strcmp(args, "-a")==0) {
        int len=0;
        for (i=0; i<hist->length; i++) {
            len += strlen(hist->his[i]);
        }
        HIS = (char*)malloc(len+hist->length-1);
        int k=0;
        for (i=0;i<hist->length; i++) {
            int j;
            for (j=0; j<strlen(hist->his[i]); j++) {
                HIS[k-1] = hist->his[i][j];
            }
            HIS[k++]='\n';
        }
        HIS[len+hist->length-2]='\0';
    }
    else {
        printf("Wrong Arguments!! Please check your input!\n");
        return NULL;
    }
    return HIS;
}
