/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   separate_quote_chuncks_internal.h                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: valero <valero@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 16:53:18 by valero            #+#    #+#             */
/*   Updated: 2025/11/20 17:09:18 by valero           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SEPARATE_QUOTE_CHUNCKS_INTERNAL_H
# define SEPARATE_QUOTE_CHUNCKS_INTERNAL_H

# include "separate_quote_chuncks.h"
# include "../expandable_object/expandable_object_internal.h"

t_token_section				*ft_create_token_session(
								char *session, char quote_type);
t_token_section				*ft_token_session_dup(
								t_token_section *token_session);
void						ft_token_session_destroy_callback(void *arg);
t_token_separated_sections	*ft_create_token_separated_sections(void);

#endif
