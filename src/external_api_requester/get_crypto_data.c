#include "server.h"

/* Free in Matrix*/
static void free_matrix(char **matrix)
{
	int	i;

	i = 0;
	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

/* Trate and take the btc value line*/
static char *data_treat(char *data)
{
	int		i;
	char	*temp;

	i = 0;
	while (data[i] != '.')
		i++;
	i += 2;
	temp = strndup(data, i);
	return (temp);
}

/* Create or update the content from btc_data*/
char *get_crypto_data(void)
{
	t_data_request	*data;
	int	fd;
	char	*line;
	char	*aux;
	char	**matrix;

	data = calloc(1, sizeof(data));
	fd = open("btc_data.txt", O_RDONLY);
	if (fd < 0)
		return NULL;
	aux = ft_strdup("");
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		aux = strjoin_free(aux, line);
		free(line);
	}
	matrix = ft_split(aux, ',');
	data->treat_data = data_treat(matrix[8]);
	free_matrix(matrix);
	close(fd);
	return (data->treat_data);
}
