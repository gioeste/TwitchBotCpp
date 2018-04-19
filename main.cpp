#include "TwitchChatBot.h"
#include <Windows.h>
int main()
{
	try
	{
		ChatBot chatBot("q238ppjlz9olgtowmz1alkqy05qval", "laskdjlaskdj12");

		chatBot.onCommand("test", [&](const std::string UserID)
		{
			chatBot.send_message("Hello");
		});

		try
		{
			chatBot.run();
		}
		catch(std::exception& e)
		{
			std::cout << "What : " + (std::string)(e.what()) << std::endl;
		}

		std::cout << " 이벤트 핸들러 끝 " << std::endl;
		system("pause");
		return 0;
	}catch(std::exception& e)
	{
		e.what();
	}
}