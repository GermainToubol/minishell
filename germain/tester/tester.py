import os
import subprocess
import logging
import uuid

def colors_256(color_):
    num1 = str(color_)
    if (color_ == -1):
        return ("\033[0;0m")
    return(f"\033[38;5;{num1}m")

rows, columns = os.popen('stty size', 'r').read().split()
rows = int(rows)
columns = int(columns)

summary = {}

print(" Make ".center(columns - 1, "-"))
print(colors_256(30), end="");
with subprocess.Popen(["make", "-C", ".."], stdout=subprocess.PIPE) as proc:
    print(proc.stdout.read().decode())
print(colors_256(-1), end='')

print(" Run Tests ".center(columns - 1, "-"))

with open("minishell.test", "r") as testfile:
    for command_line in testfile.readlines():
        if (command_line[:2] == "##"):
            cmd = command_line.strip()
            summary[cmd] = [0, 0]
            print()
            print(f" {command_line.strip()} ".center(columns // 2, "*"))
            continue
        if (command_line[:1] == "#"):
            cmd = command_line.strip()
            summary[cmd] = [0, 0]
            print()
            print(f" {command_line.strip()} ".center(columns - 1, "*"))
            continue
        tmp_id = uuid.uuid4().hex
        with subprocess.Popen(["../minishell", '-c', command_line.strip()], stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
            with open(f"log_minishell_{tmp_id}", "w") as logfile:
                try:
                    outs, errs = proc.communicate(timeout=15)
                except TimeoutExpired:
                    proc.kill()
                    outs, errs = proc.communicate()
                logfile.write(f"## {command_line.strip()}\n")
                logfile.write(outs.decode())
                logfile.write(errs.decode())
                logfile.write("RETUN: {}\n".format(proc.returncode))

        with subprocess.Popen(["bash", '-c', command_line.strip()], stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
            with open(f"log_bash_{tmp_id}", "w") as logfile:
                try:
                    outs, errs = proc.communicate(timeout=15)
                except TimeoutExpired:
                    proc.kill()
                    outs, errs = proc.communicate()
                logfile.write(f"## {command_line.strip()}\n")
                logfile.write(outs.decode())
                logfile.write(errs.decode())
                logfile.write("RETUN: {}\n".format(proc.returncode))

        with subprocess.Popen(["bash", "-c", f'cat log_bash_{tmp_id} | sed "s/^bash: line 0/bash/g" | ""sed "s/^bash/minishell/g" | diff - log_minishell_{tmp_id}'], stdout=subprocess.PIPE) as proc:
            summary[cmd][1] += 1
            diff = proc.stdout.read().decode()
            width = columns - len(command_line.strip()) - 4 - 1
            spacer = ' ' * width
            if (diff == ""):
                summary[cmd][0] += 1
                print (f"{colors_256(46)}{command_line.strip()}{spacer}[OK]{colors_256(-1)}")
            else:
                print (f"{colors_256(196)}{command_line.strip()}{spacer}[KO]{colors_256(-1)}")
                print(colors_256(220), diff, colors_256(-1) , sep='', end='')

print(" Summary ".center(columns - 1, "-"))
for key in summary:
    if (summary[key][0] != summary[key][1]):
        print(colors_256(220), end='');
    out =  "[{}/{}]".format(*summary[key])
    width=columns - 2 - 1 - len(key) - len(out)
    spacer = '.' * width
    print(f"{key}  {spacer}{out}{colors_256(-1)}")
print(" Clean ".center(columns - 1, "-"))
with subprocess.Popen(["bash", "-c", "rm -f log_bash_* log_minishell_*"]):
    pass
print(" Done ".center(columns - 1, "-"))
