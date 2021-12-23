#!/usr/bin/env python3
# -*- coding: utf-8 -*-    

import numpy as np

import matplotlib as mpl
import matplotlib.pyplot as plt


##########################################################
# https://matplotlib.org/gallery.html
# хорошая подборка разных примеров отображения данных
##########################################################

if (__name__ ==  '__main__'):
###
    data = np.loadtxt('output.dat')
    n_fft = 2 * (len(data))
    arr_n = np.arange(n_fft / 2)
    fd = 6000
    
    x = arr_n * (fd / n_fft) ## значения по оси X
    fig1, ax1 = plt.subplots()
    
    ax1.plot(x, data)

    # Подписи
    ax1.set_title('N = %i' %n_fft)
    ax1.set_xlabel('Частота сигнала')
    ax1.set_ylabel('Амплитуда')
    
    ax1.grid(True) #включить сетку

    ## Отображаем все рисунки (вызывается один раз)
    plt.show()
else:
    print(__name__, 'is imported')
    
    
