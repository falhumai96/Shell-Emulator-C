#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdbool.h>
#include <sys/types.h>
#include <signal.h>

// Will be used if we decided to use dynamic memory
char* saved_ptr1 = NULL;
char* saved_ptr2 = NULL;
char* saved_ptr3 = NULL;
char* saved_ptr4 = NULL;
char* saved_ptr5 = NULL;
char* saved_ptr6 = NULL;
char* saved_ptr7 = NULL;

// pointers to the current command data

struct tokinized_cmds { // just pointers to the current commands read
    char *cmd_words[513];
    char *cmd_name;
    int word_count;
};

typedef struct command_storage { // will hold the cmd words and the number of commands
    char cmd_words[513][1024];
    int word_count;
} command_storage;

typedef struct history {
    command_storage cmds[11];
    int size;
} history;


struct tokinized_cmds cmd;
command_storage current_command; // storage for the current command only
history h; // storage for history commands
bool is_background; // will be used for if there is & at the end of the command
char inp = '\0';
int buf_chars = 0;
char* current_path[1024];
char cmd_line[1024];
int current_history_start = 0;

void mini_garbage_collector_for_saved_ptrs() {
    if (saved_ptr1 != NULL) {
        if (saved_ptr1 == saved_ptr2) {
            saved_ptr2 = NULL;
        }

        if (saved_ptr1 == saved_ptr3) {
            saved_ptr3 = NULL;
        }

        if (saved_ptr1 == saved_ptr4) {
            saved_ptr4 = NULL;
        }

        if (saved_ptr1 == saved_ptr5) {
            saved_ptr5 = NULL;
        }

        if (saved_ptr1 == saved_ptr6) {
            saved_ptr6 = NULL;
        }

        if (saved_ptr1 == saved_ptr7) {
            saved_ptr7 = NULL;
        }
        free(saved_ptr1);
        saved_ptr1 = NULL;
    }

    if (saved_ptr2 != NULL) {
        if (saved_ptr2 == saved_ptr1) {
            saved_ptr1 = NULL;
        }

        if (saved_ptr2 == saved_ptr3) {
            saved_ptr3 = NULL;
        }

        if (saved_ptr2 == saved_ptr4) {
            saved_ptr4 = NULL;
        }

        if (saved_ptr2 == saved_ptr5) {
            saved_ptr5 = NULL;
        }

        if (saved_ptr2 == saved_ptr6) {
            saved_ptr6 = NULL;
        }

        if (saved_ptr2 == saved_ptr7) {
            saved_ptr7 = NULL;
        }
        free(saved_ptr2);
        saved_ptr2 = NULL;
    }

    if (saved_ptr3 != NULL) {
        if (saved_ptr3 == saved_ptr1) {
            saved_ptr1 = NULL;
        }

        if (saved_ptr3 == saved_ptr2) {
            saved_ptr2 = NULL;
        }

        if (saved_ptr3 == saved_ptr4) {
            saved_ptr4 = NULL;
        }

        if (saved_ptr3 == saved_ptr5) {
            saved_ptr5 = NULL;
        }

        if (saved_ptr3 == saved_ptr6) {
            saved_ptr6 = NULL;
        }

        if (saved_ptr3 == saved_ptr7) {
            saved_ptr7 = NULL;
        }
        free(saved_ptr3);
        saved_ptr3 = NULL;
    }

    if (saved_ptr4 != NULL) {
        if (saved_ptr4 == saved_ptr1) {
            saved_ptr1 = NULL;
        }

        if (saved_ptr4 == saved_ptr2) {
            saved_ptr2 = NULL;
        }

        if (saved_ptr4 == saved_ptr3) {
            saved_ptr3 = NULL;
        }

        if (saved_ptr4 == saved_ptr5) {
            saved_ptr5 = NULL;
        }

        if (saved_ptr4 == saved_ptr6) {
            saved_ptr6 = NULL;
        }

        if (saved_ptr4 == saved_ptr7) {
            saved_ptr7 = NULL;
        }
        free(saved_ptr4);
        saved_ptr4 = NULL;
    }

    if (saved_ptr5 != NULL) {
        if (saved_ptr5 == saved_ptr1) {
            saved_ptr1 = NULL;
        }

        if (saved_ptr5 == saved_ptr2) {
            saved_ptr2 = NULL;
        }

        if (saved_ptr5 == saved_ptr3) {
            saved_ptr3 = NULL;
        }

        if (saved_ptr5 == saved_ptr4) {
            saved_ptr4 = NULL;
        }

        if (saved_ptr5 == saved_ptr6) {
            saved_ptr6 = NULL;
        }

        if (saved_ptr5 == saved_ptr7) {
            saved_ptr7 = NULL;
        }
        free(saved_ptr5);
        saved_ptr5 = NULL;
    }

    if (saved_ptr6 != NULL) {
        if (saved_ptr6 == saved_ptr1) {
            saved_ptr1 = NULL;
        }

        if (saved_ptr6 == saved_ptr2) {
            saved_ptr2 = NULL;
        }

        if (saved_ptr6 == saved_ptr3) {
            saved_ptr3 = NULL;
        }

        if (saved_ptr6 == saved_ptr4) {
            saved_ptr4 = NULL;
        }

        if (saved_ptr6 == saved_ptr5) {
            saved_ptr5 = NULL;
        }

        if (saved_ptr6 == saved_ptr7) {
            saved_ptr7 = NULL;
        }
        free(saved_ptr6);
        saved_ptr6 = NULL;
    }

    if (saved_ptr7 != NULL) {
        if (saved_ptr7 == saved_ptr1) {
            saved_ptr1 = NULL;
        }

        if (saved_ptr7 == saved_ptr2) {
            saved_ptr2 = NULL;
        }

        if (saved_ptr7 == saved_ptr3) {
            saved_ptr3 = NULL;
        }

        if (saved_ptr7 == saved_ptr4) {
            saved_ptr4 = NULL;
        }

        if (saved_ptr7 == saved_ptr5) {
            saved_ptr5 = NULL;
        }

        if (saved_ptr7 == saved_ptr6) {
            saved_ptr6 = NULL;
        }
        free(saved_ptr7);
        saved_ptr7 = NULL;
    }
}

