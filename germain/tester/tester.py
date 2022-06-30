import os
import subprocess
import logging

with open("log_minishell", "w") as logfile:
    pass
with open("log_bash", "w") as logfile:
    pass

with open("minishell.test", "r") as testfile:
    for command_line in testfile.readlines():
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
