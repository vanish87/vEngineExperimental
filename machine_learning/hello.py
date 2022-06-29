print("Hello World")


import numpy as np
import torch
 
n = np.array([1, 2, 3])
a = torch.from_numpy(n.astype(np.float32)).clone()
print(a)

print(torch.__version__)
print(torch.cuda.get_device_name())