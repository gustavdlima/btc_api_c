FROM gcc:4.9

COPY . /usr/src/api
WORKDIR /usr/src/api

RUN make

EXPOSE 4242

CMD ["./server"]
