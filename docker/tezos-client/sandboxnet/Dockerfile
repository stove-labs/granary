FROM tezos/tezos:master

USER root
RUN apk add --no-cache bash

COPY proxy.sh /usr/local/bin/tezos-client-proxy
RUN chmod +x /usr/local/bin/tezos-client-proxy

USER tezos

ENV IDENTITY_POW="0"
ENV PROTOCOL="alpha"
ENV NODE_HOST "127.0.0.1"

# Instead of accessing the tezos-client directly
# We use a proxy here because i couldn't figure out
# how to pass options like --addr to the tezos-client
# without getting a 'Unexpected command line option' error.
ENTRYPOINT [ "/usr/local/bin/tezos-client-proxy" ]


