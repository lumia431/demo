#include "pch.h"
#include "uaTrans.h"
using namespace trans;
UaTrans::UaTrans(TransInfo &info, std::vector<std::string> &tagNames)
	:m_info(info), m_logger(info.logger)
{
	//port = atoi(info.uaAddr.c_str());
	std::vector<std::string> tagName(tagNames);

	POINT_VALUE temp;
	for (int i = 0; i < tagNames.size(); ++i)
	{
		temp.tagName = tagNames[i];
		temp.value = 0.0;
		point.push_back(temp);
	}
}

int trans::UaTrans::Connect()
{
	p->newOpcuaServer(m_info.uaPort, point);
	std::thread t(&trans::UaTrans::OPCUArun, this);
	t.detach();

	return 0;
}

int trans::UaTrans::Send(const std::vector<std::string>& tagNames, const std::vector<TagData>& tagDatalist)
{
	point.clear();
	if (tagNames.size() != tagDatalist.size())
	{
		return -1;
	}


	POINT_VALUE temp;
	for (int i = 0; i < tagNames.size(); ++i)
	{
		temp.tagName = tagNames[i];
		temp.value=tagDatalist[i].value;
		point.push_back(temp);
	}

	p->writeNewData(point);
	return 0;
}

int trans::UaTrans::Reconnect()
{
	return 0;
}

void trans::UaTrans::OPCUArun()
{
	p->status();
}





