/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouichou <aouichou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 18:57:35 by aouichou          #+#    #+#             */
/*   Updated: 2023/03/23 10:24:24 by aouichou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <unistd.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <errno.h>
# include <limits.h>

# define ERROR1				"minishell: syntax error near 00unexpected \
token `newline'"
# define READ_FD 			0
# define WRITE_FD 			1
# define PATH				"/usr/local/sbin:/usr/local/bin:/usr/bin:/bin"

# define RED	       		"\001\033[1;31m\002"
# define GREEN	       		"\001\033[1;32m\002"
# define CYAN	       		"\001\033[1;36m\002"
# define BLUE	       		"\001\033[1;34m\002"
# define YELLOW	       		"\001\033[1;33m\002"
# define BLANK	       		"\001\033[0m\002"

enum	e__errors
{
	QUOTE = 1,
	NO_DIR = 2,
	NO_PERM = 3,
	NO_CMD = 6,
	DUP_ERR = 7,
	FORK_ERR = 8,
	PIPE_ERR = 9,
	PIPE_ENDERR = 10,
	MEM = 11,
	IS_DIR = 12,
	NOT_DIR = 13,
	REDIR_ERR = 14,
	REDIR_ERR2 = 15
};

typedef struct s_ext
{
	int			exit_status;
}				t_ext;

typedef struct s_cmd
{
	char		**cmd_array;
	char		*path;
	int			infile;
	int			outfile;
}				t_cmd;

typedef struct s_main
{
	char		**environ;
	char		**argv;
	pid_t		pid;
	t_list		*cmds;
}				t_main;

// env.c

char			*ft_getenv(char *var, char **envp, int z);
int				var_in_envp(char **envp, char *var, int i[2]);
char			**ft_setenv(char *var, char *value, char **envp, int n);
int				ft_unset(t_main *ptr);

// parser.c

void			*check_line(char *line, t_main *ptr);

// expander.c

char			*expand_path(char *str, int i, int quotes[2], char *var);
char			*expand_variables(char *str, int i, t_main *ptr);

// builtins.c

int				check_builtin(t_cmd *cmd);
int				builtin(t_main *ptr, t_list *cmd, int *do_exit, int n);
int				ft_echo(t_list	*cmd);
int				ft_pwd(void);
int				ft_cd(t_main *ptr);

// get_fd.c

int				get_fd(int oldfd, char *path, int flags[2]);
void			infile1(t_cmd **node, char **argv, int *i);
void			infile2(t_cmd **node, char **argv, int *i);
void			outfile1(t_cmd **node, char **argv, int *i);
void			outfile2(t_cmd **node, char **argv, int *i);

// heredoc.c

int				get_heredoc(char *str[2], char *temp[2]);
char			*read_heredoc(char *str[2], size_t len, char *limit, \
								char *warn);

// execute.c

void			get_cmd(t_main *ptr, t_list *cmds, char **array, char *path);
void			ft_pipex(t_list *cmds, t_cmd *cmd, int *tmp, int i);
void			execute(t_main *ptr, t_list *cmds, t_cmd *cmd, int i);

// export.c

void			ft_export(t_main *ptr, char *temp_str, char **cmd);

// pipex.c

void			ppx_fork(t_main *ptr, t_list *cmds, int fd[2], int *tmp_fd);
void			*ppx_redirect(t_list *cmds, int (*fd)[2], int i);
void			*ppx_child_exec(t_main *ptr, t_list *cmds, int *fd, int tmp_fd);
void			*ppx_execute(t_main *ptr, t_list *cmds, int *fd, int tmp_fd);

// signal.c

void			signal_handler(int sig);

// error.c

void			*ft_error(char *arg, int error, int rno);

// init.c

t_main			*init_main(char **argv, char **envp);
t_cmd			*init_cmd(void);

// prompt.c

char			*get_prompt(t_main *ptr);

// split_check_quotes.c

char			**split_and_check_quotes(char *line, char *set);

// unquote.c

char			**unquote_array(char **argv);

// fill_list.c

t_list			*fill_list(char **argv, int i);

// cmds_split_trim.c

char			**cmds_split_trim(char *str, char *set);

// count_redir.c

int				ft_count_redir(char *str, int i);

// split_keep.c

char			**ft_split_keep(char *s, char c);

// per_history.c

void			get_history(t_main *ptr);
void			add_to_history(t_main *ptr, char *line);

// ft_exit.c

long long		ft_exit_atoi(char *nb, long long *nbr);
int				ft_exit(t_list *cmd, int *do_exit, int pipe);

// free.c

void			free_ptr(void);
void			free_lst(void *content);
int				ft_free(void *ptr, void *ptr2);
void			ppx_close_fd(int fd[2]);

// env_tools.c

int				ft_export_variable_check(char *variable);
int				is_valid_var(char *var);
int				is_valid_char(char c);

// tools.c

t_ext			*get_ext(void);
t_main			*get_ptr(void);

// tools2.c

int				ft_str_is(char *str, char *set);
char			*add_quotes(char *str);

#endif