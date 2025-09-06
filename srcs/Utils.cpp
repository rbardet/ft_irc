#include "../includes/Utils.hpp"

const std::string getParam(int cmdLength, const std::string &line) {
	std::string args = line.substr(cmdLength);
	std::string firstParam = args.substr(0, args.find(' '));
	return(firstParam);
}
