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
    x = np.arange(len(data)) ## значения по оси X
    
    fig1, ax1 = plt.subplots()
    
    ax1.plot(x, data)
    #ax1.set_yscale('linear') ## масштаб по оси Y

    # Подписи
    ax1.set_title('Example')
    ax1.set_xlabel('x samples')
    ax1.set_ylabel('data values')
    
    ax1.grid(True) #включить сетку

## Отображаем все рисунки (вызывается один раз)
    plt.show()
else:
    print(__name__, 'is imported')
    
    
