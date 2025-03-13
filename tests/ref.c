#include "../inc/test.h"

t_astnode	*head = NULL;
char		*argv[] = {"./minishell"};

Test(ast, refactor_child_var_1)
{
	t_token	tok;
	t_data	data;

	create_env(2, "SHLVL=11", "PWD=master");
	data.env = init_env(argv, envp);
	tok.type = ECHO; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	tok.type = EXPAND_VAR;
	tok.literal = ft_strdup("SHLVL");
	add_child(head, new_astnode(&tok));
	tok.type = EXPAND_VAR;
	tok.literal = ft_strdup("PWD");
	add_child(head, new_astnode(&tok));
	expand_tree(&data, head);
	cr_expect(strcmp(head->children->literal, "12") == 0, "Expected to expand env var but 12 != %s", head->children->next->literal);
	cr_expect(strcmp(head->children->prev->literal, "master") == 0, "Expected to expand env var but master != %s", head->children->prev->literal);
	free_env(&data.env);
	free_envp();
	free_ast(&head);
}

Test(ast, refactor_child_var_2)
{
	t_token	tok;
	t_data	data;

	data.env = NULL;
	tok.type = EXEC; 
	tok.literal = NULL;
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	tok.type = SSPACE;
	add_child(head, new_astnode(&tok));
	tok.type = SSPACE;
	add_child(head, new_astnode(&tok));
	tok.type = ECHO;
	add_child(head, new_astnode(&tok));
	tok.type = SSPACE;
	add_child(head, new_astnode(&tok));
	expand_tree(&data, head);
	cr_assert_not_null(head->children);
	cr_assert(head->children->type == ECHO);
	cr_expect_null(head->children->next, "Expected NULL but there is %s", decode(head->children->next->type));
	cr_expect_null(head->children->prev->next);
	free_env(&data.env);
	free_envp();
	free_ast(&head);
}

Test(ast, refactor_child_dq_1)
{
	t_token	tok;
	t_data	data;

	create_env(2, "SHLVL=11", "PWD=master");
	data.env = init_env(argv, envp);
	tok.literal = NULL;
	tok.type = ECHO; 
	head = new_astnode(&tok);
	cr_assert_not_null(head);
	tok.type = DQUOTE;
	add_child(head, new_astnode(&tok));
	tok.type = WORD;
	tok.literal = ft_strdup("HELLO  ");
	add_child(head, new_astnode(&tok));
	tok.type = EXPAND_VAR;
	tok.literal = ft_strdup("SHLVL");
	add_child(head, new_astnode(&tok));
	tok.type = EXPAND_VAR;
	tok.literal = ft_strdup("PWD");
	add_child(head, new_astnode(&tok));
	tok.type = WORD;
	tok.literal = ft_strdup("  WORLD");
	add_child(head, new_astnode(&tok));
	tok.literal = NULL;
	tok.type = DQUOTE;
	add_child(head, new_astnode(&tok));
	expand_tree(&data, head);
	cr_assert_not_null(head);
	cr_assert_not_null(head->children);
	cr_assert_not_null(head->children->literal);
	cr_expect_null(head->children->next);
	cr_expect_null(head->children->prev->next);
	cr_expect(strcmp(head->children->literal, "HELLO  12master  WORLD") == 0);
	free_env(&data.env);
	free_envp();
	free_ast(&head);
}


/*
static void	expand_var(t_env *head, t_astnode *node);
static void	construct_dquote(t_data *data, t_astnode *head);
static void	delete_head_child(t_astnode *head);

void	refactor_chilren(t_data *data, t_astnode *head, bool is_echo)
{
	t_astnode	*cur;
	t_astnode	*next;

	if (!head || !data || !head->children)
		return ;
	while (head->children->type == SSPACE && !is_echo)
		delete_head_child(head);
	cur = head->children;
	while (cur)
	{
		next = cur->next;
		if (cur->type == EXPAND_VAR)
			expand_var(data->env, cur);
		cur = next;
	}
}

static void	delete_head_child(t_astnode *head)
{
	t_astnode	*prev;
	t_astnode	*next;

	if (!head || !head->children)
		return ;
	prev = head->children->prev;
	next = head->children->next;
	free(head->children->literal);
	free(head->children);
	if (!next)
		head->children = NULL;
	else
	{
		head->children = next;
		head->children->prev = prev;
	}
}

static void	expand_var(t_env *head, t_astnode *node)
{
	char		*temp;
	t_env		*env;

	if (!node || !node->type)
		return ;
	env = getenv_val(head, node->literal);
	free(node->literal);
	if (!env)
		node->literal = ft_strdup("");
	else
		node->literal = ft_strdup(env->value);
}


void	refactor_chilren(t_data *data, t_astnode *head, bool is_echo)
{
	t_astnode	*cur;
	t_astnode	*next;
	t_astnode	*prev;

	if (!head || !data || !head->children)
		return ;
	while (head->children->type == SSPACE && !is_echo)
		delete_head_child(head);
	cur = head->children;
	prev = NULL;
	while (cur)
	{
		next = cur->next;
		if (cur->type == SSPACE && !is_echo)
		{
			if (!cur->next)
			{
				cur->prev->next = NULL;
				head->children->prev = cur->prev;
			}
			else
				prev = cur->prev;
			free(cur->literal);
			free(cur);
			if (prev)
				prev->next = next;
			prev = NULL;
		}
		else if (cur->type == EXPAND_VAR)
			expand_var(data->env, cur);
		cur = next;
	}
}*/
