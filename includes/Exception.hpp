
#pragma once
#include <exception>

class Exception
{
	public:
		class getaddrinfo : public std::exception {
			const char	*what() const throw() {
				return "getadddrinfo() error: ";
			}
		};

		class bind : public std::exception {
			const char	*what() const throw() {
				return "bind() error: ";
			}
		};

		class listen : public std::exception {
			const char	*what() const throw() {
				return "listen() error: ";
			}
		};

		class poll : public std::exception {
			const char	*what() const throw() {
				return "poll() error: ";
			}
		};
};
