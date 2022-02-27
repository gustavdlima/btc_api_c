#include "server.h"

/* Create/Open log file and print the content of the request*/
void	print_log(t_logs *logs, struct mg_http_message *parsed_request)
{
	char 	*time;

  	logs->file = fopen("./log/log.log", "a");
	time = get_time();
	if(logs->file != NULL)
	{
		fprintf(logs->file, "\nRequest\n");
		// 											STATUS CODE
		fprintf(logs->file, "STATUS CODE: ");
		fprintf(logs->file, "%d\n", logs->status);
		// 											METHOD
		fprintf(logs->file, "METHOD: ");
		if (strncmp(parsed_request->method.ptr, "GET", parsed_request->method.len))
			fprintf(logs->file, "log.error{WRONG METHOD} ");
		fprintf(logs->file, "%.*s\n", (int)parsed_request->method.len, parsed_request->method.ptr);
		// 											URI
		fprintf(logs->file, "URI: ");
		if (strncmp(parsed_request->uri.ptr, "/", parsed_request->uri.len))
			fprintf(logs->file, "log.error{WRONG URI} ");
		fprintf(logs->file, "%.*s\n", (int)parsed_request->uri.len, parsed_request->uri.ptr);
		// 											PROTOCOL
		fprintf(logs->file, "PROTO: ");
		fprintf(logs->file, "%.*s\n", (int)parsed_request->proto.len, parsed_request->proto.ptr);
		// 											BODY
		fprintf(logs->file, "Body: ");
		fprintf(logs->file, "%.*s\n", (int)parsed_request->body.len, parsed_request->body.ptr);
		// 											DATE & TIME
		fprintf(logs->file, "Date & Time: ");
		fprintf(logs->file, "%s", time);
	}
	fclose(logs->file);
}
