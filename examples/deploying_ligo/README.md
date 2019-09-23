# Prerequisites
Docker is running, check with: 

```zsh
curl --unix-socket /var/run/docker.sock http://localhost/v1.37/version
```

Granary CLI installed
```zsh
npm install --global --unsafe-perm @stove-labs/granary@pre-alpha
```

Ligo CLI installed
```zsh
curl https://gitlab.com/ligolang/ligo/raw/dev/scripts/installer.sh | bash -s "next"
```

# Get started with

```zsh
# Install dependencies
npm i
# Initialise granary
npm run init
# Start the node
npm run start
# Activate protocol 004
npm run activate-proto-004
# Compiling Ligo to Michelson
npm run compile
# Deploying the Michelson Contract to Sandbox 
npm run originate
# Buying your first Taco
npm run invoke
```

For troubleshooting, visit
[docs-common-issues](https://stove-labs.github.io/granary/docs/getting-started-install#troubleshooting-common-issues).
