cmake_minimum_required(VERSION 3.20.0)

# Locate the main Zephyr workspace components automatically
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(frdm_mcxn236_blinky)

# Map compilation entry to main source execution script
target_sources(app PRIVATE src/main.c)
