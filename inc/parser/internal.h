#ifndef PINTERNAL_H
# define PINTERNAL_H

# include "./types.h"

void		print_tokens(t_token *token);
void		generate_tokens(t_lexer	*l);
void		free_lexer(t_lexer *l);
void		read_char(t_lexer *l);
void		eat_whitespaces(t_lexer *l);
void		add_child(t_astnode *parent, t_astnode *child);
void		print_ast(t_astnode *node, int depth);
void		free_ast(t_astnode **node);
int			lex_env_var(t_lexer *l);
int			lex_keyword(t_lexer *l);
int			lex_executable(t_lexer *l);
int			lex_word(t_lexer *l);
int			lex_quote(t_lexer *l);
int			is_there_exec(t_lexer *l);
int			append_token(t_lexer *l, t_token_type type, int size);
int			analyze_tokens(t_lexer *l);
int			get_pos_next_whitespace(t_lexer *l);
char		peek_char(t_lexer *l);
char		*decode(t_token_type t);
t_lexer		*new_lexer(const char *str);
t_lexer		*new_lexer(const char *str);
t_token		*new_token(t_token_type t, t_lexer *l, int size);
t_astnode	*new_astnode(t_token *tok);
t_astnode	*parse_exec(t_token *token);
t_astnode	*parse_redir(t_token **token);
t_astnode	*parse(t_lexer *l);
bool		is_letter(char c);
bool		ft_isspace(char ch);
bool		is_token_exec(t_token_type t);
bool		match(t_token *token, t_token_type expected[], int size);

#endif
