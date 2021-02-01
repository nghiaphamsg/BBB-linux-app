<h1> A C/C++ Web Client Using OpenSSL </h1>

## 1. Intro
- Sometimes it is necessary to communicate securely between a client and a server. For example, if you are sending a username and password to an online service. In addition, particular care should be taken in applications where the Beagle board can actuate motors or relays a malicious attack could cause physical destruction. One way to implement secure communications is to use the OpenSSL toolkit.
- OpenSSL ( www.openssl.org ) is a toolkit that implements Secure Sockets Layer (SSL), Transport Layer Security (TLS), and a cryptography library. This library
can be installed using the following:
```shell
  sudo apt install openssl libssl-dev
```
## 2. Usage 
- OpenSSL is a complex and comprehensive toolkit that can be used to encrypt all types of communications.
1. The TCP socket connection is formed to the HTTP secure (i.e., HTTPS) port, which is port **443** by default.
2. The SSL library is initialized using the `SSL_Library_init()` function.
3. An SSL context object is used to establish the TLS/SSL connection. The security and certificate options can be set in this object.
4. The network connection is assigned to an SSL object and a handshake is performed using the `SSL_connect()` function.
5. The `SSL_read()` and `SSL_write()` functions are used.
6. The `SSL_free()` function is used to shut down the TLS/SSL connection, freeing the socket and SSL context objects.

## 3. Testing
- Compile:
```shell
  g++ webClientSSL.cpp -o webClientSSL -lcrypto -lssl
```

- Run:
```shell
  ./webClientSSL www.google.com
```

- Logs:
```
**START**
HTTP/1.1 200 OK
Date: Mon, 01 Feb 2021 07:57:40 GMT
Expires: -1
Cache-Control: private, max-age=0
Content-Type: text/html; charset=ISO-8859-1
P3P: CP="This is not a P3P policy! See g.co/p3phelp for more info."
Server: gws
X-XSS-Protection: 0
X-Frame-Options: SAMEORIGIN
Set-Cookie: 1P_JAR=2021-02-01-07; expires=Wed, 03-Mar-2021 07:57:40 GMT; path=/; domain=.google.com; Secure
Set-Cookie: NID=208=qDMAcz73xB9TsJPlATSz9JzXjqIbjgY3MINxTLHG2C1sh9gME2ZAGPExK6N-Q7AdKaAgxOe7W-J9EoRRWtLFRb3LJ0EyYYiGx6hjI4lG2_ZNHpkircfHM7TOtQ7_L00JxgwBDVCostkxElzhaVffFCpEzpqvIDDv_UkNx8zGY6c; expires=Tue, 03-Aug-2021 07:57:40 GMT; path=/; domain=.google.com; HttpOnly
Alt-Svc: h3-29=":443"; ma=2592000,h3-T051=":443"; ma=2592000,h3-Q050=":443"; ma=2592000,h3-Q046=":443"; ma=2592000,h3-Q043=":443"; ma=2592000,quic=":443"; ma=2592000; v="46,43"
Accept-Ranges: none
Vary: Accept-Encoding
Connection: close
Transfer-Encoding: chunked

53bc
<!doctype html><html itemscope="" itemtype="http://schema.org/WebPage" lang="ja"><head><meta content="&#19990;&#30028;&#20013;&#12398;&#12354;&#12425;&#12422;&#12427;&#24773;&#22577;&#12434;&#26908;&#32034;&#12377;&#12427;&#12383;&#12417;&#12398;&#12484;&#12540;&#12523;&#12434;&#25552;&#20379;&#12375;&#12390;&#12356;&#12414;&#12377;&#12290;&#12373;&#12414;&#12374;&#12414;&#12394;&#26908;&#32034;&#27231;&#33021;&#12434;&#27963;&#29992;&#12375
**END**
```
