#! /bin/bash

echo "Rodando Cruzamento 1"
./bin/prog 'one' '192.168.1.129' &

sleep 2

echo "Rodando Cruzamento 2"
./bin/prog 'two' '192.168.1.129' &