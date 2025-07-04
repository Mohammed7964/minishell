/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaezzem <omaezzem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 23:17:48 by omaezzem          #+#    #+#             */
/*   Updated: 2025/06/15 16:53:44 by omaezzem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <stddef.h>
#include <sys/wait.h>
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <limits.h>
#include <signal.h>
#include <sys/stat.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <fcntl.h>

# define FAILURE    0
# define SUCCESS    1
# define PMAX    4096
# define PATH_ENV "/mnt/homes/omaezzem/brew/bin:/mnt/homes/omaezzem/brew/bin:/mnt/homes/omaezzem/brew/bin:/mnt/homes/omaezzem/goinfre/homebrew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin:/usr/local/munki:/Library/Apple/usr/bin"

extern int g_sig;

typedef  enum
{
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_APPEND,
    TOKEN_HEREDOC,
    TOKEN_REDIRECT_IN,
    TOKEN_REDIRECT_OUT,
    TOKEN_OPEN_PAREN,
    TOKEN_CLOSE_PAREN,
    TOKEN_FILE,
    TOKEN_IN_FILE,
    TOKEN_OUT_FILE,
    TOKEN_OR,
    TOKEN_APPEND_FILE,
    TOKEN_HEREDOC_FILE,
    TOKEN_OPTION,
    TOKEN_SPACE,
    TOKEN_DQUOTE,
    TOKEN_SQUOTE,
    TOKEN_CMD,
}    t_type;


typedef struct s_env
{
    char            *var;
    char            *val;
    struct  s_env    *next;
}                t_env;

typedef struct s_exp
{
    char            *vr;
    char            *vl;
    struct  s_exp    *next;
}                t_exp;

typedef struct s_herdoc
{
    char    *delimiter;
    char    *filename;
    int        flag_heredoc;
    int        fd;
    struct s_heredoc *next;
} t_heredoc;

typedef struct s_cmd
{
    char            **cmd;
    char            **args;
    char            **files;
    t_type            type;
    t_env            *env;
    t_exp            *exp;
    t_heredoc        *heredoc;
    char             *value_expand;
    char            **redirection;
    char             *workdir;
    int               ex_status;
    int                flag_status;
    char              **envp;
    int               flg;  
    int                numcmd;
    struct s_cmd    *next;
}                t_cmd;
typedef enum e_quote_type
{
	NO_QUOTE,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
    NO_EXPAND,
}	t_quote_type;

typedef struct s_token
{
    char *value;
    t_quote_type	quote_type;
    int expand;
    t_cmd **cmd;
    t_type type;
    struct s_token *next;
} t_token;
typedef struct s_dynstr
{
    char *data;
    size_t len;
    size_t cap;
} t_dynstr;


typedef struct s_gc_node
{
    void                *ptr;
    struct s_gc_node    *next;
}   t_gc_node;

typedef struct s_gc
{
    t_gc_node *list;
}   t_gc;

typedef struct s_ctx
{
    t_cmd       *data;
    t_cmd       *cmd;
    int         numcmd;
    char        **envp;
    t_token        *curr;
    t_token        *tk;
    int            exit_status;
    int            *s;
    int         *d;
    t_token        *delim;
    t_exp       *exp;
    t_heredoc   *heredoc;
    t_gc    *gc;
    t_env    *env;
    int        fd;
    char    *delimeter;
    char    *tmp;
    int        expand_flag;
    int         fdher;
    int         (*pipes)[2];
    int		abort_cmd;
    int         *pids;
} t_ctx;



/*---------------------------------------------utils---------------------------------------------*/

