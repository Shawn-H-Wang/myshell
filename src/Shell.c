//
//  Shell.c
//  t
//
//  Created by Shawn H Wang on 2020/11/3.
//

#include "Shell.h"
#include "cd.h"
#include "nf.h"
#include "nfe.h"
#include "hist.h" 
#include "pipe.h"
#include "pwd.h"

char cwd[MAX]; // Save current working directory.
char *cmds[MAX]; // Save several commands(splited by ';')
history *hist; // Save the history of input_commands.

void Shell_Looper()
{
    char *cmd;  // Input cmd line;
    int iter, TAG=0;
    cmd = (char*)malloc(MAX+1); // Save the input line into the cmd.
    hist = (history*)malloc(sizeof(history));
    init_hist(hist);
    PrintAbout();   // Print MyShell's Tag
    
    while (1) {
        iter = 0;
        print_prompt();
        input_line(cmd);
        add_hist(hist, cmd);
        split_inline(cmd);
        
        while (cmds[iter] != NULL) {
            if (exec_cmd(cmds[iter]) == -1) { // Tag of command "exit". Others' return is 1
                TAG = -1;
                break;
            }
            iter++;
        }
        
        if (TAG == -1) { // IF TAG is minus 1, break the looper.
            break;
        }
    }
    // Free space of the cmd
    free(cmd);
    destroy_hist(hist);
}

/*
 * Print the information about the system.
 * Include USER/HOSTNAME/DIRECTORY...
 */
void print_prompt()
{
    struct utsname uname_ptr;
    struct passwd *uname_pid;
    uname(&uname_ptr);  /* Get information from system by the sys_execution "uname"
                         Include OS_NAME/OS_NETWORK_NODE_NAME/OS_RELEASE/OS_VERSION/OS_MACHINE_INFO
                         IF successful--return 0 OR return -1 and SET "errno" value to EFAULT*/
    uname_pid = getpwuid(getuid()); /* Get information about passwd from system by the sys_execution "getpwuid"
                                     Include NAME/PASSWORD/...*/
    getcwd(cwd, sizeof(cwd));
    char tag = strcmp(uname_pid->pw_name, "root")==0 ? '#':'$';
    printf("{%s@%s:%s} %c> ",uname_pid->pw_name, uname_ptr.nodename, cwd, tag);
}

// Input command line.
// Use function "GETLINE"
// IF we use the "fgets", we could not flush the space about the "cmd"!!
void input_line(char *cmd)
{
    ssize_t buffer;         /*ssize_t: "int" in 32bit machine AND "long int" in 64bit machine*/
    size_t buf_bytes = MAX; /*size_t: Unsigned Integer*/
    buffer = getline(&cmd, &buf_bytes, stdin); /*A stdin function from C++
                                                IF success--return bytes of
                                                str_cmd OR return -1*/
    if (buffer < 0) {
        puts("");
        return;
    }
    cmd[(int)(--buffer)] = '\0'; // End tag of a string in C
    replace_char(cmd);
}

// Replace tab-blank to the blank!
void replace_char(char *cmd)
{
    int i;
    for (i=0; i<strlen(cmd); i++) {
        if (cmd[i] == '\t')
            cmd[i] = ' ';
    }
}

// Split the inline by ';' into several commands
void split_inline(char *in_line)
{
    int n;
    for (n=0; n<MAX; n++) { // Init every item in the array of string named "cmds"
        cmds[n] = (char*)malloc(MAX_CMD*sizeof(char));
    }
    n=0;
    cmds[n] = strtok(in_line, ";");
    while (1) {
        n+=1;
        cmds[n]=strtok(NULL, ";");
        if (cmds[n] == NULL)
            break;
    }
}

// Split command line by every blank
// Tag: "0" means the name of cmd   OR   the arguments of the cmd
char *split_blank(char *cmd, int tag)
{
    char *token;
    if (tag==0)
        token = strtok(cmd, " ");
    else
        token = strtok(NULL, " ");
    return token;
}

