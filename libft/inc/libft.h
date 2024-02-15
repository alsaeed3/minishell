/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alsaeed <alsaeed@student.42abudhabi.ae>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/11 17:20:59 by alsaeed           #+#    #+#             */
/*   Updated: 2024/02/15 16:19:03 by alsaeed          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <limits.h>
# include <stdint.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>

/* Libc functions */
int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
int			ft_isspace(char c);
void		*ft_memset(void *b, int c, size_t len);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dst, void *src, size_t n);
void		*ft_memmove(void *dst, void *src, size_t len);
size_t		ft_strlcpy(char *dst, char *src, size_t dstsize);
size_t		ft_strlcat(char *dst, char *src, size_t dstsize);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(char *s, size_t c);
char		*ft_strrchr(char *s, size_t c);
int			ft_strncmp(char *s1, char *s2, size_t n);
int			ft_strcmp(char *s1, char *s2);
void		*ft_memchr(void *s, int c, size_t n);
int			ft_memcmp(void *s1, void *s2, size_t n);
char		*ft_strnstr(char *haystack, char *needle, size_t len);
int			ft_atoi(char *s, int *error);
void		*ft_calloc(size_t count, size_t size);
char		*ft_strdup(char *s1);
char		*ft_strdup_nonl(char *s1);
char		*ft_strstr(char *haystack, char *needle);
char		*ft_strncpy(char *dest, char *src, size_t n);
char		*ft_strcpy(char *dest, char *src);

/* Singly-linked list functions */
typedef struct s_list
{
	int				data;
	int				index;
	struct s_list	*next;
}	t_list;

int			ft_lstsize(t_list *lst);
t_list		*ft_lstadd_back(t_list *head, int integer);
void		ft_lstadd_front(t_list *head, int integer);
t_list		*ft_lst_last(t_list *head);
void		ft_deallocate_lst(t_list **stack);
int			ft_array_size(char **array);

/* ft_printf */
int			ft_putchar(char c);
int			ft_putstr(char *str);
int			ft_putnbr(int n);
int			print_hex(unsigned int n, char c);
int			print_pointer(unsigned long n);
int			print_undec(unsigned int n);
int			ft_printf(char *str, ...);

/* get_next_line */
size_t		ft_strlen(char *str);
size_t		ft_strlen_nl(char *str);
char		*ft_strjoin(char *s1, char *s2);
char		*ret_line(char *s);
char		*update_stash(char *s);
char		*get_next_line(int fd);

/* Additional functions */
char		*ft_substr(char *s, unsigned int start, size_t len);
char		*ft_strjoin_sp(int ac, char **av);
char		*ft_strtrim(char *s1, char *set);
char		**ft_split(char *s, char c);
char		*ft_itoa(int n);
char		*ft_strmapi(char *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
void		ft_free_array(char ***array);
int			ft_isspace_str(char *s);
int			ft_space_arg(char **s);
int			ft_array_size(char **array);
char		**ft_get_array(int ac, char **av);
void		free_set_null(void **ptr);

#endif