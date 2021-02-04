#include <iostream>
#include <cstdlib>

/* You can use a third argument on main() to receive the environment settings */
int main(int argc, char *argv[], char *env[])
{
	/* Display all of the environment settings using a loop as follows */
	char **env_ptr;
	for (env_ptr = env; *env_ptr != NULL; env_ptr++)
	{
		std::cout << *env_ptr << std::endl;
	}

	std::cout << "**************************************************" << std::endl;

	/* Alternatively, you can use the getenv() function */
	char *val = getenv("SHELL");
	std::cout << "The user shell is: " << val << std::endl;
	std::cout << "The user path is: " << getenv("PATH") << std::endl;

	return 0;
}
