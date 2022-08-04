#! /bin/bash

echo "Rodando Cruzamento 3"
./bin/prog 'three' '192.168.1.129' &

sleep 2

echo "Rodando Cruzamento 4"
./bin/prog 'four' '192.168.1.129' &