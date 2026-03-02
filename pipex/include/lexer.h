/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kyanagis <kyanagis@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/28 05:56:04 by kyanagis          #+#    #+#             */
/*   Updated: 2025/08/29 01:04:32 by kyanagis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "pipex.h"

typedef enum e_lexer_state
{
	LEX_GEN,
	LEX_SQ,
	LEX_DQ,
	LEX_ESC,
	LEX_DQ_ESC
}					t_lexer_state;

typedef struct s_lexer
{
	char			*work;
	char			**args;
	size_t			read_pos;
	size_t			write_pos;
	size_t			args_len;
	size_t			args_cap;
	ssize_t			token_start;
	t_lexer_state	state;
}					t_lexer;

int					is_dq_escapable(char c);

void				handle_dq_esc(t_lexer *lexer, char c);
void				handle_dquote(t_lexer *lexer, char c);
void				handle_squote(t_lexer *lexer, char c);
void				handle_esc(t_lexer *lexer, char c);
void				handle_gen(t_lexer *lexer, char c);

void				grow_args(char ***pargs, size_t *cap, size_t need);
void				push_current_token(t_lexer *lxer);

#endif