#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	y;
	size_t	i;
	char	*str;

	i = 0;
	y = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(str = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[y])
		str[i++] = s2[y++];
	str[i] = '\0';
	return (str);
}

int		get_next_line(int fd, char **line)
{
	char	buf[2];
	int		sr;
	char	*tmp;

	sr = 0;
	buf[1] = '\0';
	if (!line)
		return (-1);
	if (!(*line = malloc(1)))
		return (-1);
	**line = 0;
	if (fd < 0 || !line || read(fd, buf, 0) < 0)
		return (0);
	while ((sr = read(fd, buf, 1)) > 0)
	{
		if (sr == -1)
			exit(0);
		if (*buf != '\n')
		{
			tmp = *line;
			*line = ft_strjoin(*line, buf);
			free(tmp);
		}
		else
			break ;
	}
	return (sr);
}

double    ft_how_many(char *line, int len)
{
    double  i;
    double  p;
    double  res;
    char    symb;

    symb = *line;
    line++;
    i = 1;
    while (*line)
    {
        if (symb == *line)
            i++;
        line++;
    }
    p = i / len;
    res = - (p * log2(p));
    return (res);
}

double    ft_iter(char *line)
{
    int     i;
    char    *str;
    int     arr[129];
    double  res;
    int     len;

    i = 0;
    while (i < 128)
        arr[i++] = 0;
    res = 0;
    len = strlen(line);
    str = line;
    while (*str)
    {
        if (arr[(int)*str] == 0)
        {
            res += ft_how_many(str, len);
            arr[(int)*str] = 1;
        }
        str++;
    }
    return (res);
}

void    ft_start(char   *name)
{
    int     fd;
    char    *line;
    char    *res;
    char    *tmp;
    double  entropy;

    fd  = open(name, O_RDONLY);
    res = malloc(1);
    res[0] = 0;
    while (get_next_line(fd, &line))
    {
        tmp = res;
        res = ft_strjoin(res, line);
        free(tmp);
        free(line);
    }
    tmp = res;
    res = ft_strjoin(res, line);
    free(tmp);
    free(line);
    entropy = ft_iter(res);
    printf("%f", entropy);
    free(res);
}

int     main(int argc, char *argv[])
{
    if (argc != 2)
        return (1);
    else
        ft_start(argv[1]);
    return (0);
}