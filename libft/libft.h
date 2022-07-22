/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chaidel <chaidel@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:28:08 by chaidel           #+#    #+#             */
/*   Updated: 2022/07/22 18:39:14 by chaidel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <string.h>
# include <unistd.h>

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
	struct s_list	*previous;
}	t_list;

int					ft_isalpha(int c);
int					ft_isdigit(int c);
int					ft_isalnum(int c);
int					ft_isascii(int c);
int					ft_isprint(int c);
size_t				ft_strlen(const char *str);
void				*ft_memset(void *s, int c, size_t n);
void				ft_bzero(void *s, size_t n);
void				*ft_memcpy(void *dest, const void *src, size_t n);
void				*ft_memmove(void *dest, const void *src, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
size_t				ft_strlcat(char *dst, const char *src, size_t size);
char				*ft_strcat(char *dest, const char *src);
int					ft_toupper(int c);
int					ft_tolower(int c);
char				*ft_strupper(char *str);
char				*ft_strlower(char *str);
char				*ft_strchr(const char *s, int c);
char				*ft_strchr_after(const char *s, int c);
char				*ft_strrchr(const char *s, int c);
int					ft_strncmp(const char *s1, const char *s2, size_t len);
int					ft_strcmp(const char *s1, const char *s2);
void				*ft_memchr(const void *s, int c, size_t n);
int					ft_memcmp(const void *s1, const void *s2, size_t n);
char				*ft_strnstr(const char *str,
						const char *to_find, size_t len);
int					ft_atoi(const char *str);
unsigned long long	ft_atoi_unsigned_long_long(const char *str);
char				*ft_strdup(const char *str);
void				*ft_calloc(size_t length, size_t type);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strtrim(char const *str, char const *sep);
char				**ft_split(char const *s, char sep);
char				*ft_itoa(int number);
char				*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void				ft_striteri(char *s, void (*f)(unsigned int, char *));
size_t				ft_putchar_fd(char c, int fd);
size_t				ft_putstr_fd(char *s, int fd);
size_t				ft_putendl_fd(char *s, int fd);
size_t				ft_putnbr_fd(int n, int fd);
char				*ft_straddc_first(char c);
char				*ft_straddc(char *str, char c);

t_list				*ft_lstnew(char *content);
void				ft_lstadd_front(t_list **alst, t_list *new);
int					ft_lstsize(t_list *lst);
t_list				*ft_lstlast(t_list *lst);
void				ft_lstadd_back(t_list **alst, t_list *new);
void				del(char *content);
void				ft_lstdelone(t_list *lst, void (*del)(char *));
void				ft_lstclear(t_list **lst, void (*del)(char *));
void				ft_lstiter(t_list *lst, void (*f)(char *));
t_list				*ft_lstmap(t_list *lst,
						char *(*f)(char *), void (*del)(char *));
#endif
