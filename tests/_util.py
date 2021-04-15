from os import popen

def getprocoutput(cmd):
    p = popen(cmd, 'r')
    res = p.read()
    p.close()
    return res
