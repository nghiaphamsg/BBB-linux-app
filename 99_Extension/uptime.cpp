#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char* argv[]){

   std::fstream fs;
   float uptime, idletime;

   fs.open("/proc/uptime", std::fstream::in);
   fs >> uptime >> idletime;

   std::cout << "The system up time is " << uptime/60 << " minutes.\n";
   std::cout << "It was idle for " << idletime/60 << " minutes, or "
             <<  100*(idletime/uptime) << "%\n";

   fs.close();
   return 0;
}
