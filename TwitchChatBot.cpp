#include "TwitchChatBot.h"
#include <boost/asio.hpp>


//TwitchChatBot::TwitchChatBot(std::string Tocken, std::string UserName): IsConnect(false),
//                                                                        IRCSocket(io_service),
//                                                                        isFirst(false)
//{
//	try
//	{
//		readBuffer = new char[2048];
//
//		tcp::resolver resolver(io_service);
//
//		boost::asio::connect(IRCSocket, resolver.resolve("irc.chat.twitch.tv", std::to_string(6667)));
//
//		IRCSocket.async_receive(boost::asio::buffer(readBuffer, 2048),
//		                        std::bind(&TwitchChatBot::AsyncRecvHandler, this,
//		                                  std::placeholders::_1,
//		                                  std::placeholders::_2));
//
//		std::string requestConnectBuffer = "PASS oauth:" + Tocken + "\r\n";
//		std::string BostUserName = "NICK " + UserName + "\r\n";
//		std::string JoinPrivateChannel = "JOIN #laskdjlaskdj12 \r\n";
//
//		printLog("전송 준비중");
//
//		IRCSocket.send(boost::asio::buffer(requestConnectBuffer.c_str(), requestConnectBuffer.size()));
//		IRCSocket.send(boost::asio::buffer(BostUserName.c_str(), BostUserName.size()));
//		IRCSocket.send(boost::asio::buffer(JoinPrivateChannel.c_str(), JoinPrivateChannel.size()));
//	}
//	catch (std::exception& e)
//	{
//		e.what();
//		IsConnect = false;
//	}
//}
//
//
//TwitchChatBot::~TwitchChatBot()
//{
//}
//
//void TwitchChatBot::run()
//{
//	io_service.run();
//}
//
//void TwitchChatBot::AsyncRecvHandler(const boost::system::error_code& error, const std::size_t& readByteSize)
//{
//	if (error)
//	{
//		printLog(error.message());
//		return;
//	}
//
//	printLog(readBuffer);
//	std::string readByte(readBuffer, readByteSize);
//
//	if (!isFirst)
//	{
//		if (readByte.find(":tmi.twitch.tv 001") == std::string::npos)
//		{
//			printLog("Reply가 실패했습니다.");
//			return;
//		}
//	}
//
//	if (readByte.find("PING :tmi.twitch.tv") != std::string::npos)
//	{
//		std::string TestString = "PONG :tmi.twitch.tv \r\n";
//		IRCSocket.send(boost::asio::buffer(TestString.c_str(), TestString.size()));
//
//		IRCSocket.async_receive(boost::asio::buffer(readBuffer, 2048),
//		                        std::bind(&TwitchChatBot::AsyncRecvHandler, this,
//		                                  std::placeholders::_1,
//		                                  std::placeholders::_2));
//
//		memset(readBuffer, 0, 2048);
//
//		return;
//	}
//
//	else if (readByte.find("!testone") != std::string::npos)
//	{
//		printLog("Test를 전송 ");
//		std::string TestString = "PRIVMSG #laskdjlaskdj12 :This is test \r\n";
//
//		IRCSocket.send(boost::asio::buffer(TestString.c_str(), TestString.size()));
//
//		IRCSocket.async_receive(boost::asio::buffer(readBuffer, 2048),
//		                        std::bind(&TwitchChatBot::AsyncRecvHandler, this,
//		                                  std::placeholders::_1,
//		                                  std::placeholders::_2));
//
//		memset(readBuffer, 0, 2048);
//
//		return;
//	}
//
//	else if (readByte.find("!testtwo") != std::string::npos)
//	{
//		printLog("Test를 전송 ");;
//		std::string TestString = "PRIVMSG #laskdjlaskdj12 HelloWorld123 \r\n";
//		IRCSocket.send(boost::asio::buffer(TestString.c_str(), TestString.size()));
//
//		IRCSocket.async_receive(boost::asio::buffer(readBuffer, 2048),
//		                        std::bind(&TwitchChatBot::AsyncRecvHandler, this,
//		                                  std::placeholders::_1,
//		                                  std::placeholders::_2));
//
//		memset(readBuffer, 0, 2048);
//
//		return;
//	}
//
//
//	else if (readByte.find("!commandlist") != std::string::npos)
//	{
//		printLog("List를 전송");
//
//		std::string CommandList = "!test :현재 커맨드의 테스트를 출력합니다. !List : 현재 커맨드 리스트를 출력합니다.\r\n";
//		std::string TestString = "PRIVMSG #laskdjlaskdj12 :" + CommandList;
//
//		IRCSocket.send(boost::asio::buffer(TestString.c_str(), TestString.size()));
//
//		IRCSocket.async_receive(boost::asio::buffer(readBuffer, 2048),
//		                        std::bind(&TwitchChatBot::AsyncRecvHandler, this,
//		                                  std::placeholders::_1,
//		                                  std::placeholders::_2));
//
//		memset(readBuffer, 0, 2048);
//
//		return;
//	}
//
//	isFirst = true;
//
//	memset(readBuffer, 0, 2048);
//	//
//	//	IRCSocket.receive(boost::asio::buffer(readBuffer, 2048));
//	//
//	//	printLog(readBuffer);
//	//
//	//	std::string SayHello = "PRIVMSG #laskdjlaskdj12 HelloWorld123 \r\n";
//	//
//	//	IRCSocket.send(boost::asio::buffer(SayHello.c_str(), SayHello.size()));
//	//
//	//	memset(readBuffer, 0, 2048);
//	//
//	//	IRCSocket.receive(boost::asio::buffer(readBuffer, 2048));
//	//
//	//	printLog(readBuffer);
//
//	IRCSocket.async_receive(boost::asio::buffer(readBuffer, 2048),
//	                        std::bind(&TwitchChatBot::AsyncRecvHandler, this,
//	                                  std::placeholders::_1,
//	                                  std::placeholders::_2));
//}


