# yolov13-windows-onnx
This repository show how to train and predict in Windows system, and onnx runtime

# Step1 anaconda-config
1) make sure VS2019 installed sucesss
2) make sure anaconda installed sucess
3) conda create -n yolov13 python=3.11
4) conda activate yolov13

# Step2 yolov12-windows-config
1) install CPU or GPU pytorch==2.2.2 torchvision==0.17.2<br>
  GPU: conda install pytorch==2.2.2 torchvision==0.17.2 torchaudio==2.2.2 pytorch-cuda=12.1 -c pytorch -c nvidia<br>
  CPU: conda install pytorch==2.2.2 torchvision==0.17.2 torchaudio==2.2.2 cpuonly -c pytorch<br>
2) pip install ninja packaging wheel gitpython<br>
3) git config --system core.longpaths true
4) git clone --recurse-submodules -b v2.7.3 https://github.com/Dao-AILab/flash-attention.git
5) cd flash-attention
6) python setup.py develop<br>
   ***This process cost almost 2hours***<br>
   ***Ampere GPUs and newer is needed for Flash-Attention setup***<br>
   ***If "out of memory" displayed in Flash-Attention setup, you can config more virtual memory in windows system*** <br>
![image](https://github.com/user-attachments/assets/9cf82fe5-397b-4f13-b8ad-4fea41607f0d)

7) modify the reqirements.txt due to the "flash-attention" and pytorch have been installted<br>
![image](https://github.com/user-attachments/assets/426a2bbc-ac3d-4074-a746-21b30c3a8b4c)

8）pip install -r requirements.txt 
9) pip install -e . 

# Step3 yolov13-windows-verify
1) yolo predict model=yolov12l.pt source=bus.jpg show=True
2) the result will be shown in "runs\detect\predict"
![image](https://github.com/user-attachments/assets/53f356af-dbbe-41f4-bc3a-225346d7fb47)


# Step4 yolov13-pt to onnx
1) add python file:exprot.py:
```python
from ultralytics import YOLO

model = YOLO('yolov13l.pt')
model.export(format="onnx",half=False)  # or format="onnx" half=True
```
***half=ture means fp16, otherwise is FP32*** <br>
2) excute the exprot.py
![image](https://github.com/user-attachments/assets/4cf61bb2-827e-4a0e-81fc-d01aec470544)


# Step5  VS2019 onnx calculate
1) followed the project reference, and the choose GPU or not, then to run it
![image](https://github.com/user-attachments/assets/a57d6255-5932-43e6-a493-e4352ed387bb)

***I sucess achieve in VS2019, cuda 12.1 and onnxrunningtime-1.18 in windows10 and windows server2012. 1.C++ inference in step 11, If you use cudnn9.x please use onnxruunming-time 18.1.1, and if you use cudnn8.x use onnx 18.1.0***
![image](https://github.com/user-attachments/assets/b873d7e2-2e08-4d99-a45b-3074367443e1)

# Finally
If you donnot have the "Ampere GPUs and newer", the Flash-Attention couldnot be installed in windows environment, you cannot train the yolov12 in windows.
BUT if you just want to inference the yolov13 "Ampere GPUs and newer" is no need at all.
In CPU only and GTX-1060-6G
![image](https://github.com/user-attachments/assets/a02a17f1-1823-40ab-9279-9ce4b115baae)
![image](https://github.com/user-attachments/assets/bbbb1e91-b9d6-41a0-ba02-04c992e6467e)

*If we use fp16 onnx in step-4, the inference could be spped up much as illustrated belows(fp16 in GTX-1060-6G),we feel the same as FP32, no improvments*
![image](https://github.com/user-attachments/assets/c1ad4b8e-fdbf-4f74-8f6d-181bc8ef5b85)
