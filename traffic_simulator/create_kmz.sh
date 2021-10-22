#!/bin/bash

# Based on Sagar’s sample hw1 solution

cd Release/bin
zip -r myfile.zip myfile.kml files
mv myfile.zip myfile.kmz
mv myfile.kmz ../../data