ChatBot::ChatBot(std::string Tocken, std::string UserName) : //work(io_service),
	tocken(Tocken),
	io_service(),
	work(new boost::asio::io_service::work(io_service)),
	socket(io_service),
	username(UserName)
{
	recvBuffer.resize(2048);
}

ChatBot::~ChatBot()
{
	io_service.reset();
}

void ChatBot::onCommand(const std::string Command, CommandListener listener)
{
	std::string command = "!" + Command + "\r\n";

	commandList[command] = listener;
}

void ChatBot::connect_twitch_IRC()
{
	std::string requestConnectBuffer = "PASS oauth:" + tocken + "\r\n";
	std::string BostUserName = "NICK hello \r\n";

	socket.send(boost::asio::buffer(requestConnectBuffer.c_str(), requestConnectBuffer.size()));
	socket.send(boost::asio::buffer(BostUserName.c_str(), BostUserName.size()));;

	std::string recvConnect;
	recvConnect.resize(2048);

	socket.receive(boost::asio::buffer(recvConnect));

	printLog(recvConnect);

	if (recvConnect.find(":tmi.twitch.tv 001") == std::string::npos)
	{
		throw std::runtime_error("Connect is fail : " + recvConnect);
	}
}

void ChatBot::enter_room()
{
	std::string JoinPrivateChannel = "JOIN #" + username + " \r\n";

	socket.send(boost::asio::buffer(JoinPrivateChannel.c_str(), JoinPrivateChannel.size()));

	std::string recvJoin;
	recvJoin.resize(2048);

	socket.receive(boost::asio::buffer(recvJoin));

	printLog(recvJoin);

	std::string joinresult;
	joinresult.resize(2048);

	socket.receive(boost::asio::buffer(joinresult));
	printLog(joinresult);

	if (joinresult.find(":End of /NAMES list") == std::string::npos)
	{
		throw std::runtime_error("Join Channel is Fail : " + recvJoin);
	}
}

void ChatBot::run()
{
	tcp::resolver resolver(io_service);

	boost::asio::connect(socket, resolver.resolve("irc.chat.twitch.tv", std::to_string(6667)));

	connect_twitch_IRC();

	enter_room();

	io_service.post(std::bind(&ChatBot::add_async_handler, this));

	io_service.run();
}

void ChatBot::send_message(std::string Message)
{
	if (socket.is_open())
	{
		std::string TestString = "PRIVMSG #" + username + " :" + Message + "\r\n";

		socket.send(boost::asio::buffer(TestString));
	}
}

void ChatBot::async_recv_handler(const boost::system::error_code& error, const std::size_t& readByteSize)
{
	try
	{
		std::string recvCommand(recvBuffer.c_str(), readByteSize);
		if (error)
		{
			throw std::runtime_error(error.message());
		}

		if (recvCommand.find("PING :tmi.twitch.tv") != std::string::npos)
		{
			std::string TestString = "PONG :tmi.twitch.tv \r\n";
			socket.send(boost::asio::buffer(TestString.c_str(), TestString.size()));
		}

		else
		{
			std::string privMessagetemplate = "PRIVMSG #" + username + " :";
			size_t position = recvCommand.find("PRIVMSG #" + username + " :");

			size_t parseCommand = position + privMessagetemplate.size();

			std::string command = recvCommand.substr(parseCommand);

			printLog("Command : " + command);

			if (commandList.find(command) != commandList.end())
			{
				printLog("커맨드 수신");

				size_t first_parse_name = command.find(":");
				size_t second_parse_name = command.find("!");

				std::string user_name = command.substr(first_parse_name + 1, second_parse_name - 1);

				CommandListener Handler = commandList.find(command)->second;

				Handler(username);
			}

			command.clear();
			command.resize(2048);
		}

		add_async_handler();

	}
	catch (std::exception& e)
	{
		e.what();
	}
}