char* find_dir(char** str_arr, char** look_up_dir) {
    char* res = NULL;
    char path_name[1024];
    if (*str_arr[0] == '/') {
        return str_arr[0];
    } else if (*str_arr[0] == '.') {
        if (*++str_arr[0] == '.') {
            if (getcwd(path_name, sizeof (path_name)) == NULL) {
                perror("getcwd(): error\n"); // executable not found
            } else {
                *--str_arr[0];
                asprintf(&res, "%s%s%s", path_name, "/", str_arr[0]); // create a new one and return it
            }
            return res;
        }


        *--str_arr[0];
        if (*++str_arr[0] == '/') {
            if (getcwd(path_name, sizeof (path_name)) == NULL)
                perror("getcwd(): error\n"); // path not found
            else {
                asprintf(&res, "%s%s", path_name, str_arr[0]); // create a new one and return it
            }
            return res;
        }
    }

    int i;
    for (i = 0; i < 1024; ++i) {
        if (look_up_dir[i] != NULL) {
            // deleting in every loop - major memory leak if not doing so
            if (res != NULL) {
                free(res);
            }
            asprintf(&res, "%s%s%s", look_up_dir[i], "/", str_arr[0]);
            if (access(res, X_OK) == 0) {
                return res;
            }
        }
    }

    // deleting if there is still non-deleted memory
    if (res != NULL) {
        free(res);
    }
    fprintf(stderr, "%s: command not found\n", str_arr[0]);
    return NULL;
}

