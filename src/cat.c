#include "cat.h"
#include "Shell.h"

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
