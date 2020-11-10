//
//  pwd.c
//  t
//
//  Created by Shawn H Wang on 2020/11/7.
//

#include "pwd.h"

char path[BUFSIZ];

void clear_path()
{
    int i;
    for (i=0; i<BUFSIZ; i++) {
        path[i]='\0';
    }
}

char* get_path()
{
    return path;
}

void add_to_path(char *its_path)
{
    if (its_path == NULL || strlen(its_path)==0) {
        return;
    }
    size_t l = strlen(path);
    int i = (int)l;
    path[i++]='/';
    for (; i<l+strlen(its_path)+1; i++) {
        path[i] = its_path[i-l-1];
    }
}

void get_current_path(ino_t this_inode) {
    ino_t my_inode;
    char its_path[BUFSIZ];
    if (get_inode("..") != this_inode) {    // If the current directory is equal to the father directory, it means we have arrived at the root directory
        chdir("..");
        inum_to_dname(this_inode, its_path, BUFSIZ);    // Get current directory name.
        my_inode = get_inode(".");
        get_current_path(my_inode);
        add_to_path(its_path);
    }
}

// Get the directory in the inode_number and save it into the buffer
void inum_to_dname(ino_t inode_to_find, char *buffer, int buf_len)
{
    DIR *dir_ptr;
    struct dirent *dirent_ptr;
    dir_ptr = opendir(".");
    if (dir_ptr == NULL) {
        perror(".");
        return;
    }
    while ((dirent_ptr=readdir(dir_ptr)) != NULL) {
        if (dirent_ptr->d_ino == inode_to_find) {
            strncpy(buffer, dirent_ptr->d_name, buf_len);
            buffer[buf_len-1] = '\0';
            closedir(dir_ptr);
            return;
        }
    }
    fprintf(stderr, "Error Looking for inum: %du\n", (int)inode_to_find);
}

// Get the inode_number by the fname
ino_t get_inode(const char* fname)
{
    struct stat info;
    if (stat(fname, &info) == -1) { //
        perror("Cannot find this directory!!");
        perror(fname);
    }
    return info.st_ino;
}