int get_path(char* dirs[]) {
    char* current_env;
    char* pth;

    int i;

    for (i = 0; i < 513; i++)
        dirs[i] = NULL;
    current_env = (char*) getenv("PATH");
    if (saved_ptr7 != NULL) {
        free(saved_ptr7);
        saved_ptr7 = NULL;
    }
    saved_ptr7 = (char*) malloc((sizeof (char) * strlen(current_env)) + 1); // the extra 1 is for \0
    pth = saved_ptr7;

    strcpy(pth, current_env);
    saved_ptr7 = pth;
    char* pch;
    pch = strtok(pth, ":");
    int j;
    for (j = 0; pch != NULL; ++j) {
        pch = strtok(NULL, ":");
        dirs[j] = pch;
    }
}

int tokenize_cmd(char * cmd_ln, struct tokinized_cmds * command) {
    current_command.word_count = 0;
    int i;
    for (i = 0; i < strlen(cmd_ln); ++i) {
        if (cmd_ln[i] != ' ' && cmd_ln[i] != '\n' && cmd_ln[i] != '\t' && cmd_ln[i] != '\0') {
            char temp[1024];
            int current_index_at_temp = 0;
            int j = 0;
            for (j = i; j < strlen(cmd_ln) && (cmd_ln[j] != ' ' && cmd_ln[j] != '\n' && cmd_ln[j] != '\t' && cmd_ln[j] != '\0');) {
                temp[current_index_at_temp] = cmd_ln[j];
                ++current_index_at_temp;
                ++j;
                i = j;
            }
            temp[j] = '\0';
            strcpy(current_command.cmd_words[current_command.word_count], temp);
            command->cmd_words[current_command.word_count] = current_command.cmd_words[current_command.word_count];
            ++current_command.word_count;
            for (j = 0; j < 1024; ++j) {
                temp[j] = '\0';
            }
            current_index_at_temp = 0;
        }
    }
    command->word_count = current_command.word_count;

    for (i = command->word_count; i < 513; ++i) {
        command->cmd_words[i] = NULL;
    }

    return 0;
}

int process_one_word_cmd(char* buffer, char* cmd_inp) {
    buf_chars = 0;

    while ((*cmd_inp != '\n') && (buf_chars < 1024)) {
        buffer[buf_chars++] = *cmd_inp;
        *cmd_inp = getchar();
    }
    buffer[buf_chars] = '\0';
    return 0;
}

int exec_fin_file_cmd(char * passed_cmd_name, char * str_arr[], char * filename) {
    int file_dr_pip[2];

    if (pipe(file_dr_pip) == 1) {
        perror("pipe");
        mini_garbage_collector_for_saved_ptrs();
        exit(127);
    }

    int fork_stat = fork();

    if (fork_stat == -1) {
        perror("fork()");
        mini_garbage_collector_for_saved_ptrs();
        exit(127);
    } else if (fork_stat == 0) {
        close(file_dr_pip[0]);
        dup2(file_dr_pip[1], 1);
        close(file_dr_pip[1]);
        FILE * p_fin;
        char my_str;

        p_fin = fopen(filename, "r");

        if (p_fin == NULL) {
            perror("Error opening file");
        } else {

            while ((my_str = fgetc(p_fin)) != EOF) {
                putchar(my_str);
            }
            fclose(p_fin);
        }
        mini_garbage_collector_for_saved_ptrs();
        exit(EXIT_SUCCESS);
    } else {
        close(file_dr_pip[1]);
        dup2(file_dr_pip[0], 0);
        close(file_dr_pip[0]);

        execve(passed_cmd_name, str_arr, 0);
        perror(passed_cmd_name);
        mini_garbage_collector_for_saved_ptrs();
        exit(125);
    }
    return 0;
}

