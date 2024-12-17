# Webserv - École 42 Project

This project is an HTTP server implementation in C++98, inspired by **Nginx**. The goal is to create a lightweight, event-driven server that can handle multiple clients simultaneously, manage incoming HTTP requests, and respond according to the HTTP/1.1 protocol.

## Features

- Compliant with HTTP/1.1 protocol.
- Handles multiple clients concurrently using **multiplexing** (epoll).
- Basic request parsing and response generation.
- Support for GET, POST, and DELETE methods.
- Configurable through a custom configuration file.
- Directory listing, file serving, and CGI support for dynamic content.

## Project Structure

- **src/**: Source files for the server, request/response handling, and utilities.
- **inc/**: Header files and interfaces.
- **cfg/**: Configuration files for testing different setups.
- **www/**: Directory containing sample files for testing file serving and CGI.


# Webserv Project Roadmap

## 1. Socket Setup 
- class: `HTTPServer`
- [ ] Create a listening socket.
- [ ] Bind the socket to a port.
- [ ] Set the socket to listen for connections.
- [ ] Accept incoming client connections.

## 2. HTTP Request Parsing
- class: `HTTPRequest`
- [ ] Read raw data from the client socket.
- [ ] Parse the HTTP method, URI, and headers.
- [ ] Handle basic validation of the HTTP request.


## 3. HTTP Response Generation
class: `HTTPResponse`
- [ ] Construct a basic HTTP response (status line, headers, body).
- [ ] Send the response to the client.
- [ ] Close the client socket.


## 4. Event Multiplexing
class: `Multiplexer`
- [ ] Integrate `select`, `poll`, or `epoll` for handling multiple connections.
- [ ] Process multiple clients concurrently without blocking.


## 5. Configuration Handling
class: `ConfigParser`
- [ ] Implement a basic configuration file parser.
- [ ] Use configuration data to set up server parameters (port, root, routes).


## 6. Static File Serving
class: `FileHandler`
- [ ] Serve static files from a directory.
- [ ] Handle directory traversal and error cases (404, 403).


## 7. Routing
class: `Router`
- [ ] Create a routing system to match URIs with actions (e.g., static files, CGI scripts).
- [ ] Allow configuration of custom routes.


## 8. CGI Support
class: `CGIHandler`
- [ ] Implement CGI script execution.
- [ ] Capture script output and send it as an HTTP response.


## 9. HTTP/1.1 Features
class: `Connection`
- [ ] Add support for persistent connections (keep-alive).
- [ ] Implement chunked transfer encoding.
- [ ] Handle additional HTTP headers.


## 10. Error Handling
class: `ErrorHandler`
- [ ] Implement error handling for invalid requests and server issues.
- [ ] Serve error pages for common HTTP status codes (e.g., 404, 500).


## 11. Advanced Features (Optional)
class: `Logger, SSLHandler`
- [ ] Add support for POST and DELETE methods.
- [ ] Log requests and server activity.
- [ ] Implement SSL/TLS for HTTPS.

