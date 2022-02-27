FROM gcc:4.9

COPY . /usr/src/app
WORKDIR /usr/src/app

RUN make

EXPOSE 4242

CMD ["./server"]
