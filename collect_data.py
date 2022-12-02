#!/usr/env python3

import subprocess
import time


def process_day(path: str):
    files = subprocess.run(f"ls {path}",
                           shell=True, capture_output=True).stdout.decode()
    if files.find("Cargo.toml") != -1:
        process_day_rust(path)


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


for day in days:
    process_day(day)
