#include "../includes/Bot.hpp"

bool Bot::running = true;

Bot::Bot(): fd(-1), port(-1), password(""), ip("") {}
Bot::Bot(const Bot &src): fd(src.fd), port(src.port), password(src.password), ip(src.ip) {}
Bot Bot::operator=(const Bot &src) {
	this->fd = src.fd;
	this->port = src.port;
	this->password = src.password;
	this->ip = src.ip;

	return (*this);
}
Bot::~Bot() {}

Bot::Bot(const int port, const std::string password, const std::string ip):
fd(-1), port(port), password(password), ip(ip) {
	loadWelcomeMessages();
}

void Bot::signalHandler(int signum) {
	(void) signum;
	std::cout << std::endl << "Closing Bot..." << std::endl;
	running = false;
}

void Bot::loadWelcomeMessages() {
	std::ifstream	msgFile(FILE);
	if (!msgFile.is_open()) {
		throw(std::runtime_error("Can't open message file"));
	}

	std::string line;
	while (std::getline(msgFile, line)) {
		this->messages.push_back(line);
	}

	printMessage();
}

void Bot::printMessage() {
	for (size_t i = 0; i < this->messages.size(); i++) {
		std::cout << this->messages[i] << std::endl;
	}

}

void Bot::connect() {
	
}
