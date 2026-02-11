## 001_showip.c explaination

* int argc --> counts the no of words you type in the terminal
* char *argv[] --> stores the words typed in the terminal

```
int main(int argc, char *argv[])

running ./filename hello world

argc = 3;
argv[0] = "./filename"
argv[1] = "hello"
argv[2] = "world"
```

* hints --> is a struct
* res and p are pointers
* char ipstr[INET6_ADDRSTRLEN];

array of data type char

INET6_ADDRSTRLEN: The Size. This is a constant number (usually defined as 46) hidden in the header files.

* fprintf - guides where to save the output
>fprintf(where, "whatever");

```
if (argc != 2) {
        fprintf(stderr,"usage: showip hostname\n");
        return 1;
    }
```

arguments should be exactly two

```
    memset(&hints, 0, sizeof hints);
    hints.ai_family = AF_UNSPEC;  // Either IPv4 or IPv6
    hints.ai_socktype = SOCK_STREAM; //SOCK_DGRAM if you wanna use datagram instead of tcp
```
memset [PREDEFINED FUNCTION]: It fills a block of memory with a specific value.
here, writes 0 into every single byte of hints variable.

if `memset(&hints, 1, sizeof hints);`

It fills every single 8-bit byte with the value 1.
If you fill all 4 bytes with 1 (binary 00000001), the computer reads it as:
00000001 00000001 00000001 00000001

That equals 16,843,009, not 1.


```
if ((status = getaddrinfo(argv[1], NULL, &hints, &res)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status));
        return 2;
    }
```

* `getaddrinfo(Node, Port/Service, Hints, Result)`

* After this line, res points to the data.

* getaddrinfo(Node, Service, Hints, Result) returns 0 when everything works.

* `fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(status))`
* `gai_strerror` stands for Get Address Info String Error

* `stderr`: Predefined pointer (Standard Error). Directs the message to the error console instead of standard output.
* `status`: User-defined variable. The numeric error code passed into the translator.

```
for(p = res;p != NULL; p = p->ai_next) {
        void *addr;
        char *ipver;
        struct sockaddr_in *ipv4;
        struct sockaddr_in6 *ipv6;

        // get the pointer to the address itself,
        // different fields in IPv4 and IPv6:
        if (p->ai_family == AF_INET) { // IPv4
            ipv4 = (struct sockaddr_in *)p->ai_addr;
            addr = &(ipv4->sin_addr);
            ipver = "IPv4";
        } else { // IPv6
            ipv6 = (struct sockaddr_in6 *)p->ai_addr;
            addr = &(ipv6->sin6_addr);
            ipver = "IPv6";
        }
```

* `res` contains the head of the linked list you get from getaddrinfo.
*  `p` starts from head of the linked list `res` and stops when reaches the end of the list.