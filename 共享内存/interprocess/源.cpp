//#include <boost/interprocess/shared_memory_object.hpp>
//#include <boost/interprocess/windows_shared_memory.hpp> 
//#include <boost/interprocess/mapped_region.hpp> 
//#include <iostream> 
//#include <windows.h>
//int main()
//{
//	//用 boost::interprocess::open_or_create 作为参数，共享内存如果存在就将其打开，否则创建之。
//	boost::interprocess::shared_memory_object shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write);
//	shdmem.truncate(1024);
//	std::cout << shdmem.get_name() << std::endl;
//	boost::interprocess::offset_t size;
//	if (shdmem.get_size(size))
//		std::cout << size << std::endl;
//	/*每个应用程序需要映射共享内存到自己的地址空间上，这是通过 boost::interprocess::mapped_region 类实现的*/
//	//boost::interprocess::mapped_region region(shdmem, boost::interprocess::read_write);
//	//std::cout << std::hex << "0x" << region.get_address() << std::endl;
//	//std::cout << std::dec << region.get_size() << std::endl;
//	boost::interprocess::mapped_region region2(shdmem, boost::interprocess::read_only);
//	std::cout << std::hex << "0x" << region2.get_address() << std::endl;
//	std::cout << std::dec << region2.get_size() << std::endl;
//	//int *i1 = static_cast<int*>(region.get_address());
//	//*i1 = 99;
//	int *i2 = static_cast<int*>(region2.get_address());
//	std::cout << *i2 << std::endl;
//	//bool removed = boost::interprocess::shared_memory_object::remove("Highscore");
//	//std::cout << removed << std::endl;
//	//多数Unix操作系统，包括Linux，一旦系统重新启动，都会自动删除共享内存,在 Windows 或 Mac OS X上，remove() 必须调用
//	//这两种系统实际上将共享内存存储在持久化的文件上，此文件在系统重启后还是存在的。
//	/*boost::interprocess::windows_shared_memory shdmem(boost::interprocess::open_or_create, "Highscore", boost::interprocess::read_write, 1024);*/
//
//}
//#include <boost/interprocess/managed_shared_memory.hpp> 
//#include <iostream> 
//
//int main()
//{
//	boost::interprocess::shared_memory_object::remove("Highscore");
//	boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "Highscore", 1024);
//	int *i = managed_shm.construct<int>("Integer")(99);
//	std::cout << *i << std::endl;
//	std::pair<int*, std::size_t> p = managed_shm.find<int>("Integer");//find返回或者是一个指向这个特定对象的指针，或者是0表示给定名称的对象没有找到
//	if (p.first)
//		std::cout << *p.first << std::endl;
//	int *i = managed_shm.construct<int>("Integer")[10](99);
//	//find() 函数返回的对象能够区分是单个对象还是数组对象。 对于前者，second 的值是1，而对于后者，它的值是数组元素的个数。
//
//}
#include <boost/interprocess/managed_shared_memory.hpp> 
#include <boost/interprocess/sync/named_mutex.hpp> 
#include <boost/interprocess/sync/named_condition.hpp> 
#include <boost/interprocess/sync/scoped_lock.hpp> 
#include <iostream> 

int main()
{
	boost::interprocess::managed_shared_memory managed_shm(boost::interprocess::open_or_create, "shm", 1024);
	int *i = managed_shm.find_or_construct<int>("Integer")(0);
	boost::interprocess::named_mutex named_mtx(boost::interprocess::open_or_create, "mtx");
	boost::interprocess::named_condition named_cnd(boost::interprocess::open_or_create, "cnd");
	boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(named_mtx);
	while (*i < 10)
	{
		if (*i % 2 == 0)
		{
			++(*i);
			named_cnd.notify_all();
			named_cnd.wait(lock);
		}
		else
		{
			std::cout << *i << std::endl;
			++(*i);
			named_cnd.notify_all();
			named_cnd.wait(lock);
		}
	}
	named_cnd.notify_all();
	boost::interprocess::shared_memory_object::remove("shm");
	boost::interprocess::named_mutex::remove("mtx");
	boost::interprocess::named_condition::remove("cnd");
	system("pause");
	return 0;
}