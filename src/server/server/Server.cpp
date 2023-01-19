#include "Server.h"
#include <iostream>
#include <json/json.h>
#include <microhttpd.h>
#include <string.h>

using namespace state;
using namespace std;

const int PORT = 8000;

class RequestData {
    public:
    RequestData() : data() {}

    void appendData(const char *data, size_t size) {
        this->data.append(data, size);
    }

    std::string getData() {
        return data;
    }

    MHD_PostProcessor *postProcessor;

    private:
    std::string data;
};


struct PostProcessor
	{
		char *data;
		int size;
	};

// enum MHD_Result 
// post_iterator(void *cls,
//                 enum MHD_ValueKind kind,
//                 const char *key,
//                 const char *filename,
//                 const char *content_type,
//                 const char *transfer_encoding,
//                 const char *data, uint64_t off, size_t size)
// {
//     return MHD_NO;
// }

enum MHD_Result  post_iterator(void *cls, enum MHD_ValueKind kind, const char *key, const char *filename, const char *content_type, const char *transfer_encoding, const char *data, uint64_t off, size_t size) {
    RequestData *requestData = (RequestData *)cls;
    requestData->appendData(data, size);
    return MHD_YES;
}

namespace server {
    Server::Server()
    {
        
    }

    Server::~Server()
    {

    }

    Server::Server(shared_ptr<State> a_gameState){
        gameState = a_gameState;
    }

    /**
     * @brief Server main router
    */
    int Server::requestHandler(void *cls, MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **ptr) {
        RequestData *requestData = (RequestData *)*ptr;

        if (*ptr == NULL) {
            // Initialize any state for this connection
            *ptr = new RequestData();
            requestData = (RequestData *)*ptr;
            cout << "Here  ptr NUll" << requestData->getData() << " uh " << endl;
        }

        if (std::string(method) == "POST") {
            MHD_set_connection_value(connection, MHD_HEADER_KIND, "Content-Type", "application/json");
            cout << "Here  ptr POST" << endl;
            requestData->appendData(upload_data, *upload_data_size);
        }

        if (*upload_data_size != 0) {
            // More data is coming
            cout << "More data coming " << *upload_data_size << endl;
            requestData->appendData(upload_data, *upload_data_size);
            return MHD_YES;
        }
        else {
            std::cout << "Request Body: " << requestData->getData() << std::endl;
            std::string response = "OK";
            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response.size(), (void *)response.c_str(), MHD_RESPMEM_MUST_COPY);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
            MHD_destroy_response(mhd_response);
            return ret;
        }
    }


    // int Server::requestHandler (void* cls, struct MHD_Connection* connection, const char* url, const char* method, 
    //                             const char* version, const char * upload_data, size_t * upload_data_size, void** ptr){

    //     Server *server = (Server *)cls;

    //     RequestData *requestData = (RequestData *)*ptr;

    // if (*ptr == NULL) {
    //     // Initialize any state for this connection
    //     requestData = new RequestData();
    //     *ptr = requestData;
    //     requestData->postProcessor = MHD_create_post_processor(connection, 1024, &post_iterator, requestData);
    // }

    // if (std::string(method) == "POST") {
    //     MHD_post_process(requestData->postProcessor, upload_data, *upload_data_size);
    // }

    // if (*upload_data_size != 0) {
    //     // More data is coming
    //     return MHD_YES;
    // }
    // else {
    //     // Request complete
    //     MHD_destroy_post_processor(requestData->postProcessor);
    //     std::cout << "Request Body: " << requestData->getData() << std::endl;
    //     std::string response = "OK";
    //     struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response.size(), (void *)response.c_str(), MHD_RESPMEM_MUST_COPY);
    //     int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    //     MHD_destroy_response(mhd_response);
    //     return ret;
    // }
        

    //     // string response;
    //     // if (string(method) == "GET") {
    //     //     response = Server::getHandler(server, connection, url);
    //     // } 
    //     // else if (string(method) == "POST") {
    //     //     struct MHD_PostProcessor *pp;

    //     //     pp = MHD_create_post_processor(connection, 1024, &post_iterator, *ptr);

    //     //     cout << "PP " << pp << endl;    

    //     //     MHD_post_process(pp, upload_data, *upload_data_size);

    //     //     cout << "Here post " << *upload_data_size << endl;
    //     //     cout << "Here " << upload_data << endl;
    //     //     response = Server::postHandler(server, connection, url, upload_data, upload_data_size);
    //     // } else {
    //     //     response = "405: Method Not Allowed";
    //     // }

    //     // struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response.size(), (void *)response.c_str(), MHD_RESPMEM_MUST_COPY);
    //     // int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    //     // MHD_destroy_response(mhd_response);

    //     // return ret;
    // }

    /**
     * @brief GET requests router
    */
    std::string Server::getHandler (Server* a_server, MHD_Connection* con, const char* url)
    {
        string response;

        if (string(url) == "/") {
            Json::Value stateJson = a_server->gameState->serialize();
            response = DataOps::jsonToString(stateJson);
        }
        else {
            response = "404: Not Found";
        }

        return response;
    }

    /**
     * @brief Post requests router
    */
    std::string Server::postHandler (Server* a_server, MHD_Connection* con, const char* url, const char* data, size_t* size)
    {
        string response = "Received POST request";

        // Requête pour initialiser un state avec un nombre de players et de bots
        if(string(url) == "/init"){

            // TO-DO : Convertir la requête en JSON
            cout << "Here " << *size << endl;
            cout << "Here " << data << endl;
            string reqData = string(data);
            //Json::Value reqData = DataOps::stringToJson(string(data)); 

            a_server->gameState->init();
            Json::Value stateJson = a_server->gameState->serialize();
            response = DataOps::jsonToString(stateJson);
        }
        return response;
    }

    /**
     * @brief Lauch the server
    */
    int Server::run(){
        
        struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION, PORT, NULL, NULL, (MHD_AccessHandlerCallback)&Server::requestHandler, this, MHD_OPTION_END);
        if (daemon == NULL) {
            return 1;
        }

        getchar();

        MHD_stop_daemon(daemon);

        return 0;
    }
}