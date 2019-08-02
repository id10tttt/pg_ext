FROM debian:buster

LABEL maintainer="1di0t"

# Generate locale C.UTF-8 for postgres and general locale data
ENV LANG C.UTF-8

RUN apt update && apt upgrade -y && \
    apt install vim apt-transport-https ca-certificates gnupg make gcc sudo wget curl systemd -y

ENV PG_VERSION=9.6
RUN wget -q https://www.postgresql.org/media/keys/ACCC4CF8.asc -O - | apt-key add -
# install latest postgresql-client
RUN set -x; \
        echo 'deb http://apt.postgresql.org/pub/repos/apt/ buster-pgdg main' > etc/apt/sources.list.d/pgdg.list \
        && apt-get update  \
        && apt-get install -y postgresql-client-${PG_VERSION} postgresql-server-dev-${PG_VERSION} postgresql-${PG_VERSION} \
        && rm -rf /var/lib/apt/lists/*

RUN mkdir new_town_method
RUN mkdir expected
RUN mkdir -p new_town_method/sql

COPY ./new_town_method.c new_town_method/
COPY ./new_town_method.control new_town_method/
COPY ./new_town_method--0.0.1.sql new_town_method/
COPY ./Makefile new_town_method/
COPY ./Dockerfile new_town_method/
COPY ./sql/new_town_method_test.sql new_town_method/sql/
COPY ./expected/new_town_method_test.out expected/

RUN useradd ext_postgres
RUN echo "ext_postgres      ALL=(ALL:ALL) NOPASSWD:ALL" >> /etc/sudoers

RUN cd new_town_method && make && make install

# RUN sudo service postgresql start 
# RUN psql -c "create extension test_function_hello;" && psql -c "select test_function_hello(1,2,3,4);"
USER ext_postgres