int exec_fout(char * passed_cmd_nm, char * str_arr[], char * fin_name) {
    int define = dup(1);

    int fout = open(fin_name, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU | S_IRGRP | S_IROTH);
    if (fout < 0) {
        return 1;
    }

    if (dup2(fout, 1) < 0) {
        return 1;
    }

    int pid_stat = fork();
    if (pid_stat == 0) {
        close(fout);
        close(define);
        execve(passed_cmd_nm, str_arr, 0);
        mini_garbage_collector_for_saved_ptrs();
        exit(EXIT_SUCCESS);
        return 0;
    }


    dup2(define, 1);
    close(fout);
    close(define);
    if (is_background == false) {
        wait(NULL);
    }
    close(fout);
    return 0;
}

void perform_piped_cmd(char *argvA[], char *argvB[], char * nameA, char * nameB) {
    int pipefd[2];

    if (pipe(pipefd)) {
        perror("pipe");
        mini_garbage_collector_for_saved_ptrs();
        exit(127);
    }

    int fork_stat = fork();

    if (fork_stat == -1) {
        perror("fork()");
        mini_garbage_collector_for_saved_ptrs();
        exit(127);
    } else if (fork_stat == 0) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        execve(nameA, argvA, 0);
        mini_garbage_collector_for_saved_ptrs();
        exit(126);
    } else {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        execve(nameB, argvB, 0);
        perror(nameB);
        mini_garbage_collector_for_saved_ptrs();
        exit(125);
    }
}

void insert_history() {
    int i;
    bool entered = false;
    if (h.size == 10) {
        entered = true;
        for (i = 0; i < h.size - 1; ++i) {
            int j;
            for (j = 0; j < h.cmds[i + 1].word_count; ++j) {
                strcpy(h.cmds[i].cmd_words[j], h.cmds[i + 1].cmd_words[j]);
            }
            h.cmds[i].word_count = h.cmds[i + 1].word_count;
        }
        ++current_history_start;
    }

    if (entered == false) {
        for (i = 0; i < cmd.word_count; ++i) {
            strcpy(h.cmds[h.size].cmd_words[i], cmd.cmd_words[i]);
        }
        h.cmds[h.size].word_count = cmd.word_count;
        ++h.size;
    } else {
        for (i = 0; i < cmd.word_count; ++i) {
            strcpy(h.cmds[9].cmd_words[i], cmd.cmd_words[i]);
        }
        h.cmds[9].word_count = cmd.word_count;
    }
}

void signal_handler(int sig) {
    if (sig == SIGINT) {
        printf("\n");
        int i;
        for (i = 0; i < h.size; ++i) {
            printf("%d: ", (current_history_start + i + 1));
            int j;
            for (j = 0; j < h.cmds[i].word_count; ++j) {
                printf("%s ", h.cmds[i].cmd_words[j]);
            }
            printf("\n");
        }
        char printpath_cmd[1024];
        if (getcwd(printpath_cmd, sizeof (printpath_cmd)) != NULL) {
            printf("%s", getcwd(printpath_cmd, sizeof (printpath_cmd)));
        } else {
            perror("getcwd() of current directory error!!");
        }
        printf("> ");
        printf("\n");
    }
}

int exec_systeml_commands() {
    int stat;
    pid_t child_pid;

    int child_pid_stat = fork();
    if (child_pid_stat < 0) {
        fprintf(stderr, "Child forking failed: \n");
        return 1;
    } else if (child_pid_stat == 0) {
        execve(cmd.cmd_name, cmd.cmd_words, 0); // execution of external commands
        printf("System command exited!!\n");
        mini_garbage_collector_for_saved_ptrs();
        exit(EXIT_SUCCESS);
        return 1;
    } else if (child_pid_stat > 0) {
        if (is_background == false) {
            do {
                child_pid = waitpid(child_pid_stat, &stat, WUNTRACED | WCONTINUED);
                if (child_pid == -1) {
                    perror("waitpid");
                    mini_garbage_collector_for_saved_ptrs();
                    exit(EXIT_FAILURE);
                }

                if (WIFEXITED(stat)) {
                    return 0;
                } else if (WIFSIGNALED(stat)) {
                    printf("Killed... Signal: %d\n", WTERMSIG(stat));
                } else if (WIFSTOPPED(stat)) {
                    printf("Suspended... Signal: %d\n", WSTOPSIG(stat));
                } else if (WIFCONTINUED(stat)) {
                    printf("Continued...\n");
                }
            } while (!WIFEXITED(stat) && !WIFSIGNALED(stat)); // The do while is to make sure that the after executing system commands, no line is returned to the shell prompt arrow
        }
        return 0;
    }
}

