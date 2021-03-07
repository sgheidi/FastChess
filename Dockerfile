FROM gcc:latest
COPY . /usr/local/bin/fastchess
WORKDIR /usr/local/bin/fastchess
RUN apt update && apt upgrade -y; apt install -y libsfml-dev; \
apt-get install -y --no-install-recommends \
        # required for curl
        ca-certificates \
        # required for downloading
        curl \
        # required for X forwarding
        xauth; \
        chmod +x pch.sh; \
        chmod +x run.sh; 

# CMD [ "echo DISPLAY; ./run.sh" ]