char *split_and(char *cmd, int tag)
{
    char *token;
    if (tag==0)
        token = strtok(cmd, "&");
    else
        token = strtok(NULL, "&");
    return token;
}

char *split_pipe(char *cmd, int tag)
{
    char *token;
    if (tag==0)
        token = strtok(cmd, "|");
    else
        token = strtok(NULL, "|");
    return token;
}

// Correct the old way.
// The new function to execute the command;
int exec_cmd(char *cmd)
{
    char *commands[3];
    size_t l1 = strlen(cmd);
    commands[0] = NULL;
    commands[0] = split_and(cmd, 0);
    if (strlen(commands[0]) == l1) {    // Without '&'
        char *commds[2];
        size_t l2 = strlen(cmd);
        commds[0] = NULL;
        commds[0] = split_pipe(commands[0], 0);
        if (strlen(commds[0]) == l2) {    // Without '|'
            char *argv[MAX_ARG]; // The array for arguments
            argv[0] = NULL;
            argv[0] = split_blank(cmd, 0); // Get the name of the cmd
            // Judge some commands could without any special characters.
            if (strcmp(argv[0], "cd") == 0) {
                char *dir = split_blank(cmd, 1);
                if (split_blank(cmd, 1) != NULL) {
                    printf("Too many arguments for command: cd! Please check your input!\n");
                    return 1;
                }
                cd(dir);
                return 1;
            }
            else
                return fork_exec(argv, cmd, hist);
        }
        else {
            commds[1] = split_and(commands[0], 1);
            char *token;
            if (commds[1] == NULL || (token=split_blank(commds[1], 0)) == NULL) {
                puts("Pipe without any command! Please check your input!!");
                return 1;
//                printf("> ");
//                char *ncmd = (char*)malloc(MAX+1);
//                input_line(ncmd);
//                add_hist_str(hist->his[hist->length-1], ncmd);
//                strcpy(commds[1], hist->his[hist->length-1]);
            }
            else {
                commds[1][strlen(token)+1] = ' ';
            }
            exec_with_pipe(commds, hist);
            return 1;
        }
    }
    else {  // With '&'
        int i=1;
        while (1) {
            if (i >= 3) {
                puts("Too many processes need to be executed concurrently, we can only keep three!!");
                break;
            }
            commands[i] = NULL;
            commands[i] = split_and(cmd, 1);
            if (commands[i++] == NULL)
                break;
        }
        exec_fork(commands, (i>=3?3:i));
        return 1;
    }
}


void PrintAbout()
{
    printf("\nWeclome To the MyShell!\n\n");
    printf("=======================================\n");
    printf("w      w      w     oooooo     ssssss \n");
    printf("w     w w     w    o      o   s       \n");
    printf(" w   w   w   w     o      o    sssss  \n");
    printf("  w w     w w      o      o         s \n");
    printf("   w       w        oooooo    ssssss  \n");
    printf("=======================================\n\n");
}

// Print MyShell's Byebye Tag
void PrintBye()
{
    printf("===============================================\n");
    printf("BBBBB  Y     Y  EEEEEE  BBBBB  Y     Y  EEEEEE \n");
    printf("B    B  Y   Y   E       B    B  Y   Y   E      \n");
    printf("B    B   Y Y    E       B    B   Y Y    E      \n");
    printf("BBBBB     Y     EEEEEE  BBBBB     Y     EEEEEE \n");
    printf("B    B    Y     E       B    B    Y     E      \n");
    printf("B    B    Y     E       B    B    Y     E      \n");
    printf("BBBBB     Y     EEEEEE  BBBBB     Y     EEEEEE \n");
    printf("===============================================\n\n");
    printf("\n<Process completed>\n\n");
}


int is_in_list(char *cmds[], const char *cmd, int len)
{
    int i;
    for (i=0; i<len; i++) {
        if (strcmp(cmds[i], cmd)==0)
            return 1;
    }
    return 0;
}
