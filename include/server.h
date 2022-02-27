#ifndef SERVER_H
#define SERVER_H

#include "mongoose.h"
#include "get_next_line.h"
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <curl/curl.h>

#define HOST "http://0.0.0.0:4242"

typedef struct	s_memory_struct {
  char *memory;
  size_t size;
}				t_memory_struct;

typedef	struct s_data_request{
	FILE		*file;
	int			status;
	char		*treat_data;
}				t_data_request;

typedef	struct s_logs{
	FILE		*file;
	const char	*method;
	int			status;
	int			data_request;
}				t_logs;

//---------------------------- route.c
void 	route(struct mg_connection *c, struct mg_http_message *parsed_request, t_logs *logs);

//---------------------------- api_requester.c
char	*api_requester(void);

//---------------------------- log.c
void	print_log(t_logs *logs, struct mg_http_message *parsed_request);

//---------------------------- log_utils.c
char* get_time (void);

//---------------------------- utils.c
void    load_html_resources(void);
char	*ft_substr(char const *s, unsigned int start, size_t len);
size_t	ft_strlcpy(char *dest, const char *src, size_t size);
char	*strjoin_free(char *s1, char const *s2);
char	**ft_split(char const *s, char c);

char  *index_page;
#endif
