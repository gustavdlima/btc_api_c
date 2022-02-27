#include "server.h"

/* Get the route of the URI and send a simple HTTP response using printf() semantic.
*/
void  route(struct mg_connection *c, struct mg_http_message *parsed_request, t_logs *logs)
{
  t_data_request  *data;

  data = calloc(1, sizeof(data));
  data->treat_data = get_crypto_data();
  if (mg_http_match_uri(parsed_request, "/"))
  {
    logs->status = 200;
    // printf("%d\n", logs.status);
    mg_http_reply(c, logs->status, "", "{%s\"}\n", data->treat_data);
    free(data->treat_data);
  }
  else
  {
    logs->status = 404;
    mg_http_reply(c, logs->status, "", "%s", index_page);
  }
}
