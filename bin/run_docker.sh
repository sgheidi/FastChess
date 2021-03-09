#!/bin/bash

docker build .. -t fastchess:1;
sudo docker run --rm -it fastchess:1
