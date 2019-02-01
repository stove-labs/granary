FROM tezos-environment-manager/sandbox-node:latest

RUN git clone https://gitlab.com/tzscan/tzscan

RUN cd tzscan && \
    git submodule init && \
    git submodule update

RUN ln -snf /usr/share/zoneinfo/Zulu /etc/localtime && echo $TZ > /etc/timezone

RUN cd tzscan && \
    apt-get -y install \
    postgresql libsodium-dev libgeoip1 \
    geoip-database libcurl4-gnutls-dev \
    curl zlib1g-dev libgeoip-dev

ENV OPAMYES=true

RUN opam init --compiler=4.06.1 --disable-sandboxing

RUN cd tzscan && \
    opam install\
     camlp4\
     re.1.7.3\
     ocplib-json-typed\
     ocurl\
     js_of_ocaml\
     js_of_ocaml-ppx\
     js_of_ocaml-camlp4\
     js_of_ocaml-lwt\
     omd\
     cohttp-lwt\
     cohttp-lwt-unix\
     base64\
     ezjsonm\
     ocplib-endian\
     geoip\
     ocp-build\
     nocrypto\
     sodium\
     lru\
     alcotest\
     calendar \
     lwt_log \
     csv-lwt && \
     opam pin --dev ocplib-json-typed && \
     opam install ocplib-json-typed

RUN git clone https://github.com/darioteixeira/pgocaml && \
    cd pgocaml && \
    eval $(opam env) && \
    ./configure --enable-p4 --prefix $OPAM_SWITCH_PREFIX --docdir $OPAM_SWITCH_PREFIX/doc && \
    make && \
    make doc && \
    make install

USER postgres

RUN service postgresql start && \
    psql --command "CREATE USER root; ALTER ROLE root CREATEDB";

USER root

RUN opam install js_of_ocaml-tyxml.3.2.0

RUN cd tzscan && \
    eval $(opam env) && \
    ./configure

RUN cd tzscan && \
    touch Makefile.database && \
    echo "API_HOST:=localhost\nAPI_PORT:=8080\nNEED_PARSEXP=true" >> Makefile.database

RUN opam install js_of_ocaml.3.2.0

RUN cd tzscan && \
    service postgresql start && \
    eval $(opam env) && \
    make

RUN apt-get -y install php

RUN cd tzscan && \
    rm config.json && \
    echo "test" && \
    echo '[{"name": "betanet-main","crawler" : [{"url" : "http://sandboxnet_node", "port" : 18731}], "api" : [{"url" : "http://sandboxnet_node", "port" : 18731}]}]' >> config.json

ADD ./scripts/init-tzscan.sh /bin/init-tzscan
RUN chmod +x /bin/init-tzscan