t_env		*ft_lstnew_val(char *val);
t_env		*ft_lstnew_var(char *var);
void		ft_lstadd_back_env(t_env **lst, t_env *new);
void		ft_lstadd_back_exp(t_exp **lst, t_exp *new);
int			ft_strcmp(char *s1, char *s2);
char		**mysplit(char *s, char c);
int			ft_strlen(char *str);
char		*ft_strdup(char *s);
int			ft_isalnum(int c);
char		*ft_strjoin(char *s1, char *s2);
void		print_exe(char *str);
int			mini_atoi(char *str);
void		ft_freeptr(void *ptr);
int			ft_isspace(char *str);
int			ft_strncmp(char *s1, char *s2, size_t n);
char		*ft_strchr(char *s, int c);
int			len_arg(char **args);
char		**ft_split(char *s, char c);
char		*ft_strchr_add_one(char *s, int c);
char	*ft_strncpy(char *dest, char *src, size_t n);
int			ft_isnum(int c);
void		ft_putstr_fd(char *s, int fd);
int			ft_isalpha(int c);
void		*ft_memcpy(void *dst, const void *src, size_t n);
int			ft_len_redirections(char **redirections);
int     	ft_output_append(char **file, char **redirections, int i);
int     	ft_inp_heredoc(char **file, char **redirections, int i);
char		*ft_itoa(int n);
long long 	ft_atoi(const char *str);
char    *ft_strcpy(char *s1, char *s2);
void		ft_exp_clear(t_exp **lst);
void		free_split(char **arr);
void		ft_env_clear(t_env **lst);
void	*ft_memset(void *b, int c, size_t len);
/*---------------------------------------------execution--------------------------------------------*/

int		ft_echo(char **args);
int		ft_cd(t_env *env, char **args ,t_exp *exp);
t_env	*ft_create_env(char **env, t_env **ev);
int		builtin_env(t_env **env_head, char **args);
void	ft_exit(t_cmd *data, char **args);
char	*find_env(t_env *env, char *var);
int		execute_single_cmd(t_env **env, char **envp, t_cmd *data, t_heredoc *heredoc);
int		ft_pwd(t_env *env);
int		ft_export(t_exp *exp, t_env *env, char **args);
t_exp	*ft_create_env_export(char **env, t_exp **list);
int	ft_unset(t_exp **exp, t_env **env, char **args);
void to_single_redirection(char **files, char **redirections, int herdocfd, t_cmd *data);
int ft_execute(t_ctx *ctx, t_cmd **data, char **envp, t_heredoc *heredoc);
void	add_usr_bin_env(t_env **env_head);
void	add_path(t_env **env_head);
void	add_shlvl(t_env **env_head);
void	add_pwd(t_env **env_head);
void	minishell_invalid(char *invalid_str);
int	ft_do_redirections(char **files, char **redirections, int heredoc, t_cmd *data);
void	update_val_env(t_env *env, char *var, char *val);
void	update_val_exp(t_exp *exp, char *var, char *val);
void	update_new(t_env **ev, char *newpath);
char	*determine_path(t_env *env, char **args, int lenargs);
void	update_old(t_env **ev, char *oldpath);
int		find_plus(char *var);
int		len_alnum_var(char *var);
int		find_equal(char *str);
int		len_at_first_equal(char *str);
int		len_equal(char *str);
int	if_double_var(t_exp **exp);
void	add_to_export_list_v(t_exp **exp, char *avzero);
void	add_to_export_list_vl(t_exp **exp, char *avzero, char *avone);
void	update_join_exp(t_exp *exp, char *var, char *val);
void	update_join_env(t_env *env, char *var, char *val);
void	add_to_export_list_vl(t_exp **exp, char *avzero, char *avone);
void	add_to_export_list_v(t_exp **exp, char *avzero);
void	add_to_env_list(t_env *env, char *args, char *avzero, char *avone);
int	sort_exp_list(t_exp **exp);
void	minishell_invalid(char *invalid_str);
char	*check_var(char *var);
char	*args_zero(char *args);
char	*args_one(char *args);
int		search_var_in_exp(t_exp *exp, char *var);
int		search_var_in_env(t_env *env, char *var);
int		ft_builtins(t_env **env, t_exp **exp, t_cmd *data, int herdcfd);
int		is_builtin(char *args);
int     check_dir_file(char **args, t_cmd *data);
int		len_cmd(t_cmd *data);
int		notpipe(t_cmd *data);
void    exit_one_handred_twenty_seven(t_cmd *data);
void	invalid_msg(char **cmd, t_cmd *data);
void    exit_failure(t_cmd *data);
void    exit_success(t_cmd *data);
void	invalid_path(t_cmd *data);
void    exit_one_handred_twenty_sex(t_cmd *data);
int	is_cmd_path(t_cmd *curr, char **commande, t_ctx *ctx, int i);
int	join_execve_cmd(char *path, char **commande, t_cmd *curr, t_ctx *ctx);
int	ft_execve(t_cmd *curr, t_env **env, t_ctx *ctx, int i);
void	free_pipes(int (*pipes)[2], t_cmd *data, int *pids, int numcmd);
int		create_pipes(int numcmd, int (*pipes)[2], int *pids, t_cmd *data);
int		do_child_one(int i, t_ctx *ctx, t_cmd *curr);
int 	do_child_two(t_cmd *curr, int i, t_ctx *ctx);
int		dup_and_close_pipes(int (*pipes)[2], int i, int numcmd);
int		execute_single_cmd(t_env **env, char **envp, t_cmd *data, t_heredoc *heredoc);
int		execute_path(t_cmd *data, char **envp, char **commande);
int		process_single_arg(t_exp *exp, t_env *env, char *arg);
void	determine_export_case(t_exp *exp, t_env *env, char *arg, char *avzero);
void	handle_equal_case(t_exp *exp, t_env *env, char *arg, char *avzero);
void	handle_plus_case(t_exp *exp, t_env *env, char *arg, char *avzero);
int update_exit_status(int status, t_cmd *data);
/*---------------------------------------------parsing--------------------------------------*/
#define MAX_ENV 50
# define ENOBRACE 1
# define ENOROOM 2
# define GRN  "\033[0;32m"

