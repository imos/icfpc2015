FROM ubuntu:14.04
MAINTAINER imos@docker.com

# Install SSH server.
RUN apt-get update -qq && \
    apt-get install -qqy openssh-server
RUN mkdir /var/run/sshd

# Install useful tools.
RUN apt-get update -qq && \
    apt-get install -qqy \
        build-essential devscripts ubuntu-standard software-properties-common \
        screen lxc traceroute gdb \
        vim git subversion mercurial cmake make \
        dos2unix nkf curl xz-utils graphviz imagemagick

# Install C++.
RUN apt-get update -qq && apt-get install -qqy clang-3.6 clang-format-3.6

# Install scripts (python, php, ruby).
RUN apt-get update -qq && \
    apt-get install -qqy \
        python3.4 ruby1.9.3 rubygems-integration php5-cli python-pip

# Install C#.
RUN apt-get update -qq && apt-get install -qqy mono-devel

# Install Haskell.
RUN apt-get update -qq && apt-get install -qqy haskell-platform && cabal update

# Install Go.
RUN apt-get update -qq && apt-get install -qqy golang

# Install Java.
RUN echo oracle-java8-installer shared/accepted-oracle-license-v1-1 \
        select true | debconf-set-selections && \
    add-apt-repository -y ppa:webupd8team/java && \
    apt-get update -qq && apt-get install -qqy oracle-java8-installer

# Install JavaScript.
# RUN wget -O - https://deb.nodesource.com/setup | bash && \
#     apt-get install -qqy nodejs npm

# Install AWS command.
RUN pip install awscli

# Install utilities for Bazel.
RUN apt-get update -qq && \
    apt-get install -qqy libarchive-dev pkg-config zip g++ zlib1g-dev

# Install Apache-PHP.
RUN apt-get update -qq && \
    apt-get install -qqy apache2 libapache2-mod-php5 php5-mysql \
                         php5-gd php5-curl php-pear php-apc
RUN sed -i 's/AllowOverride None/AllowOverride All/g' /etc/apache2/apache2.conf
RUN a2enmod rewrite

# Add ninelet user.
RUN useradd \
        --home-dir=/home/ninelet \
        --create-home \
        --uid=20602 \
        --user-group \
        --shell=/bin/bash \
        ninelet
RUN mkdir -p /home/ninelet/.ssh
RUN echo 'ssh-rsa AAAAB3NzaC1yc2EAAAADAQABAAABAQCrHaL3kdZ2RekCdpkie3fsiv2yVyyWRBOO6Q68Kr+tFStRqtF8q1/UoeteUIOxzwKaAmHoaM9PkItdMBki0BLQDimCZwjjbkosritGDMTJXGd21O72mWaTv+nfq+/ishCdt6gdBYXTejvpPJhq8ZMYhTYJZkWqlGO2CKrWcnHHu1HhnValeqNWS5nh8BULOTMKaixjdzXIkWgm8HyiewvqjZXC3tZlfFDErRpiS7SYfJHd4PujjFCNyiVxZ5yOvEGMXQa1UFxQlfX8H+lAr6qObK50osAdUbvjjbhIhMvZT2higSNNtv/yiaLRnLbbOHomObvqxob5TUVdCkazXX3N imos@docker' > /home/ninelet/.ssh/authorized_keys
RUN echo 'ninelet ALL=(ALL:ALL) NOPASSWD: ALL' > /etc/sudoers.d/ninelet
RUN echo 'ninelet:$1$yLREWjDA$pR8cjWbX984KgIzMu71Z4.' | chpasswd --encrypted
RUN echo 'source /mirror/github/bin/bashrc' >> /home/ninelet/.bashrc
RUN echo 'export PATH="/mirror/global/bin:${PATH}"' >> /home/ninelet/.bashrc
RUN echo 'export PATH="/mirror/github/bin:${PATH}"' >> /home/ninelet/.bashrc
RUN echo 'export PATH="/mirror/dropbox/bin:${PATH}"' >> /home/ninelet/.bashrc
RUN echo 'export PATH="/home/ninelet/bin:${PATH}"' >> /home/ninelet/.bashrc

# Set language settings.
RUN echo 'LANGUAGE=en_US.UTF8' >> /etc/environment
RUN echo 'LANG=en_US.UTF8' >> /etc/environment
RUN echo 'LC_ALL=C.UTF-8' >> /etc/environment

# Set a ninecluster role.
RUN echo 'NINECLUSTER=ninelet' >> /etc/environment

# Create useful symbolic links.
RUN ln -s /alloc/global /home/ninelet/global
RUN ln -s /mirror/github /home/ninelet/github
RUN ln -s /alloc/dropbox /home/ninelet/Dropbox

# Set up bazel settings.
RUN echo 'build --package_path %workspace%:/mirror/global/bazel/base_workspace' >> /home/ninelet/.bazelrc
RUN echo 'query --package_path %workspace%:/mirror/global/bazel/base_workspace' >> /home/ninelet/.bazelrc
RUN echo 'fetch --package_path %workspace%:/mirror/global/bazel/base_workspace' >> /home/ninelet/.bazelrc

# Set up imos/bin.
RUN grep '/usr/imos/bin:' /etc/environment || \
    sed -i 's%PATH="%PATH="/usr/imos/bin:%' /etc/environment
ENV PATH /usr/imos/bin:$PATH
RUN grep '/alloc/github/bin:' /etc/environment || \
    sed -i 's%PATH="%PATH="/alloc/github/bin:%' /etc/environment
ENV PATH /alloc/github/bin:$PATH
RUN echo "Defaults secure_path = \"$PATH\"" >/etc/sudoers.d/00-secure_path
RUN mkdir -p /usr/imos/bin
RUN git clone --depth 1 'https://github.com/imos/bin' /usr/imos/bin

# Clear cache if necessary.
ADD ./dummy /var/tmp/dummy
RUN cd /usr/imos/bin && git pull

EXPOSE 22
EXPOSE 80
CMD ["/bin/bash", "-c", "/usr/sbin/sshd -D -o 'ClientAliveInterval 5' -o 'ClientAliveCountMax 3'"]
