#!/bin/bash
sudo make clean
sudo make all
sudo make load
sync
sudo ./a.out
