import subprocess
import os
buildPath="build_linux/external"
if not os.path.exists(buildPath):
	os.makedirs(buildPath, exist_ok=True)
subprocess.run(["cmake", "../../external", "-DCMAKE_BUILD_TYPE=Debug"], cwd=buildPath)
subprocess.run(["cmake", "--build", ".", "--target", "install", "--config", "Debug"], cwd=buildPath)
subprocess.run(["cmake", "../../external", "-DCMAKE_BUILD_TYPE=Release"], cwd=buildPath)
subprocess.run(["cmake", "--build", ".", "--target", "install", "--config", "Release"], cwd=buildPath)
os.system("pause")
