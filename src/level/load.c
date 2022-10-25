/*
** EPITECH PROJECT, 2022
** SandProject
** File description:
** load.c
*/

#include "structs.h"
#include "prototypes.h"

char *read_file(char *location)
{
    struct stat st;
    char *buff;
    int i = 0;
    char *file = malloc(sizeof(char) * 300);
    int fd;

    file = my_strcpy(file, "levels/");
    file = my_strcat(file, location);
    fd = open(file, O_RDONLY);
    stat(file, &st);
    buff = malloc(sizeof(char) * st.st_size + 1);
    i = read(fd, buff, st.st_size);
    close(fd);
    buff[i] = '\0';
    return (buff);
}

char *get_file_ext(const char *filename)
{
    int i = 0;
    int len =  my_strlen(filename);
    int last_dot = -1;
    char *ext = malloc(sizeof(char) * my_strlen(filename) + 1);

    for (;i < len; i++)
        if (filename[i] == '.')
            last_dot = i;
    if (last_dot == -1)
        return NULL;
    filename += last_dot;
    ext = my_strcpy(ext, filename);
    return ext;
}

int get_nb_files(const char *path)
{
    find_files_t tf;
    DIR *d;
    struct dirent *dir;
    int x = 0;
    int nb = 0;

    if ((d = opendir("levels/")) == NULL)
        return -1;
    while ((dir = readdir(d)) != NULL)
        nb++;
    closedir(d);
    return nb - 2;
}

char **find_files(void)
{
    find_files_t tf;
    int index = 0;

    tf.file_nb = get_nb_files("levels/");
    tf.content = NULL;
    if (tf.file_nb == -1)
        return NULL;
    tf.found_files = malloc(sizeof(char *) * (tf.file_nb + 1));
    if ((tf.d = opendir("levels/")) == NULL)
        return NULL;
    while ((tf.dir = readdir(tf.d)) != NULL) {
        if (my_strcmp(get_file_ext(tf.dir->d_name), ".lvl") == 0) {
            tf.file = open(tf.dir->d_name, O_RDONLY);
            tf.content = my_strdup(read_file(tf.dir->d_name));
            tf.found_files[index] = my_strdup(tf.content);
            index++;
        }
    }
    tf.found_files[index] = NULL;
    if (tf.file_nb == 0)
        return NULL;
    return tf.found_files;
}
