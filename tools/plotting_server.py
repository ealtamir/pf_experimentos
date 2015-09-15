#!/usr/local/bin/python3

import os

from struct import calcsize, unpack

FIFO_FILENAME = "/tmp/passive_walker_exp.fifo"
DATA_FORMAT = '@ddd'

fifo = None

def start_plot_server():
    init_plot()
    while True:
        data = get_fitness_components_data()
        update_plot(data)

def init_plot():
    pass

def update_plot(data):
    print(data)

def get_fitness_components_data():
    if not fifo: open_fifo()
    data_tuple = get_data()
    if data_tuple:
        return data_tuple
    else:
        print("Data tuple came empty")

def get_data():
    data = os.read(fifo, calcsize(DATA_FORMAT))
    if data:
        return unpack(DATA_FORMAT, data)
    return None

def open_fifo():
    global fifo
    fifo = os.open(FIFO_FILENAME, os.O_RDONLY)
    return fifo

if __name__ == '__main__':
    start_plot_server()