void    append_token(t_token **head, t_token *new_token);
void clear_fd(void);
t_token    *create_token(t_gc *gc, char *value, t_type type);
int add_word1(t_gc *gc, char *input, t_token **head, int i);
t_token *tokenize(t_gc *gc, char *input);
t_token *tokenize2(t_gc *gc, char *input);
int skip_spaces(t_gc *gc, char *input, int i, t_token **head);
char	*strip_quotes(t_gc *gc, char *str);
t_token    *tokenize1(t_gc *gc, char *input);
int add_word(t_gc *gc, char *input, t_token **head, int i);
int skip_quotes(const char *s, int i);
int handle_redir(t_gc *gc, char *input, t_token **head, int i);
// void sigint_handler(int sig_num);
int	handle_quoted_content(char *str, int i, char *res, int *j);
int	is_escaped_quote(char *str, int i);
int redir_pipe(char c);
char    *expand_dollar_variable(t_ctx *ctx, char *result,
        char **src, size_t *total);
int ft_issspace(char c);
void mark_file_tokens(t_token *tokens);
int	is_end_of_heredoc(char *line, char *delim);
int	should_expand_line(char *line, int expand_flag);
int	count(const char *s, int *flag, int *b_flag);
int check_pipe_at_start(t_token *tokens);
int    handle_heredoc_logic(t_gc *gc, t_token *cur, t_ctx *ctx, int *res);
int	check_status(int status);
void	sigint_heredoc(int sig);
void heredoc_sigint_child_handler(int sig);
void heredoc_sigint_main_handler(int sig);
void    sanitize_heredocs(t_gc *gc, t_token *tokens);
int    check_basic_errors(t_gc *gc, t_token *tokens, t_ctx *ctx, int *res);
int    error(t_gc *gc, t_token *tokens, t_ctx *ctx);
int    handle_heredoc_parent(pid_t pid, int write_fd, t_ctx *ctx);
int    check_delim_validity(t_token *delim, t_heredoc *heredoc);
int    fork_and_handle(t_gc *gc, t_ctx *ctx);
int	handle_heredoc(t_gc *gc, t_token *start, t_ctx *ctx);
int is_redir_syntax_err(t_token *cur);
int open_heredoc_file(t_gc *gc, t_heredoc *heredoc);
void remove_quotes2_token(t_gc *gc, t_token *token);
t_token    *prepare_tokens(char *input, t_ctx *ctx, t_gc *gc, t_env *env);
void handle_heredoc_child(t_gc *gc, t_ctx *ctx);
void read_and_write_heredoc(t_ctx *ctx);
int is_end_of_heredoc(char *line, char *delim);
int should_expand_line(char *line, int expand_flag);
void write_expanded_line(t_ctx *ctx, char *line);
char    *handle_dollar_sequence(t_ctx *ctx, char *result, char **src_ptr, size_t *total);
int    extract_varname(char **src, char *varname);
char    *append_expanded_var(t_ctx *ctx, char *result, char *varname, size_t *total);
// char    *expand_heredoc(t_gc *gc, t_token *token, t_env *env);
char    *append_to1_result1(t_gc *gc, char *result, char *str, size_t *total);
void    handle_expansion(t_ctx *ctx, t_token **cur, t_token *tk, t_cmd *cmd);
t_token    *add_expanded_tokens(t_gc *gc, char *value, t_token **cur);
char    *expand_value(t_ctx *ctx, char *value, t_cmd *cmd);
void    handle_dollar(t_ctx *ctx, char **src, t_dynstr *ds, t_cmd *cmd);
void    append_dollars(t_gc *gc, t_dynstr *ds, int count);
char    *get_var_value(t_gc *gc, char **src, t_env *env, t_cmd *cmd);
char    *get_var_name(t_gc *gc, char **src);
void	handle_quotes(t_ctx *ctx, char c);
int    tokenize_next_token(t_gc *gc, char *input, t_token **head, int i);
char    *dyn_str_finalize(t_gc *gc, t_dynstr *ds);
int    dyn_str_append(t_gc *gc, t_dynstr *ds, const char *str, size_t len);
void dyn_str_init(t_dynstr *ds);
int    error2(t_token *cur);
int    error_pipe(t_token *tokens);
int    is_invalid_pipe_sequence(t_token *cur);
void    count_dollars(char **src, int *escape_count, int *expand);
char *make_heredoc_filename(t_gc *gc);
void    print_type(t_type type);
void    ft_bzero(void *s, size_t n);
t_type    get_token_type(char *str);
// int    error(t_gc *gc, t_token *tokens, t_ctx *ctx);
char    *ft_substr(char *s, int start, int len);
// int        error_pipe(t_token *tokens);
void    sigint_handler(int sig);
t_token *tokenize(t_gc *gc, char *input);
void	signals_heredoc(void);
char    *read_input(char *prompt);
char    *expand_heredoc(t_ctx *ctx, t_token *token);
t_cmd    *parse(t_gc *gc, t_env *env, t_heredoc *heredoc, t_cmd **cmd_1);
t_cmd *joining(t_token *tokens);
t_cmd    *joining2(t_gc *gc, t_token *tokens);
// t_cmd    *joining2(t_token *tokens);
t_token *tokenize1(t_gc *gc, char *input);
int skip_quotes(const char *s, int i);
char    **init_cmd(char **full);
void    free_cmd(t_cmd *cmd);
t_token    *expand(t_ctx *ctx, t_token *tk, t_cmd *cmd);
int        expand_env(char **oldp, char **newp, int brace_flag, char *var, t_env *env);
int        expand_pid(char **newp, int space_left);
int        expand_argv(char **oldp, char **newp, int space_left);
int        expand_status(char **newp, int space_left);
char    **init_args(char **full, int len);
void    handle_redirection(t_gc *gc, t_token **cur, char ***redir, char ***files);
char    **append_string_array(t_gc *gc, char **arr, char *str);
char    *gitenv(const char* name);
int        expand_argc(char **newp, int space_left);
char *gc_strdup(t_gc *gc, char *s);
char    *gc_itoa(t_gc *gc, int n);
char *gc_substr(t_gc *gc, char *s, int start, int len);
void	remove_quotes3_token(t_gc *gc, t_token *token, int *b_flag);
int        is_match(char *str, char *ptrn);
char *gc_strjoin(t_gc *gc, char *s1, char *s2);
int        expand_wildcard(char **oldp, char **newp, int space_left);
int	is_empty_quotes(char *str, int i);
void	remove_quotes_token_list(t_gc *gc, t_token *tk);
/*---------------------------------------------garbage collectore--------------------------------------*/


void    gc_init(t_gc *gc);
void    *gc_malloc(t_gc *gc, size_t size);
void    gc_free_all(t_gc *gc);
#endif
