FROM gcc:latest
COPY . /usr/src/fastchess
WORKDIR /usr/src/fastchess
RUN apt update && apt upgrade -y
RUN apt install -y libsfml-dev
RUN export DISPLAY=host.docker.internal:0
CMD [ "./run.sh" ]