int analyze_pip_cmd(int pased_index) {
    char* str_A[5];
    char* str_B[5];
    char* cmd_A;
    char* cmd_B;

    int i;
    for (i = 0; i < pased_index; i++) {
        str_A[i] = cmd.cmd_words[i];
    }
    str_A[i] = NULL;
    if (saved_ptr1 != NULL) {
        free(saved_ptr1);
        saved_ptr1 = NULL;
    }
    saved_ptr1 = find_dir(str_A, current_path);
    cmd_A = saved_ptr1;


    int j1;
    int j2 = 0;
    for (j1 = pased_index + 1; j1 < cmd.word_count; ++j1) {
        str_B[j2] = cmd.cmd_words[j1];
        j2++;
    }
    str_B[j2] = NULL;
    if (saved_ptr2 != NULL) {
        free(saved_ptr2);
        saved_ptr2 = NULL;
    }
    saved_ptr2 = find_dir(str_B, current_path);
    cmd_B = saved_ptr2;

    fflush(stdout);

    int pid;
    int stat;

    pid_t temp = fork();

    if (temp == -1) {
        perror("fork");
    } else if (temp == 0) {
        perform_piped_cmd(str_A, str_B, cmd_A, cmd_B);
    } else {
        if (is_background == false) {
            pid = wait(&stat);
        }
        return 0;
    }
    return 1;
}

int fout_cmd(int passed_in_index) {
    char *cmd_name;
    char *str[5];

    int j;
    for (j = 0; j < passed_in_index; ++j) {
        str[j] = cmd.cmd_words[j];
    }

    str[j] = NULL;
    if (saved_ptr3 != NULL) {
        free(saved_ptr3);
        saved_ptr3 = NULL;
    }
    saved_ptr3 = find_dir(str, current_path);
    cmd_name = saved_ptr3;
    int res = exec_fout(cmd_name, str, cmd.cmd_words[passed_in_index + 1]);
    return res;
}

int fin_cmd(int i) {
    char *cmd_name;
    char *str[5];

    int j;
    for (j = 0; j < i; ++j) {
        str[j] = cmd.cmd_words[j];
    }


    str[j] = NULL;
    if (saved_ptr4 != NULL) {
        free(saved_ptr4);
        saved_ptr4 = NULL;
    }
    saved_ptr4 = find_dir(str, current_path);
    cmd_name = saved_ptr4;



    fflush(stdout);

    int pid;
    int stat;

    pid_t temp = fork();

    if (temp == -1) {
        perror("fork");
    } else if (temp == 0) {
        exec_fin_file_cmd(cmd_name, str, cmd.cmd_words[i + 1]);
    } else {
        if (is_background == false) {
            pid = wait(&stat);
        }
        return 0;
    }
    return 0;
}

int analyze_piped_cmds() {

    int pip_ln = 0;


    int fin = 0;
    int fout = 0;

    char *fin_name;
    char *fout_name;


    int i;
    for (i = 0; i < cmd.word_count; ++i) {
        if (strcmp(cmd.cmd_words[i], "<") == 0) { // file in command of pip
            return fin_cmd(i);
        } else if (strcmp(cmd.cmd_words[i], ">") == 0) { // file out command of pip
            return fout_cmd(i);
        } else if (strcmp(cmd.cmd_words[i], "|") == 0) { // normal pip
            return analyze_pip_cmd(i);
        }
    }
    return exec_systeml_commands();
}

