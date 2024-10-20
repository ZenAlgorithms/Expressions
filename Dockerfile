FROM iantorres/boosted:amd64-latest

COPY . .

RUN mkdir build \
    && cd build \
    && cmake .. -DBUILD_TESTS=ON \
    && make \
    && cd ../bin \
    && ./tests

RUN mkdir install \
    && cd install \
    && cmake .. -DBUILD_TESTS=OFF \
    && make \
    && make install