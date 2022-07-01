import os
import subprocess
import logging

print("------------ Run Tests ---------------")
with open("log_minishell", "w") as logfile:
    pass
with open("log_bash", "w") as logfile:
    pass

with open("minishell.test", "r") as testfile:
    for command_line in testfile.readlines():
        if (command_line[0] == "#"):
            print(command_line.strip())
            continue

        with subprocess.Popen(["../minishell", '-c', command_line.strip()], stdout=subprocess.PIPE, stderr=subprocess.PIPE) as proc:
            with open("log_minishell", "a") as logfile:
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
            with open("log_bash", "a") as logfile:
                try:
                    outs, errs = proc.communicate(timeout=15)
                except TimeoutExpired:
                    proc.kill()
                    outs, errs = proc.communicate()
                logfile.write(f"## {command_line.strip()}\n")
                logfile.write(outs.decode())
                logfile.write(errs.decode())
                logfile.write("RETUN: {}\n".format(proc.returncode))

print("------------ Analyse Diffs -----------")
with subprocess.Popen(["bash", "-c", 'cat log_bash | sed "s/^bash/minishell/g" | diff - log_minishell']):
    pass

print("------------ Done --------------------")
