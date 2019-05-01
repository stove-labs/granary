# Run the CLI for dummy testing purposes
./granary.js --help

# 
# Config
# 
./granary.js config --help
./granary.js config set test 1
./granary.js config show test
# Custom config path
./granary.js config set test 2 --config=granary-test.json
./granary.js config show test  --config=granary-test.json
