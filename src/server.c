#include "server.h"

static int          g_event_loop = 1;

/* Function to stop infinity loop in main function when ctrl+c is pressed*/
static void sigint(int signum)
{
  (void)signum;
  g_event_loop = 0;
  printf("\n\n[SERVER DOWN]");
}

/* Function to get the method. */
int get_method(struct mg_str method)
{
  if (!strncmp(method.ptr, "GET", method.len))
    return (1);
  return (0);
}

/* An event handler function! Simply calls mg_http_reply() function which serves send simple HTTP response using printf() semantic.
*/
static void server(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
  struct  mg_http_message *parsed_request;
  t_logs  logs;
  int     method;

  if (ev == MG_EV_HTTP_MSG)
  {
    // Cast ev_data to struct mg_http_message, which contains a parsed HTTP request.
    parsed_request = (struct mg_http_message *)ev_data;
    method = get_method(parsed_request->method);
    if (method == 1)
    {
      api_requester();
      route(c, parsed_request, &logs);
    }
    else
    {
      logs.status = 500;
      mg_http_reply(c, logs.status, NULL, "%s", "Wrong METHOD, try GET on URI '/'");
    }
    print_log(&logs, parsed_request);
  }
  (void) fn_data;
}

int main(void)
{
  struct mg_mgr mgr;                            // Init event manager struct

  printf("\nServer [ON]!\n\nTo access, try localhost:4242/\n");
  signal(SIGINT, sigint);                       // Start signal
  load_html_resources();                        // load html file content
  mg_mgr_init(&mgr);                            // Init event manager
  if(!mg_http_listen(&mgr, HOST, server, NULL)) // Create HTTP listener
    return (0);
  while(g_event_loop)
    mg_mgr_poll(&mgr, 1000);             // Infinite event loop
  free(index_page);
  mg_mgr_free(&mgr);                            // Close and free
  return 0;
}
