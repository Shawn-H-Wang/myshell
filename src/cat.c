#include "cat.h"
#include "Shell.h"

char *CONTENT;

void clear_content()
{
    if (CONTENT == NULL) {
        CONTENT = (char*)malloc(BUFSIZ*2+1);
    }
    int i;
    for (i=0; i<BUFSIZ; i++) {
        CONTENT[i] = '\0';
    }
}

char *get_content()
{
    return CONTENT;
}

void exec_cat_pipe(char *cmd)
{
    char *args = split_blank(cmd, 1);
    if (args == NULL) {
        printf("You don't input args! Please check your input!!");
    }
    else {
        int j = 0;
        while (args != NULL) {
            FILE *fp;
            if (!(fp = fopen(args, "r"))) {
                fprintf(stderr, "Cannot open file %s", args);
                clear_content();
                return;
            }
            int c;
            while ((c = fgetc(fp)) != EOF) {
                CONTENT[j++] = (char)c;
            }
            fclose(fp);
            args = split_blank(cmd, 1);
        }
        strcat(CONTENT, "\n");
    }
}

int exec_cat(char *cmd)
{
    char *args = split_blank(cmd, 1);
    if (args == NULL) {
        printf("You don't input args! Please check your input!!");
    }
    else {
        while (args != NULL) {
            FILE *fp;
            if (!(fp = fopen(args, "r"))) {
                fprintf(stderr, "Cannot open file %s", args);
                exit(-1);
            }
            int c;
            while ((c = fgetc(fp)) != EOF) {
                fputc(c, stdout);
            }
            fclose(fp);
            args = split_blank(cmd, 1);
        }
        puts("");
    }
    return 1;
}
