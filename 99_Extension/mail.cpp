/*  @brief: send mail example
 *  @date: 2021/02/01
 *  @pakage: sudo apt-get install ssmtp mailutils
 *  @config: /etc/ssmtp/ssmtp.conf
 *  @usage: ./build mail.cpp x86
 *          ./mail
 */
#include <iostream>
#include <string>
#include <sstream>

int main()
{
    std::string to("nghiaphamsg@gmail.com");
    std::string subject("Test Mail");
    std::string body("Something like...");

    std::stringstream cmd;
    cmd << "echo \""<< body <<"\" | mail -s \""<< subject <<"\" "<< to;
    int result = system(cmd.str().c_str());
    std::cout << "command: " << cmd.str() << std::endl;

    return result;
}