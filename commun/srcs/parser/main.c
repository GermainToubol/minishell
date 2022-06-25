/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmauguin <fmauguin@student.42.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/15 00:58:06 by fmauguin          #+#    #+#             */
/*   Updated: 2022/06/25 15:11:04 by fmauguin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lexer.h"
#include "astree.h"
#include "parser.h"
#include "libft.h"
#include "utils.h"

/**	mallocator main	**/
/**
int	main_mallocator2(char *arg)
{
	char		*line;
	t_tokens	tokens;
	t_parse		**parse;
	t_astree	*root;

	line = ft_strdup(arg);
	if (!line)
		return (1);
	if (lexer(line, &tokens))
		return (free(line), 0);
	print_lexer(line, &tokens);
	free(line);
	parse = parser(&tokens);
	if (!parse)
		return (0);
	if (create_astree(parse, &root))
		return (free_parse(parse), 0);
	display_tree("", root, 0);
	astree_apply_suffix(root, free_tree);
	free_parse(parse);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac < 2)
		return (display_error("Error\nusage: ./minishell {ARG}\n", 0), 1);
	ft_printf("\x1b[32mWelcome to Minishell\n\x1b[0m");
	if (main_mallocator2(av[1]))
		return (1);
	return (0);
}
**/
int	main_content(void)
{
	char		*line;
	t_tokens	tokens;
	t_parse		**parse;
	t_astree	*root;

	line = readline("\x1b[33mMINISHELL$> \x1b[0m");
	if (lexer(line, &tokens))
		return (free(line), 0);
	print_lexer(line, &tokens);
	free(line);
	parse = parser(&tokens);
	if (!parse)
		return (0);
	if (create_astree(parse, &root))
		return (free_parse(parse), 0);
	display_tree("", root, 0);
	astree_apply_suffix(root, free_tree);
	free_parse(parse);
	return (0);
}

int	main(int ac, char **av)
{
	if (ac > 1)
		return (display_error("Error\nusage: ./minishell\n", 0), 1);
	ft_printf("\x1b[32mWelcome to Minishell\n\x1b[0m");
	(void)av;
	while (1)
		if (main_content())
			return (1);
	return (0);
}
