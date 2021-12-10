import subprocess
import os
sourcePath=os.path.abspath("./external")
buildPath=os.path.abspath("./build_windows/external")
if not os.path.exists(buildPath):
	os.makedirs(buildPath, exist_ok=True)


#build debug
subprocess.run(["cmake", "-S" + sourcePath, "-B" + buildPath, "-DCMAKE_BUILD_TYPE=Debug"])
subprocess.run(["cmake", "--build", buildPath, "--target", "install", "--config", "Debug"])
#build release
subprocess.run(["cmake", "-S" + sourcePath, "-B" + buildPath, "-DCMAKE_BUILD_TYPE=Release"])
subprocess.run(["cmake", "--build", buildPath, "--target", "install", "--config", "Release"])

os.system("pause")
