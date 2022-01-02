FROM ubuntu:20.04
LABEL description = "A basic build environment"

RUN apt-get update && apt-get install -y g++ zip openssh-server make cmake libsqlite3-dev

RUN mkdir -p /var/run/sshd

RUN echo 'PasswordAuthentication yes' >> /etc/ssh/sshd_config && ssh-keygen -A

EXPOSE 22
