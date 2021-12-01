import subprocess
import os
buildPath="build/external"
if not os.path.exists(buildPath):
	os.makedirs(buildPath, exist_ok=True)

#build debug
subprocess.run(["cmake", "../../external", "-DCMAKE_BUILD_TYPE=Debug", "-DCMAKE_GENERATOR_PLATFORM=x64"], cwd=buildPath)
subprocess.run(["cmake", "--build", ".", "--target", "install", "--config", "Debug"], cwd=buildPath)
#build release
subprocess.run(["cmake", "../../external", "-DCMAKE_BUILD_TYPE=Release", "-DCMAKE_GENERATOR_PLATFORM=x64"], cwd=buildPath)
subprocess.run(["cmake", "--build", ".", "--target", "install", "--config", "Release"], cwd=buildPath)
os.system("pause")