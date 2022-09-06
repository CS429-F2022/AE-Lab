FROM ubuntu:18.04
RUN apt-get update && apt-get install -y build-essential gcc-aarch64-linux-gnu

WORKDIR /work
CMD make gcd hello qsort test_switch vecsum