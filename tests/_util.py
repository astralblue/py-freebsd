from os import popen

def getprocoutput(cmd):
    return popen(cmd, 'r').read()
