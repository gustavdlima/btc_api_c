#include "server.h"

/* Get BITCOIN information from another API.*/
void	api_requester(void)
{
	CURL 	*curl;
	FILE 	*file;
	int		result;

	file = fopen("./btc_data.txt", "wb");
	curl = curl_easy_init();
	curl_easy_setopt(curl, CURLOPT_URL, "https://api.coincap.io/v2/assets/bitcoin");
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, file);
	curl_easy_setopt(curl, CURLOPT_FAILONERROR, 1L);
	result = curl_easy_perform(curl);
	fclose(file);
	curl_easy_cleanup(curl);
	(void)result;
	return ;
}
