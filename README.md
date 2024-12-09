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
