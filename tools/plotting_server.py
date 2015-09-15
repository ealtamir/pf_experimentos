#!/usr/local/bin/python3

import os
import time
#import numpy as np
import matplotlib.pyplot as plt

from struct import calcsize, unpack

FIFO_FILENAME = "/tmp/passive_walker_exp.fifo"
DATA_FORMAT = '@ddd'
DATA_LENGTH = calcsize(DATA_FORMAT)

fifo = None

def start_plot_server():
    init_plot()
    count = 0
    print("Starting plotting process...")
    print("Data length: " + str(DATA_LENGTH))
    while True:
        data = get_fitness_components_data()
        if data:
            update_plot(data, count)
            count += 1
        else:
            break
    save_plot()

def save_plot():
    plt.savefig('results.png')
    plt.close()

def init_plot():
    plt.axis([0, 20, 0, 0.5])
    plt.ion()
    plt.show()

def update_plot(data, count):
    fitness = data[0]
    print("Fitness encontrado: " + str(fitness))
    plt.scatter(count, fitness)
    plt.draw()
    time.sleep(0.001)

def get_fitness_components_data():
    if not fifo: open_fifo()
    data_tuple = get_data()
    if data_tuple:
        return data_tuple
    else:
        print("Data tuple came empty")

def get_data():
    print("reading data")
    data = os.read(fifo, DATA_LENGTH)

    print("data read")
    if len(data) == DATA_LENGTH:
        return unpack(DATA_FORMAT, data)

    if len(data) < DATA_LENGTH:
        count = 0
        remainder = DATA_LENGTH - len(data)
        while remainder > 0 and count < 100:
            new_data = os.read(fifo, remainder)
            remainder -= len(new_data)
            data += new_data
            count += 1
        if count < 100: return data
    return None

def open_fifo():
    global fifo
    fifo = os.open(FIFO_FILENAME, os.O_RDONLY)
    return fifo

if __name__ == '__main__':
    start_plot_server()
