import os, time, sys
from os import system, remove, path
try:
    # Python 2.5 : Batteries included
    import xml.etree.ElementTree as ET
except ImportError:
    try:
        # Python <2.4 
        import elementtree.ElementTree as ET
    except ImportError:
        raise ImportError, "Element Tree is not installed."

def main():
###########################################
# Option to initialize from tutorial case #
###########################################
#######################################
# Option to create a case             #
#######################################
#######################################
    if(len(sys.argv)<2):
        print 'Please use option -h to see all available options'
        return

    elif(sys.argv[1]=='-h'):
        print 'help option is invoked.'
        print 'Rotorbit PortAble Visualization Library for sOlVers (PAVLOV) Version 1.0.'
        print 'To compile the library, use -m'
#######################################
# Option to create exe with make      #
#######################################
    elif(sys.argv[1]=='-m'):
        print 'PAVLOV is being compiled.'
        os.getcwd()
        os.chdir("src")
        system("rm -rf build")
        system("mkdir build")
        os.chdir("build")
        system('cmake ..')
        system('make')
        print 'PAVLOV is successfully compiled.'
#######################################
# Option to use scripts for output    #
#######################################
    elif(sys.argv[1]=='-o'):
        print 'The output scripts are employed.'
if __name__ == "__main__":
    main()

