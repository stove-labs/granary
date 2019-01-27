FROM tezos-environment-manager/sandbox-node:latest

RUN git clone https://github.com/OCamlPro/liquidity 


RUN apt-get install -y libcurl4-gnutls-dev && \
    apt-get install -y libsodium-dev 


RUN cd liquidity && \
    make clone-tezos

RUN wget https://download.libsodium.org/libsodium/releases/old/unsupported/libsodium-1.0.9.tar.gz && \
    tar -xvzf libsodium-1.0.9.tar.gz && \
    cd libsodium-1.0.9 && \
    ./configure && \
    make && \
    make check && \
    make install 

RUN cd liquidity && \
    export OPAMYES=true && \
    make build-deps

RUN cd liquidity && \
    export OPAMYES=true && \
    eval $(opam env) && \
    make && \
    make install

# RUN echo 'eval $(opam env)' >> ~/.bashrc

RUN mkdir /root/.tezos-client
RUN cp /tezos/tezos-client /bin/tezos-client
RUN tezos-client config init

RUN apt-get install -y jq

RUN echo 'chmod +x ./tezos-environment-manager/scripts/$NETWORK_TYPE/setup.sh && source ./tezos-environment-manager/scripts/$NETWORK_TYPE/setup.sh' >> ~/.bashrc

RUN curl -sL https://deb.nodesource.com/setup_10.x | bash - && \
    apt-get install -y nodejs

RUN npm install -g yarn

RUN yarn global add reason-cli@latest-linux