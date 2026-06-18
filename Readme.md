# Feedforward Neural Network Library to solve Classification Problems

This projects aim is to develop a small neural network library that focuses on classification problems. The entire project will be written in the C programming language.

## Features

1. Math Primitives (Vectors and Matrices)
2. Activation Functions
3. Layers and forward pass (Currently Working On)
4. Loss Function (Coming up ...)
5. Backpropagation (Coming up ...)
6. Training Loop (Coming up ...)

## Building

### Requirements

- Git 2.49.0
- gcc 15.2.0
- GNU Make 4.4.1

### Build

First, if you already didn't, you must clone the github repo and change directories into the project directory. Below are the commands to do so:

```bash
git clone https://github.com/PrayagPatel1/Feedforward-Neural-Network-Classifier-Library.git

cd Feedforward-Neural-Network-Classifier-Library
```

Then to run the project you may just use the "make" command:

```bash
make
```

If you don't have make install then you can create a build script:

```bash
#!/bin/bash
gcc -Wall -Wextra -o neural_network src/main.c src/vector.c src/matrix.c src/activation.c
```

Outside of the script, make sure to chmod the permissions on the script to be executable and execute the program:

```bash
chmod +x build.sh
./build.sh
```

## Use of Artifical Intelligence

Currently AI is only being used to timeline this entire project and be able to help what core components needs to be implemented inorder to reach a point where we can implement a binary classifier using neural networks.

## Resources Used

1. Neural Networks and Deep Learning by Michael Nielsen
