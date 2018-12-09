import subprocess 
import sys
import os

rootDir = os.getcwd()
is_64bits = sys.maxsize > (2**31)

def build_x86():
    print("Starting " + os.name + " x86 build on \"" + rootDir + "/CmakeLists.txt\"")
    os.chdir(rootDir)
    if not os.path.exists("bin"):
        print("Creating bin")
        os.mkdir("bin")
    os.chdir("bin")
    if not os.path.exists("x86"):
        print("Creating x86")
        os.mkdir("x86")
    os.chdir("x86")
    print("Creating CMake build files")
    p1 = subprocess.Popen(["cmake", "-G", "Visual Studio 15", "../.."])
    p1.wait()
    print("Building binaries")
    p2 = subprocess.Popen(["cmake", "--build", ".", "--config", "Release"])
    p2.wait()

def build_x64():
    print("Starting x64 " + os.name + " build on \"" + rootDir + "/CmakeLists.txt\"")
    os.chdir(rootDir)
    if not os.path.exists("bin"):
        print("Creating bin")
        os.mkdir("bin")
    os.chdir("bin")
    if not os.path.exists("x64"):
        print("Creating x64")
        os.mkdir("x64")
    os.chdir("x64")
    print("Creating CMake build files")
    p1 = subprocess.Popen(["cmake", "-G", "Visual Studio 15 Win64", "../.."])
    p1.wait()
    print("Building binaries")
    p2 = subprocess.Popen(["cmake", "--build", ".", "--config", "Release"])
    p2.wait()

def build_posix():
    print("Starting " + os.name + " build on \"" + rootDir + "/CmakeLists.txt\"")
    os.chdir(rootDir)
    if not os.path.exists("bin"):
        print("Creating bin")
        os.mkdir("bin")
    os.chdir("bin")
    print("Creating CMake build files")
    p1 = subprocess.Popen(["cmake", "-G", "Unix Makefiles", ".."])
    p1.wait()
    print("Building binaries")
    p2 = subprocess.Popen(["cmake", "--build", ".", "--config", "Release"])
    p2.wait()

if os.name == "nt": 
    if len(sys.argv) > 1:
        if str(sys.argv[1]) == "both":
            build_x86()
            build_x64()
        elif str(sys.argv[1]) == "x64":
            build_x64()
        elif str(sys.argv[1]) == "x86":
            build_x86()
    else:
        if is_64bits:
            build_x64()
        else:
            build_x86()
elif os.name == "posix": 
    build_posix()
