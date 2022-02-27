#include "server.h"


static void	free_matrix(char **matrix)
{
	int	i;

	while (i < 4)
	{
		free(matrix[i]);
		i++;
	}
	free(matrix);
}
/* Take the data into a *chunk of memory */
static size_t	WriteMemoryCallback(void *content, size_t size, size_t nmemb, void *userp)
{
	size_t realsize;
	t_memory_struct *mem;
	char *ptr;

	realsize = size * nmemb;
	mem = (t_memory_struct *)userp;
	ptr = realloc(mem->memory, mem->size + realsize + 1);
	if(!ptr)
		return 0;
	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), content, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;
	return (realsize);
}

/* Get BITCOIN information from another API.*/
char	*api_requester(void)
{
	CURL *curl;
	CURLcode result;
	t_memory_struct chunk;
	char **matrix;
	char *aux;

	chunk.memory = malloc(1);	// will be grown as needed by the realloc above
	chunk.size = 0;				// no data at this point
	curl_global_init(CURL_GLOBAL_ALL);
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://www.mercadobitcoin.net/api/BTC/ticker/");

	// send all data to WriteMemoryCallback function
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

	// get it
	result = curl_easy_perform(curl);

	// check for errors
	if (result != CURLE_OK)
		printf("curl_easy_perform() failed\n");
	else
	{
		matrix = ft_split(chunk.memory, ',');
		aux = strdup("");
		aux = strjoin_free(aux, matrix[4]);
		free_matrix(matrix);
	}
	// cleanup curl stuff
	curl_easy_cleanup(curl);
	free(chunk.memory);
	curl_global_cleanup();
	return (aux);
}
