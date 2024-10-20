FROM iantorres/boosted:latest

COPY . .

RUN cmake . -DBUILD_TESTS=ON \
    && make \
    && cd bin \
    && ./tests