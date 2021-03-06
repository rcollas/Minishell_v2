/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vbachele <vbachele@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:53:53 by rcollas           #+#    #+#             */
/*   Updated: 2021/11/06 17:52:53 by vbachele         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <stdlib.h>
# include <unistd.h>
# include "../include/minishell.h"
# include "struct.h"

int			ft_atoi(const char *str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t count, size_t size);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
int			ft_charcmp(char c1, char c2);
char		*ft_itoa(int n);
void		ft_lstadd_back(t_list **alst, t_list *new);
void		ft_lstadd_front(t_list **alst, t_list *new);
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstlast(t_list *lst);
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
t_list		*ft_lstnew(char *content);
t_envar		*ft_envar_new(char *name, char *content);
t_envar		*ft_envarlast(t_envar *envar);
void		ft_envaradd_back(t_envar **alst, t_envar *new);
int			ft_lstsize(t_list *lst);
void		*ft_memccpy(void *dst, const void *src, int c, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *dst, const void *src, size_t n);
void		*ft_memmove(void *dst, const void *src, size_t len);
void		*ft_memset(void *b, int c, size_t len);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_putstr_fd(char *s, int fd);
char		*ft_strchr(const char *s, int c);
char		**ft_split(const char *s, char c);
char		**ft_split_quotes(const char *s, char c);
char		**ft_split_pipes(const char *s, char c);
char		*ft_strdup(const char *s1);
char		*ft_strjoin(const char *s1, const char *s2);
size_t		ft_strlcat(char *dst, const char *src, size_t dstsize);
int			ft_strlcpy(char *dst, const char *src, int dstsize);
int			ft_strlen(const char *str);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
char		*ft_strrchr(const char *s, int c);
char		*ft_strtrim(const char *s1, const char *set);
char		*ft_substr(const char *s, int start, int len);
int			ft_tolower(int c);
int			ft_toupper(int c);
int			list_remove(t_list **list, int pos);
int			envar_remove(t_envar **envar, int pos);
int			list_insert(t_list **list, t_list *new, int pos);
int			envar_insert(t_envar **envar, t_envar *new, int pos);
int			ft_envarsize(t_envar *envar);
int			ft_envar_position(t_envar *envar, char *str);
char		*ft_envar_find_content(t_envar *tmp, char *str);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_isalnumqual(int c);
int			count_redir(const char *str, size_t *i,
				_Bool *is_word, int *count_words);
size_t		count_charset(const char *str, char c,
				_Bool *s_quote, _Bool *d_quote);
int			check_redir(const char *str, size_t *i,
				_Bool *s_quote, _Bool *d_quote);
int			ft_free_tab(char **str, size_t size);
int			is_sep(char c, char charset);
void		check_split_quotes(const char *str, size_t i,
				_Bool *s_quote, _Bool *d_quote);

#endif
