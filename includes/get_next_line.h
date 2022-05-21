/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 15:50:32 by chaidel           #+#    #+#             */
/*   Updated: 2022/05/21 14:47:42 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "../libft/libft.h"
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char	*get_next_line(int fd);
char	*ft_extract(int fd, char *rest);
char	*ft_get_line(char *rest);
char	*ft_cut(char *rest);
char	*ft_chr(const char *s, int c);
char	*ft_join(char *rest, char const *brut);

#endif