FROM ubuntu

RUN echo "APT::Get::Assume-Yes \"true\";\nAPT::Get::force-yes \"true\";\n" > /etc/apt/apt.conf

RUN apt update
RUN apt install gcc
RUN apt install g++
RUN apt install cmake
RUN apt install python3
RUN apt install valgrind
RUN apt install ninja-build
RUN apt install git
RUN apt install clang-format

WORKDIR /root/
COPY . c-databases

ARG CACHEBUST=1
RUN git clone --depth 1 https://github.com/meni-adin/c-errors.git _github.com/meni-adin/c-errors
RUN git clone --depth 1 https://github.com/google/googletest.git _github.com/google/googletest


WORKDIR /root/c-databases
CMD ["python3", "scripts/build_and_test.py"]
