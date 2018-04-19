#pragma once

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <iostream>
#include <functional>
#include <string>

#define printLog(X) std::cout<<__FILE__ + std::string(__FUNCTION__) + ":" + std::to_string(__LINE__) + ": " + X <<std::endl;

//using boost::asio::ip::tcp;
//
//typedef std::function<void(const std::string UserName)> CommandListener;
//
//class TwitchChatBot
//{
//public:
//	TwitchChatBot(std::string Tocken, std::string UserName);
//	~TwitchChatBot();
//
//	typedef std::function<void(const std::string UserName)> CommandListener;
//
////	template<class T>
//	void onCommand(std::string command, CommandListener listener);
//
//	void run();
//
////	bool isConnect();
//
////protected:
//	void AsyncRecvHandler(const boost::system::error_code& error, const std::size_t& readByteSize);
//
//private:
//	char* readBuffer;
//	CommandListener onCommandHandler;
//
//	boost::asio::io_service io_service;
//	tcp::socket IRCSocket;
//	bool IsConnect;
//
//	bool isFirst;
//};


typedef std::function<void(const std::string UserID)> CommandListener;

using boost::asio::ip::tcp;

class ChatBot
{
public:
	ChatBot(std::string Tocken, std::string UserName);

	~ChatBot();

	void onCommand(const std::string Command, CommandListener listener);

	void run();

	void send_message(std::string Message);

protected:
	void async_recv_handler(const boost::system::error_code& error, const std::size_t& readByteSize);

	void connect_twitch_IRC();

	void enter_room();

	void add_async_handler()
	{
		socket.async_read_some(boost::asio::buffer(recvBuffer),
			std::bind(&ChatBot::async_recv_handler, this,
				std::placeholders::_1,
				std::placeholders::_2));
	}
private:
	std::string tocken;

	std::string username;

	std::string recvBuffer;
	
	boost::asio::io_service io_service;

	tcp::socket socket;

	std::shared_ptr<boost::asio::io_service::work> work;

	std::map<std::string, CommandListener> commandList;

	std::string ErrorMessage;
};

