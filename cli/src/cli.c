#include "cli.h"

/* Print the head from the terminal interface*/
static void head()
{
	int	i;
	int	j;
	int	col;
	int	row;

	col = 43;
	row = 3;
	for (i = 0; i <= row; i++)
	{
		for (j = 0; j <= col; j++)
		{
			//									TOP LINE
			if (i == 0 && j == 0)
				printf("-");
			else if (i == 0 && j == col)
				printf("-\n");
			else if (i == 0 && j < col
					&& j != 0)
				printf("-");

			//									MID LINE
			if (i == 1 && j == 0)
				printf("--");
			else if (i == 2 && j == 15)
				printf("--\n");
			if (i == 1 && j == 5)
				printf("METHOD");
			if (i == 1 && j == 7)
				printf("--");
			if (i == 1 && j == 9)
				printf("PATH");
			if (i == 1 && j == 11)
				printf("--");
			if (i == 1 && j == 13)
				printf("TOTAL REQUESTS");
			else if (i == 1 && j > 1 && j < 15)
			printf(" ");

			//									BASE LINE
			if (i == 3 && j == 0)
				printf("-");
			else if (i == 3 && j == col)
				printf("-\n");
			else if (i == 3 && j < col
					&& j != 0)
				printf("-");
		}
	}
}

/* Print the body from the terminal interface*/
static void	body (int method_count)
{
	int	i;
	int	j;
	int	col;
	int	row;
	int	responsive;
	int	aux;

	responsive = 0;
	col = 43;
	row =  3;
	for (i = 0; i <= row; i++)
	{
		for (j = 0; j <= col; j++)
		{
			//									FIRST LINE
			if (i == 0 && j == 0)
				printf("--");
			else if (i == 0 && j == col)
				printf("--\n");
			if (i == 0 && j == 11)
				printf("--");
			if (i == 0 && j == 19)
				printf("--");
			else if (i == 0 && j < 37)
				printf(" ");
			//									SECOND LINE
			if (responsive == 0)
			{
				if (i == 1 && j == 0)
					printf("--");
				if (i == 1 && j == 4)
					printf("GET");
				if (i == 1 && j == 8)
					printf("--");
				if (i == 1 && j == 11)
					printf("/");
				if (i == 1 && j == 15)
					printf("--");
				if (i == 1 && j < 18)
					printf(" ");
			}
			if (i == 1 && j == 18 && method_count < 10)
			{
				responsive = 26;
				printf("%6d", method_count);
			}
			if (i == 1 && j == 18 && method_count > 9 && method_count < 1000)
			{
				responsive = 25;
				printf("%7d", method_count);
			}
			if (i == 1 && j == 18 && method_count > 999 && method_count < 1000000)
			{
				responsive = 24;
				printf("%8d", method_count);
			}
			if (i == 1 && j == 18 && method_count > 999999
				&& method_count < 100000000)
			{
				responsive = 22;
				printf("%10d", method_count);
			}
			if (responsive > 0)
			{
				if (i == 1 && j < responsive)
					printf(" ");
				if (i == 1 && j == responsive)
					printf("--\n");
			}
			//									THIRD LINE
			if (i == 2 && j == 0)
				printf("--");
			else if (i == 2 && j == col)
				printf("--\n");
			if (i == 2 && j == 11)
				printf("--");
			if (i == 2 && j == 19)
				printf("--");
			else if (i == 2 && j < 37)
				printf(" ");
			//									FOURTH LINE
			if (i == 3 && j == 0)
				printf("-");
			else if (i == 3 && j == col)
				printf("-\n");
			else if (i == 3 && j < 43)
				printf("-");
		}
	}
}

/* Print the footer from the terminal interface*/
static void	footer (t_time *time)
{
	int	i;
	int	j;
	int	col;
	int	row;

	col = 43;
	row = 1;
	for (i = 0; i < row; i++)
	{
		for (j = 0; j < col; j++)
		{
			if (i == 0 && j < 3)
				printf(" ");
			if (i == 0 && j == 5)
				printf("--");
			if (i == 0 && j == 5)
				printf("Last request: ");
			if (i == 0 && j == 6)
			{
				printf("%d/%s/%d ", time->day, time->month, time->year);
				printf("at %s", time->time);
			}
			if (i == 0 && j == 7)
				printf("--\n");
		}
	}
}

/* Counts the number of GET requests made to the API*/
static int	count_method(char **matrix)
{
	int i = 0;
	int	count = 0;
	while (matrix[i])
	{
		if (!strncmp(matrix[i], "GET", 3))
			count++;
		i++;
	}
	return (count);
}

/* Take the Last Request Time from the API*/
static void last_request_time(char **matrix, t_time *time)
{
	int i;
	int	count;

	count = 0;
	time->time = ft_strdup("");
	time->month = ft_strdup("");
	while (matrix[count])
		count++;
	time->time = strjoin_free(time->time, matrix[count - 2]);
	time->month = strjoin_free(time->month, matrix[count - 4]);
	time->day = atoi(matrix[count - 3]);
	time->year = atoi(matrix[count - 1]);
}

/* Free in time struct and matrix.*/
static void free_all(t_time *time, char **matrix)
{
	int	i = 0;

	free(time->month);
	free(time->time);

	while(matrix[i])
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}

void	main(void)
{
	int fd;
	char *aux;
	char *line;
	char **matrix;
	t_time	time;

	fd = open("../log/log.log", O_RDONLY);
	aux = ft_strdup("");
	while(1)
	{
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		aux = strjoin_free(aux, line);
		free(line);
	}
	matrix = ft_split(aux, ' ');
	free(aux);
	last_request_time(matrix, &time);
	head();
	body(count_method(matrix));
	footer(&time);
	free_all(&time, matrix);
	close(fd);
}
