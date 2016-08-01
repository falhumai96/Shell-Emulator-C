#include "shell.h"

int main(int argc, char* argv[]) {
    get_path(current_path); // get the starting path
    printf("\nCMPT 300 Project 2 - Shell With History\n\nMade by:\n - Faisal Al-Humaimidi\n - Peter Kvac\n\n");
    h.size = 0;
    int loop_flag = 1; // break flag
    while (loop_flag == 1) {
        is_background = false;
        signal(SIGINT, signal_handler);
        char printpath_cmd[1024];
        if (getcwd(printpath_cmd, sizeof (printpath_cmd)) != NULL) {
            printf("%s", getcwd(printpath_cmd, sizeof (printpath_cmd)));
        } else {
            perror("getcwd() of current directory error!!");
        }
        printf("> ");

        inp = getchar(); //determine if to exec just '\n' or entire cmd

        if (inp != '\n') {
            process_one_word_cmd(cmd_line, &inp);

            // The command line will not execute if there is nothing in the command line
            // If this code was not made, empty inputs will cause the program to crash
            bool is_empty = true;
            int i;
            for (i = 0; i < strlen(cmd_line); ++i) {
                if (cmd_line[i] != ' ' && cmd_line[i] != '\n' && cmd_line[i] != '\t' && cmd_line[i] != '\0') {
                    is_empty = false;
                }
            }

            if (is_empty == false) {
                if ((strcmp(cmd_line, "exit") == 0) || (strcmp(cmd_line, "quit") == 0)) {
                    mini_garbage_collector_for_saved_ptrs();
                    exit(EXIT_SUCCESS);
                } else if ((strcmp(cmd_line, "history") == 0)) {
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
                } else if ((strcmp(cmd_line, "!!") == 0)) {
                    if (h.size > 0) {
                        int i;
                        for (i = 0; i < h.cmds[h.size - 1].word_count; ++i) {
                            strcpy(current_command.cmd_words[i], h.cmds[h.size - 1].cmd_words[i]);
                        }
                        for (i = 0; i < h.cmds[h.size - 1].word_count; ++i) {
                            cmd.cmd_words[i] = current_command.cmd_words[i];
                        }
                        cmd.word_count = h.cmds[h.size - 1].word_count;
                        for (i = 0; i < h.cmds[h.size - 1].word_count; ++i) {
                            printf("%s ", cmd.cmd_words[i]);
                        }
                        printf("\n");

                        insert_history();
                        if (strcmp(cmd.cmd_words[cmd.word_count - 1], "&") == 0 && cmd.word_count > 1) {
                            cmd.cmd_words[cmd.word_count - 1] = NULL;
                            cmd.word_count = cmd.word_count - 1;
                            is_background = true;
                        }

                        perform_commands();
                    } else {
                        printf("No commands in history!!\n");
                    }
                } else if (strlen(cmd_line) > 0 & cmd_line[0] == '!') {
                    if (strlen(cmd_line) > 1) {
                        char temp_str[1024];
                        for (i = 0; i < strlen(cmd_line) - 1;) {
                            temp_str[i] = cmd_line[i + 1];
                            ++i;
                            temp_str[i] = '\0';
                        }
                        int command_num = atoi(temp_str);
                        if (command_num == 0) {
                            printf("Wrong history command!!\n");
                        } else {
                            if (command_num >= (current_history_start + 1) && command_num <= (current_history_start + h.size)) {
                                int pos = command_num - 1 - current_history_start;
                                for (i = 0; i < h.cmds[pos].word_count; ++i) {
                                    strcpy(current_command.cmd_words[i], h.cmds[pos].cmd_words[i]);
                                }
                                for (i = 0; i < h.cmds[pos].word_count; ++i) {
                                    cmd.cmd_words[i] = current_command.cmd_words[i];
                                }



                                cmd.word_count = h.cmds[pos].word_count;
                                for (i = 0; i < cmd.word_count; ++i) {
                                    printf("%s ", cmd.cmd_words[i]);
                                }
                                printf("\n");

                                insert_history();
                                if (strcmp(cmd.cmd_words[cmd.word_count - 1], "&") == 0 && cmd.word_count > 1) {
                                    cmd.cmd_words[cmd.word_count - 1] = NULL;
                                    cmd.word_count = cmd.word_count - 1;
                                    is_background = true;
                                }
                                perform_commands();
                            } else {
                                printf("No history at %d!!\n", command_num);
                            }
                        }
                    } else {
                        printf("Wrong history command!!\n");
                    }
                } else {
                    tokenize_cmd(cmd_line, &cmd);
                    insert_history();

                    if (strcmp(cmd.cmd_words[cmd.word_count - 1], "&") == 0 && cmd.word_count > 1) {
                        cmd.cmd_words[cmd.word_count - 1] = NULL;
                        cmd.word_count = cmd.word_count - 1;
                        is_background = true;
                    }

                    perform_commands();
                }
            }
        }
    }

    printf("\n");
    mini_garbage_collector_for_saved_ptrs();
    exit(EXIT_SUCCESS);
}