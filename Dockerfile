FROM ubuntu:18.04

# install pose-terrier dependencies
RUN apt-get update
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get install -y cmake libprotobuf-dev libceres-dev libeigen3-dev libopencv-dev

# build pose-terrier
ADD . / pose_terrier/
WORKDIR pose_terrier
RUN echo "include_directories(/usr/include/eigen3)" >> CMakeLists.txt
RUN mkdir build && cd build && cmake -DCMAKE_BUILD_TYPE=Release ../ && make -j4

CMD build/pose_estimator_main
