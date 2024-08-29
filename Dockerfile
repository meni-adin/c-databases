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

WORKDIR /root/
COPY . .

CMD ["python3", "scripts/in_docker_runner.py"]
