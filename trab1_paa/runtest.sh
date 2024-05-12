#!/bin/sh
rm output.txt
END=100
for ((i = 10; i<END; i++)); do
    ./genpoints $i
    ./closest input.txt
    sleep 1
done
END=1000
for ((i = 100; i<END; i+=10)); do
    ./genpoints $i
    ./closest input.txt
    sleep 1
done
END=10000
for ((i = 1000; i<END; i+=100)); do
    ./genpoints $i
    ./closest input.txt
    sleep 1
done
END=100000
for ((i = 10000; i<END; i+=1000)); do
    ./genpoints $i
    ./closest input.txt
done
END=1000000
for ((i = 100000; i<END; i+=10000)); do
    ./genpoints $i
    ./closest input.txt
done