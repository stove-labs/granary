FROM maht0rz/tezos-environment-manager-sandbox-node:latest

RUN git clone https://gitlab.com/gabriel.alfour/new-tezos-opam-repository

RUN opam repo add galfour-tezos ./new-tezos-opam-repository

RUN opam update galfour-tezos   

RUN opam install getopt --yes

RUN git clone https://gitlab.com/gabriel.alfour/tezos gabriel-tezos

RUN opam update

RUN cd gabriel-tezos/src/ligo && \
    opam install . --yes

RUN eval $(opam env)

ENTRYPOINT [ "/root/.opam/4.06.1/bin/ligo" ]