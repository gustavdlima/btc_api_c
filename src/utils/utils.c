#include "server.h"

/* Take the resources from the .html front-end */
void    load_html_resources(void)
{
    long    length;
    FILE    *f = fopen ("./frontend/index.html", "rb");
    if (f)
    {
        fseek (f, 0, SEEK_END);
        length = ftell (f);
        fseek (f, 0, SEEK_SET);
        index_page = malloc (length);
        if (index_page)
            fread (index_page, 1, length, f);
        fclose (f);
    }
}

static size_t	min(int a, int b)
{
	if (a > b)
		return (b);
	return (a);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	index;

	index = 0;
	if (!dest && !src && !size)
		return (0);
	if (size > 0)
	{
		while (index < size - 1 && src[index] != '\0')
		{
			dest[index] = src[index];
			index++;
		}
		dest[index] = '\0';
	}
	return (strlen(src));
}

char	*ft_strchr(const char *s, int c)
{
	int		index;
	char	character;

	index = 0;
	character = (char)c;
	while (s[index] != '\0')
	{
		if (s[index] == character)
			return ((char *)s + index);
		index++;
	}
	if (character == '\0')
		return ((char *)s + index);
	return (0);
}

char	*ft_strdup(const char *str)
{
	char	*string;
	size_t	index;

	index = 0;
	string = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!string)
		return (0);
	while (str[index])
	{
		string[index] = str[index];
		index++;
	}
	string[index] = '\0';
	return (string);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	index;
	size_t	max_size;
	char	*substring;

	if (!s)
		return (0);
	index = strlen((char *)s);
	if (start < index)
		max_size = min(strlen(s + start), len);
	else
		return (strdup(""));
	substring = calloc(max_size + 1, sizeof(char));
	if (!substring)
		return (0);
	ft_strlcpy(substring, &s[start], max_size + 1);
	return (substring);
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	size_t	i;
	size_t	j;
	size_t	size;

	if (!s1 || !s2)
		return (NULL);
	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * size);
	if (!str)
		return (NULL);
	i = -1;
	while (s1[++i])
		str[i] = s1[i];
	j = -1;
	while (s2[++j])
		str[i + j] = s2[j];
	str[i + j] = '\0';
	return (str);
}

char	*strjoin_free(char *s1, char const *s2)
{
	char	*nstring;
	size_t	i;
	size_t	a;

	nstring = malloc(strlen(s1) + strlen(s2) + 1);
	i = 0;
	a = 0;
	if (nstring == 0)
		return (0);
	while (s1[i] != '\0')
	{
		nstring[i] = s1[i];
		i++;
	}
	while (s2[a] != '\0')
	{
		nstring[i + a] = s2[a];
		a++;
	}
	nstring[i + a] = '\0';
	free(s1);
	s1 = NULL;
	return (nstring);
}

static size_t	count_len_words(char const *str, char delimiter)
{
	size_t	i;

	i = 0;
	while (str[i] != delimiter && str[i])
		i++;
	return (i);
}

static size_t	count_words(char const *str, char delimiter)
{
	size_t	i;
	size_t	aux;

	if (!*str)
		return (0);
	i = 1;
	aux = 0;
	while (str[i])
	{
		if (str[i] != delimiter && str[i])
		{
			aux++;
			while (str[i] != delimiter && str[i])
				i++;
		}
		else
			i++;
	}
	return (aux);
}

char	**ft_split(char const *s, char c)
{
	size_t	n_words;
	size_t	n_chars;
	size_t	index;
	char	**string;

	if (!s)
		return (0);
	n_words = count_words(s, c);
	string = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!string)
		return (0);
	index = 0;
	while (index < n_words)
	{
		while (*s && *s == c)
			s++;
		n_chars = count_len_words(s, c);
		string[index] = ft_substr(s, 0, n_chars);
		s += n_chars + 1;
		index++;
	}
	string[index] = 0;
	return (string);
}
