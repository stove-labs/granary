service postgresql start
cd /tzscan/www
php -S 0.0.0.0:8000 &
cd /tzscan
./tzscan-crawler config.json &
sleep 5
./tzscan-api-server --node-config config.json --api-config www/api-config.json &
wait