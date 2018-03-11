#include <vector>
#include <libwebsockets.h>
#include <time.h>

const int listen_port = 8008;



struct lws_context *g_pcontext;

int callback_wstest(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len);

static struct lws_protocols protocols[] = {
	{
		.name = "ws-test",
		.callback = callback_wstest,
		.per_session_data_size = 0,
	},
	{
		NULL, NULL, 0		/* End of list */
	}
};
char str[] = "{\"name\":\"position\",\"args\":{\"latitude\":\"100\",\"longitude\":\"100\"}}";

int callback_wstest(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	int n;

	fprintf(stderr,"wstest callbacked  reasin = %d\n", (int)reason);
	
	
	switch (reason) {
	case LWS_CALLBACK_ESTABLISHED:
		break;

	case LWS_CALLBACK_SERVER_WRITEABLE:
		{
			n = lws_write(wsi, (unsigned char*)str, strlen(str), LWS_WRITE_TEXT);
		}
		break;
		
	case LWS_CALLBACK_RECEIVE:
		if (in != NULL && len > 0)
		{
			fprintf(stderr,"data in: %s\n",in);
		}
		break;
		
	case LWS_CALLBACK_CLOSED:
	case LWS_CALLBACK_CLIENT_CONNECTION_ERROR:
		break;

	case LWS_CALLBACK_CLIENT_ESTABLISHED:
		break;

	case LWS_CALLBACK_CLIENT_RECEIVE:

		break;

	case LWS_CALLBACK_CLIENT_WRITEABLE:

	default:
		break;
	}

	return 0;
}

int main(int argc, char *srgv[])
{
	struct lws_context_creation_info info;
	int ret;
	struct timespec tp,op;
	
	memset(&info, 0, sizeof info);
	
	
	info.port = listen_port;
	info.iface = NULL;	//all interface
	info.protocols = protocols;
	info.ssl_cert_filepath = NULL;
	info.ssl_private_key_filepath = NULL;
	info.gid = -1;
	info.uid = -1;
	info.extensions = NULL;
	info.options = LWS_SERVER_OPTION_DISABLE_IPV6 | LWS_SERVER_OPTION_VALIDATE_UTF8; //LWS_SERVER_OPTION_UNIX_SOCK

	g_pcontext = lws_create_context(&info);
	if (g_pcontext == NULL) {
		lwsl_err("libwebsocket init failed\n");
		return -1;
	}
	
	clock_gettime(CLOCK_MONOTONIC, &op);
	
	do
	{
		lws_service(g_pcontext, 1000);
		clock_gettime(CLOCK_MONOTONIC, &tp);
		if ((tp.tv_sec - op.tv_sec) >= 1)
		{
			clock_gettime(CLOCK_MONOTONIC, &op);
			lws_callback_on_writable_all_protocol(g_pcontext,protocols);
		}
	} while(1);
	
	return 0;
}
