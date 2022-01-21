import subprocess
import os
import platform

sourcePath=os.path.abspath("./external")
buildPath=os.path.abspath("./build_"+ platform.system().lower() + "/external")
if not os.path.exists(buildPath):
	os.makedirs(buildPath, exist_ok=True)


#build debug
# subprocess.run(["cmake", "-S" + sourcePath, "-B" + buildPath, "-DCMAKE_BUILD_TYPE=Debug", "-DBUILD_SHARED_LIBS=OFF"])
subprocess.run(["cmake", "-S" + sourcePath, "-B" + buildPath, "-DCMAKE_BUILD_TYPE=Debug"])
subprocess.run(["cmake", "--build", buildPath, "--target", "install", "--config", "Debug"])
#build release
# subprocess.run(["cmake", "-S" + sourcePath, "-B" + buildPath, "-DCMAKE_BUILD_TYPE=Release", "-DBUILD_SHARED_LIBS=OFF"])
subprocess.run(["cmake", "-S" + sourcePath, "-B" + buildPath, "-DCMAKE_BUILD_TYPE=Release"])
subprocess.run(["cmake", "--build", buildPath, "--target", "install", "--config", "Release"])

# os.system("pause")
# input()
