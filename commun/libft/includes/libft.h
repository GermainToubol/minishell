/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gtoubol <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 15:03:43 by gtoubol           #+#    #+#             */
/*   Updated: 2022/06/01 14:41:54 by gtoubol          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef LIBFT_H
# define LIBFT_H
# include <stddef.h>

/* Vanilla libft */

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

int			ft_isalpha(int c);
int			ft_isdigit(int c);
int			ft_isalnum(int c);
int			ft_isascii(int c);
int			ft_isprint(int c);
size_t		ft_strlen(const char *s);
void		*ft_memset(void *s, int c, size_t n);
void		ft_bzero(void *s, size_t n);
void		*ft_memcpy(void *dest, const void *src, size_t size);
void		*ft_memmove(void *dest, const void *src, size_t size);
size_t		ft_strlcpy(char *dest, const char *src, size_t size);
size_t		ft_strlcat(char *dest, const char *src, size_t size);
int			ft_toupper(int c);
int			ft_tolower(int c);
char		*ft_strchr(const char *s, int c);
char		*ft_strrchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
char		*ft_strnstr(const char *big, const char *s2, size_t len);
int			ft_atoi(const char *s);
void		*ft_calloc(size_t nmemb, size_t size);
char		*ft_strdup(const char *s);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_strtrim(char const *s1, char const *set);
char		**ft_split(char const *s, char c);
void		ft_free_split(char **strs);
char		*ft_itoa(int n);
char		*ft_strmapi(char const *s, char (*f)(unsigned int, char));
void		ft_striteri(char *s, void (*f)(unsigned int, char*));
void		ft_putchar_fd(char c, int fd);
void		ft_putstr_fd(char *s, int fd);
void		ft_putendl_fd(char *s, int fd);
void		ft_putnbr_fd(int n, int fd);
t_list		*ft_lstnew(void *content);
void		ft_lstadd_front(t_list **lst, t_list *new);
int			ft_lstsize(t_list *lst);
t_list		*ft_lstlast(t_list *lst);
void		ft_lstadd_back(t_list **lst, t_list *new);
void		ft_lstdelone(t_list *lst, void (*del)(void *));
void		ft_lstclear(t_list **lst, void (*del)(void *));
void		ft_lstiter(t_list *lst, void (*f)(void *));
t_list		*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *));

/* Get_next_line integration */

# define BUFFER_SIZE 42
# define MAX_FDS 25

typedef struct s_buffer
{
	int		fd;
	size_t	size;
	char	buffer[BUFFER_SIZE];
}	t_buffer;

char		*get_next_line(int fd);
char		*get_next_line_fds(int fd);
t_buffer	*gnl_get_buffer(int fd, t_buffer *buffers);

/* ft_printf integration */

typedef struct s_convert
{
	char	convertion;
	char	alternate;
	char	padd_char;
	char	leftify;
	int		padd_size;
	int		has_precision;
	int		precision;
	char	sign;

}	t_convert;

int			ft_printf(const char *format, ...);
int			ft_fprintf(const int fd, const char *format, ...);

int			ft_printf_char(const int fd, char c, t_convert *convert);
int			ft_printf_str(const int fd, char *str, t_convert *convert);
int			ft_printf_long_hex(const int fd, unsigned long int nbr,
				char *charset,
				t_convert *convert);
int			ft_printf_ptr(const int fd, void	*ptr, t_convert *convert);

int			ft_printf_int(const int fd, int n, t_convert *convert);
int			ft_printf_unsigned(const int fd, unsigned int nbr,
				t_convert *convert);

int			ft_printf_hex_base(const int fd, unsigned int nbr, char *charset,
				t_convert *convert);
int			ft_printf_hex(const int fd, unsigned int nbr, t_convert *convert);
int			ft_printf_hex_caps(const int fd, unsigned int nbr,
				t_convert *convert);

int			ft_printf_percent(const int fd);

int			ft_printf_padding(const int fd, int len, t_convert *convert);
int			ft_atoi_padding(char *format, t_convert *convert);

int			ft_printf_precision(const int fd, t_convert *convert);
int			ft_len_precision(int len, t_convert *convert);
int			ft_atoi_precision(char *format, t_convert *convert);

int			set_arguments(char *format, t_convert *convert);
#endif
