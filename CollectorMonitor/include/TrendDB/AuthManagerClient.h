#pragma once
#include <string>
#include <map>
#include <boost/noncopyable.hpp>
namespace luculent {
	namespace trenddb {
		namespace rpc {
			enum AuthLevel
			{
				kUser = 0,
				kAdmin,
				kSuperadmin,
				kNouser
			};

			enum AuthStatus
			{
				kError = -1,
				kOk = 0,
				kUsernameInvalid = 1,
				kPasswdInvalid = 2,
				kPrivilageInvalid = 3
			};

			struct AuthRtn
			{
				AuthStatus status = kError;
				std::string msg;
			};

			struct AuthInfo
			{
				std::string username;
				std::string passwd;
			};

			struct FullAuthInfo
			{
				AuthInfo info;
				AuthLevel level;
			};

			class AuthManagerClient : public boost::noncopyable
			{
			public:
				virtual AuthRtn Login(const AuthInfo &info) = 0;
				virtual AuthRtn Logout() = 0;
				virtual AuthRtn AuthAdd(const AuthInfo &info) = 0;
				virtual AuthRtn AuthDelete(const AuthInfo &info) = 0;
				virtual AuthRtn AuthEdit(const AuthInfo &previousInfo, const AuthInfo &targetInfo) = 0;
				virtual AuthRtn AuthPrivilageCheck(const AuthInfo &info, AuthLevel* level) = 0;
				virtual AuthRtn AuthPrivilageEdit(const AuthInfo &info, AuthLevel level) = 0;
				virtual AuthRtn AddDb(const AuthInfo &info) = 0;
				virtual AuthRtn DeleteDb(const AuthInfo &info) = 0;
				virtual AuthRtn GetUserCount(std::map<std::string, AuthLevel> *infos) = 0;
				virtual AuthRtn AddLog(const std::string &userName, const std::string &action) = 0;
				virtual AuthRtn GetLog(const std::string &userName, std::vector<std::string> *actionLogs) = 0;
			};
		}
	}
}