void perform_commands() {
    if (strcmp("cd", cmd.cmd_words[0]) == 0) {
        if (cmd.cmd_words[1] == NULL) { // if going back home
            chdir(getenv("HOME"));
        } else {
            if (strcmp(cmd.cmd_words[1], "..") == 0) { // If going back to a previous folder
                if (chdir(cmd.cmd_words[1]) == -1) {
                    printf("%s: No such directory in the current path\n", cmd.cmd_words[1]);
                }
            } else if (cmd.word_count == 2) {
                if (chdir(cmd.cmd_words[1]) == -1) {
                    printf("%s: No such directory in the current path\n", cmd.cmd_words[1]);
                }
            } else { // if accessing folder within directories
                char check_dr_str[1024];
                strcpy(check_dr_str, "");
                int i;
                for (i = 1; i < cmd.word_count; ++i) { // check for folders with spaces
                    if (i < cmd.word_count - 1) {
                        strcat(check_dr_str, cmd.cmd_words[i]);
                        check_dr_str[strlen(check_dr_str) - 1] = '\0';
                        strcat(check_dr_str, " ");
                    } else {
                        strcat(check_dr_str, cmd.cmd_words[i]);
                    }
                }

                if (chdir(check_dr_str) == -1) {
                    printf("%s: No such directory in the current path\n", check_dr_str);
                }
            }
        }
    } else if (strcmp("clear", cmd.cmd_words[0]) == 0) {
        printf("\033[2J\033[1;1H");
    } else {
        if (saved_ptr5 != NULL) {
            free(saved_ptr5);
            saved_ptr5 = NULL;
        }
        saved_ptr5 = find_dir(cmd.cmd_words, current_path);
        cmd.cmd_name = saved_ptr5;


        if (cmd.cmd_name == NULL) {
            printf("Error command!!\n");
        }

        analyze_piped_cmds();
    }
}

void perform_commands_with_input(struct tokinized_cmds cmd) {
    if (strcmp("cd", cmd.cmd_words[0]) == 0) {
        if (cmd.cmd_words[1] == NULL) { // if going back home
            chdir(getenv("HOME"));
        } else {
            if (strcmp(cmd.cmd_words[1], "..") == 0) { // If going back to a previous folder
                if (chdir(cmd.cmd_words[1]) == -1) {
                    printf("%s: No such directory in the current path\n", cmd.cmd_words[1]);
                }
            } else if (cmd.word_count == 2) {
                if (chdir(cmd.cmd_words[1]) == -1) {
                    printf("%s: No such directory in the current path\n", cmd.cmd_words[1]);
                }
            } else { // if accessing folder within directories
                char check_dr_str[1024];
                strcpy(check_dr_str, "");
                int i;
                for (i = 1; i < cmd.word_count; ++i) { // check for folders with spaces
                    if (i < cmd.word_count - 1) {
                        strcat(check_dr_str, cmd.cmd_words[i]);
                        check_dr_str[strlen(check_dr_str) - 1] = '\0';
                        strcat(check_dr_str, " ");
                    } else {
                        strcat(check_dr_str, cmd.cmd_words[i]);
                    }
                }

                if (chdir(check_dr_str) == -1) {
                    printf("%s: No such directory in the current path\n", check_dr_str);
                }
            }
        }
    } else if (strcmp("clear", cmd.cmd_words[0]) == 0) {
        printf("\033[2J\033[1;1H");
    } else {
        if (saved_ptr6 != NULL) {
            free(saved_ptr6);
            saved_ptr6 = NULL;
        }
        saved_ptr6 = find_dir(cmd.cmd_words, current_path);
        cmd.cmd_name = saved_ptr6;

        if (cmd.cmd_name == NULL) {
            printf("Error command!!\n");
        }

        analyze_piped_cmds();
    }
}

#endif