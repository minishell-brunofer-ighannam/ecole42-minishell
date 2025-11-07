/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:10:52 by valero            #+#    #+#             */
/*   Updated: 2025/11/07 15:16:00 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

# include <stdbool.h>

# define PRINT_BOLD "\033[1m"
# define PRINT_RESET "\033[0m"
# define PRINT_LIGHT_RED "\033[91m"
# define PRINT_LIGHT_GREEN "\033[92m"
# define PRINT_LIGHT_CYAN "\033[96m"

char	*status(bool test_ok);

#endif
