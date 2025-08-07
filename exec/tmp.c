// ...existing code...

int execute_pipe(t_token *left, t_token *right)
{
    int pipefd[2];
    int pid1, pid2;

    if (pipe(pipefd) == -1)
        return (perror("pipe"), -1);

    pid1 = fork();
    if (pid1 == 0)
    {
        close(pipefd[0]); 
        dup2(pipefd[1], STDOUT_FILENO); 
        close(pipefd[1]);
        executable(left); 
        exit(0);
    }

    pid2 = fork();
    if (pid2 == 0)
    {
        close(pipefd[1]); 
        dup2(pipefd[0], STDIN_FILENO); 
        close(pipefd[0]);
        executable(right); 
        exit(0);
    }

    close(pipefd[0]);
    close(pipefd[1]);
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return 0;
}
//hadi l part li 5as tzad f execute.c
if (has_pipe(head)) {
    t_token *left = ...; 
    t_token *right = ...;
    execute_pipe(left, right);
} else {
    executable(head);
}