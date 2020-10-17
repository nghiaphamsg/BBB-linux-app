<h1> A Beagle Board Web Client </h1>

A Beagle board can initiate contact with a web server using HTTP requests to send and receive data. A C/C++ program is written that uses TCP sockets to build a basic web browser, which can communicate over HTTP or, if necessary, securely over secure HTTP (HTTPS).

## 1. Explode about network communications

- A socket is a network endpoint that is defined using an IP address and a port number. An IP address (version 4) is simply a `32-bit` number, which is represented as four eight-bit values (e.g., 192.168.7.2)
- A port number is a `16-bit` unsigned integer **(0–65,535)** that can be used to enable multiple simultaneous communications to a single IP address. 
- Ports **under 1,024** are generally restricted to root access to prevent users from hijacking core services (e.g., 80 for HTTP, 20/21 for FTP, 22 for SSH, 443 for HTTPS).

- Socket type:
    - Stream socket: use the **Transmission Control Protocol (TCP)**, which provides for reliable transfer of data where the time of transmission is not a critical factor. Its reliability means that it is used for services such as HTTP, e-mail (SMTP), and FTP, where data must be reliably and correctly transferred.
    - Datagram socket: uses the **User Datagram Protocol (UDP)**, which is less reliable but much faster than TCP, as there is no error-checking for packets. Time-critical applications such as voice over IP (VoIP) use UDP, as errors in the data will be presented in the output as noise, but the conversation will not be paused awaiting lost data to be resent.

## 2. C/C++ web client
The code performs the following steps:

- Step 1: The server name is passed to the program as a string argument. The program converts this string into an IP address (stored in the `hostent` structure) using the `gethostbyname()` function.
- Step 2: The client creates a TCP socket using the `socket()` system call.
- Step 3: The `hostent` structure and a port number (**80**) are used to create a `sockaddr_in` structure that specifies the endpoint address to which to connect the socket. This structure also sets the address family to be IP-based `(AF_INET)` and the network byte order.
- Step 4: The TCP socket is connected to the server using the `connect()` system call the communications channel is now open.
- Step 5: An HTTP request is sent to the server using the `write()` system call and a fixed-length response is read from the server using the `read()` system call. The HTML response is displayed.
- Step 6: The client disconnects, and the socket is closed using `close()`.

