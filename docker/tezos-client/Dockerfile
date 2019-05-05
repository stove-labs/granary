FROM tezos/tezos:master
USER root
COPY proxy.sh /usr/local/bin/tezos-client-proxy
# ENTRYPOINT [ "/usr/local/bin/tezos-client" ];
RUN chmod +x /usr/local/bin/tezos-client-proxy

USER tezos

# Instead of accessing the tezos-client directly
# We use a proxy here because i couldn't figure out
# how to pass options like --addr to the tezos-client
# without getting a 'Unexpected command line option' error.
ENTRYPOINT [ "/usr/local/bin/tezos-client-proxy" ]


