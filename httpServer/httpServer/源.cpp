#define _CRT_SECURE_NO_WARNINGS
#define For(n) for(int index = 0;index < n;++index)
//#include "vld.h"
//#include "output_Container.h"
#include "crow.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;
int main()
{
	crow::SimpleApp app;

	CROW_ROUTE(app, "/api/*")
		.methods("POST"_method, "GET"_method)
		([=](const crow::request& req, crow::response &res) {
		try
		{
			std::cout << "/collect/start req body = {}" << req.body << std::endl;
			res.add_header("Content-Type", "application/json;charset=UTF-8");
			res.write("start collect");
			res.end();
		}
		catch (const std::exception&e)
		{
			std::cout << "catch exception {}" << e.what() << std::endl;
			res.write(e.what());
			res.end();
		}
	});
	app.port(8088)
		//.multithreaded()
		.run();
	system("pause");
	return 0;
}