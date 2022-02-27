# BTC Value API

This api shows the value of bitcoin in real time.

The server was created with [Mongoose](https://mongoose.ws/) - an open source embedded HTTP/Websocket/MQTT library for C/C++.
Access the documentation [here.](https://mongoose.ws/documentation/#http)
This server opens an HTTP socket on port 4242 where in the '/' endpoint an HTTP request will be received.

## Prerequisites

- Ubuntu 20.04 (focal) or others Ubuntu-based distros;
- Mongoose lib;
- OpenSSL lib;
- Curl lib;

## HTTP Reference

The BTC Value API will interact with the 'GET' HTTP call method on the '/' endpoint, returning information in JSON format. On other endpoints, it will show an html start page.

## Installation

To start, clone the repository with:

`git clone https://github.com/42sp/42labs-selection-process-v2-gustavdlima.git`

Inside repository, compile the files and run the server:

    make && ./server

In case of TLS ERROR, enable SSL/TLS (using self-signed
certificates in PEM files)

    make tls

# CLI

## About
This program will show in the terminal an interface with the amount of GET requests made in the API.

## Start

To compile enter the ./cli folder and type:

    make

`To update the new requests, compile again.`

Add the current directory to the $PATH environment variable using:

    export PATH=$PATH:$(pwd)

Now install the binary in the /usr/local/bin dependency with:

    sudo make install

Finally, run in your terminal:

    cli

## Contributions
Contributions are welcome.

## License
Free!
