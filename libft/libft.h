/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpambo <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 22:41:57 by rpambo            #+#    #+#             */
/*   Updated: 2024/06/19 22:42:03 by rpambo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include "get_next_line.h"

void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_itoa(int n);
void	*ft_memset(void *s, int c, size_t n);
void	ft_putendl_fd(char *s, int fd);
void	ft_putnbr_fd(int n, int fd);
void	ft_putstr_fd(char *s, int fd);
int		ft_strcmp(const char *s1, const char *s2);
char	*ft_strjoin(char const *s1, char const *s2);
size_t	ft_strlen(const char *s);
int	ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strdup(const char *s);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_isdigit(int c);
char	*ft_strtrim(char const *s1, char const *set);
int	ft_atoi(const char *nptr);
char	*ft_strchr(const char *s, int c);
int	ft_fd_lines_counter(char *file_path);
int	ft_isalpha(int c);
int	ft_err_msg(char *msg, int int_return);
char	*ft_strstr(char *str, char *to_find);
void	ft_free_matriz(char **dp_char);
int	ft_isspace(char c);
char	**ft_matrizdup(char **to_dup);
int	ft_matriz_big_line(char **matriz);
int	ft_matrizlen(char **to_count);
void	ft_bzero(void *s, size_t n);
char	**ft_split(char const *s, char c);

#endif
