# -*- coding: utf-8 -*-
"""
Created on Tue Mar 25 08:20:03 2025

@author: 33783
"""

import os

WT1,WT2,WT3=0,0,0

for i in range (2000):
    
    stream = os.popen("seance3.exe")
    output = stream.read()
    
    # Séparer les lignes et récupérer la dernière
    last_line = output.strip().split("\n")[-3:]  # a changer en fonction du code.
    
    if WT1<float(last_line[0]):
        WT1=float(last_line[0])
    if WT2<float(last_line[1]):
        WT2=float(last_line[1])
    if WT3<float(last_line[2]):
        WT3=float(last_line[2])


print("WT1 :", WT1," ms")
print("WT2 :", WT2," ms")
print("WT3 :", WT3," ms")
    
    
    
