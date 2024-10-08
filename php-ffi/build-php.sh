#!/usr/bin/env bash

# Just a scratch file for some reasonable configure flags

./configure \
    --with-openssl \
    --with-curl \
    --with-zlib \
    --with-readline \
    --with-gettext \
    --enable-bcmath \
    --enable-calendar \
    --enable-dba \
    --enable-exif \
    --enable-fpm \
    --enable-ftp \
    --enable-gd \
    --enable-gd-native-ttf \
    --enable-intl \
    --enable-mbregex \
    --enable-mbstring \
    --enable-mysqlnd \
    --enable-pcntl \
    --enable-shmop \
    --enable-soap \
    --enable-sockets \
    --enable-sysvmsg \
    --enable-sysvsem \
    --enable-sysvshm \
    --enable-wddx \
    --enable-zip \
    --with-curl \
    --with-external-gd \
    --with-fpm-group=www-data \
    --with-fpm-user=www-data \
    --with-gd \
    --with-mhash \
    --with-mysql=mysqlnd \
    --with-mysqli=mysqlnd \
    --with-pdo-mysql=mysqlnd \
    --with-xmlrpc \
    --with-zip \
    --with-zlib \
    --without-snmp \
    --with-pear \
    --with-pdo-pgsql \
    --without-pcre-jit \
    --with-ffi \
    --prefix=/home/somrlik/.asdf/installs/php/8.3.10 \
    --sysconfdir=/home/somrlik/.asdf/installs/php/8.3.10 \
    --with-config-file-path=/home/somrlik/.asdf/installs/php/8.3.10 \
    --with-config-file-scan-dir=/home/somrlik/.asdf/installs/php/8.3.10/conf.d
