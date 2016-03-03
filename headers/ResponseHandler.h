class ResponseHandler
{
public:
	static unsigned int getCodeResponse(const char *request);
	static void handler(int code);
	static char * processingCurrentDirectory(char *response);
};