#include "WebRestApi.h"
#include <iostream>



bool WebRestApi::GetRequest() {
	// initialize RestClient
	RestClient::init();

	// get a connection object
	RestClient::Connection* conn = new RestClient::Connection(serverAdr);

	// configure basic auth
	conn->SetBasicAuth("apikey", apikey);

	// set connection timeout to 5s
	conn->SetTimeout(5);


	// set headers
	RestClient::HeaderFields headers;
	headers["Accept"] = "application/json";
	conn->SetHeaders(headers);

	r = conn->get(std::string("/queries/") + std::to_string(querryID));

	// deinit RestClient. After calling this you have to call RestClient::init()
	// again before you can use it
	RestClient::disable();

	return validResponse = r.code == 200;	
}

nlohmann::json WebRestApi::GetParsedResponse() const {
	if(validResponse){
		try
		{
			return nlohmann::json::parse(r.body);
		}
		catch (nlohmann::json::type_error& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return nlohmann::json();
}