class ResponseHandler
{
public:
	static unsigned int getCodeResponse(const char *request); // return code response from server
	static void handler(int code); // handle response code from server
};