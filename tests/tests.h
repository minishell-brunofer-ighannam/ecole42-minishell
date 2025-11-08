/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:10:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/08 17:25:56 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <stdio.h>
# include <stdbool.h>

// ========================
// Basic ANSI colors
// ========================
# define PRINT_BLACK        "\033[30m"
# define PRINT_RED          "\033[31m"
# define PRINT_GREEN        "\033[32m"
# define PRINT_YELLOW       "\033[33m"
# define PRINT_BLUE         "\033[34m"
# define PRINT_MAGENTA      "\033[35m"
# define PRINT_CYAN         "\033[36m"
# define PRINT_WHITE        "\033[37m"

// ========================
// Bright / light ANSI colors
// ========================
# define PRINT_LIGHT_BLACK   "\033[90m" // light gray
# define PRINT_LIGHT_RED     "\033[91m"
# define PRINT_LIGHT_GREEN   "\033[92m"
# define PRINT_LIGHT_YELLOW  "\033[93m"
# define PRINT_LIGHT_BLUE    "\033[94m"
# define PRINT_LIGHT_MAGENTA "\033[95m"
# define PRINT_LIGHT_CYAN    "\033[96m"
# define PRINT_LIGHT_WHITE   "\033[97m"

// ========================
// Reset and text styles
// ========================
# define PRINT_RESET        "\033[0m"
# define PRINT_BOLD         "\033[1m"
# define PRINT_UNDERLINE    "\033[4m"

// ========================
// Gray shades using 256-color mode
// ========================
# define PRINT_GRAY_232     "\033[38;5;232m" // almost black
# define PRINT_GRAY_233     "\033[38;5;233m"
# define PRINT_GRAY_234     "\033[38;5;234m"
# define PRINT_GRAY_235     "\033[38;5;235m"
# define PRINT_GRAY_236     "\033[38;5;236m"
# define PRINT_GRAY_237     "\033[38;5;237m"
# define PRINT_GRAY_238     "\033[38;5;238m"
# define PRINT_GRAY_239     "\033[38;5;239m"
# define PRINT_GRAY_240     "\033[38;5;240m"
# define PRINT_GRAY_241     "\033[38;5;241m"
# define PRINT_GRAY_242     "\033[38;5;242m"
# define PRINT_GRAY_243     "\033[38;5;243m"
# define PRINT_GRAY_244     "\033[38;5;244m"
# define PRINT_GRAY_245     "\033[38;5;245m"
# define PRINT_GRAY_246     "\033[38;5;246m"
# define PRINT_GRAY_247     "\033[38;5;247m"
# define PRINT_GRAY_248     "\033[38;5;248m"
# define PRINT_GRAY_249     "\033[38;5;249m"
# define PRINT_GRAY_250     "\033[38;5;250m"
# define PRINT_GRAY_251     "\033[38;5;251m"
# define PRINT_GRAY_252     "\033[38;5;252m"
# define PRINT_GRAY_253     "\033[38;5;253m"
# define PRINT_GRAY_254     "\033[38;5;254m"
# define PRINT_GRAY_255     "\033[38;5;255m" // almost white

typedef struct s_test	t_test;
struct s_test
{
	int		teste_number;
	bool	test_ok;
	char	*test_input;
};

char	*status(bool test_ok);
void	print_test_and_result(
			t_test test, void (*print_result)(void *arg), void *arg);

#endif
