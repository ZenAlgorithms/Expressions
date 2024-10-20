FROM iantorres/boosted:amd64-latest

COPY . .

RUN cmake . -DBUILD_TESTS=ON \
    && make \
    && cd bin \
    && ./tests