#!/usr/bin/env python3

import subprocess
import time
from enum import Enum
import matplotlib.pyplot as plt
import numpy as np


class Lang(Enum):
    RUST = 0
    C = 1
    HASKELL = 2


class DataPoint:
    def __init__(self, lang, day, time):
        self.lang = lang
        self.day = day
        self.time = time

    def __str__(self) -> str:
        return (f"{self.day} completed with {self.lang} in "
                f"{self.time:.3f} seconds")

    def __repr__(self):
        return self.__str__()


def process_day(path: str) -> DataPoint:
    files = subprocess.run(f"ls {path}",
                           shell=True, capture_output=True).stdout.decode()
    if files.find("Cargo.toml") != -1:
        time = process_day_rust(path)
        return DataPoint(Lang.RUST, path, time)


def process_day_haskell(path: str):
    pass


def process_day_c(path: str):
    pass


def process_day_rust(path: str):
    print("rust detected")
    subprocess.run(f"cd {path};cargo build", shell=True, capture_output=True)
    before = time.time()
    subprocess.run(f"cd {path};cargo run", shell=True, capture_output=True)
    after = time.time()
    difference = after - before
    print(f"time to run {path} is {difference}")
    return difference


years = subprocess.run("ls -l | grep ^d | awk '{print $9}'",
                       shell=True, capture_output=True).stdout.splitlines()
days = []

for y in years:
    y = y.decode()
    this_year_days = subprocess.run(f"ls -l {y} | grep ^d |"
                                    " awk '{print $9}'", shell=True,
                                    capture_output=True).stdout.splitlines()
    for day in this_year_days:
        daypath = f"{y}/{day.decode()}"
        days.append(daypath)


data = []

for day in days:
    if day == "2016/d05":
        continue
    data_point = process_day(day)
    if data_point is not None:
        data.append(data_point)

print(data)

days_strs = []
days_times = []

for i in data:
    days_strs.append(i.day)
    days_times.append(i.time)

x = np.array(days_strs)
y = np.array(days_times)

plt.plot(x,y)
plt.show()
