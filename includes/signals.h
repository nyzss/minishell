/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okoca <okoca@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 09:49:51 by okoca             #+#    #+#             */
/*   Updated: 2024/07/16 08:39:02 by okoca            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

void	sig_int_handler(int status);

void	sig_init_signals(void);

void	sig_heredoc(int status);

void	sig_exec(int status);

int		sig_event(void);

#endif