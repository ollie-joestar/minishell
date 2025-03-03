/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oohnivch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/09 13:21:39 by oohnivch          #+#    #+#             */
/*   Updated: 2025/03/03 19:44:49 by oohnivch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <sys/types.h>
//	Char
int		ft_isalnum(int c);
int		ft_isalpha(int c);
int		ft_isascii(int c);
int		ft_isdigit(int c);
int		ft_isprint(int c);
int		ft_tolower(int c);
int		ft_toupper(int c);
int		ft_isspace(int c);
//	String
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	**ft_split(const char *s, char c);
char	**ft_split_set(const char *s, char *c);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
void	ft_striteri(char *s, void (*f)(unsigned int, char *));
char	*ft_strjoin(const char *s1, const char *s2);
size_t	ft_strlcat(char *dest, const char *src, size_t size);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
size_t	ft_strlen(const char *str);
char	*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strnstr(const char *haystack, const char *needle, size_t n);
char	*ft_strrchr(const char *str, int c);
char	*ft_strtrim(const char *s1, const char *set);
char	*ft_substr(const char *s, unsigned int start, size_t len);
//	Memory
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t count, size_t n);
void	*ft_memchr(const void *str, int c, size_t n);
int		ft_memcmp(const void *s1, const void *s2, size_t n);
void	*ft_memcpy(void	*dest, const void *src, size_t n);
void	*ft_memmove(void *dest, const void *src, size_t n);
void	*ft_memset(void *str, int c, size_t n);
//	File
int		ft_putchar_fd(char c, int fd);
int		ft_putstr_fd(char *s, int fd);
int		ft_putendl_fd(char *s, int fd);
int		ft_putnbr_fd(int n, int fd);
//	Struct for bonus
typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;
//	Bonus
void	ft_lstadd_back(t_list **lst, t_list *new_node);
void	ft_lstadd_front(t_list **lst, t_list *new_node);
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	ft_lstdelone(t_list *lst, void (*del)(void *));
void	ft_lstiter(t_list *lst, void (*f)(void *));
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstnew(void *content);
t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));
int		ft_lstsize(t_list *lst);
//	Printf
int		ft_printf(const char *str, ...);
int		ft_printerr(const char *str, ...);
int		ft_putchar(int c);
int		ft_putstr(char *s);
int		ft_putnbr(int nb);
int		ft_putuint(unsigned int nb);
int		ft_putptr(unsigned long nb);
int		ft_puthex(unsigned long n, const char format);
//	Get next line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

char	*get_next_line(int fd, int *exitcode);
char	*get_next_line_2(int fd, char **buffer, int *exit_code);
size_t	ft_nlcheck(char const *s);
char	*ft_buffjoin(char **s1, char **s2);
void	ft_free(char **something);
size_t	ft_linelen(char *buffer);
char	*ft_parseline(char **buffer, int *exitcode);

#endif
