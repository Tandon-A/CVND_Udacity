import torch
from torchvision import transforms, utils
from torch.utils.data import DataLoader,Dataset
import pandas as pd
import matplotlib.image as mpimg
import cv2
import numpy as np


class Normalize(object):
  def __call__(self,sample):
    image = sample['image']
    key_pts = sample['key_pts']
    image_copy = np.copy(image)
    key_pts_copy = np.copy(key_pts)

    image_copy = cv2.cvtColor(image_copy,cv2.COLOR_RGB2GRAY)
    image_copy = image_copy/255.0
    
    key_pts = (key_pts - 100)/50.0

    return {'image':image_copy,'key_pts':key_pts}

class Rescale(object):
  def __init__(self,output_size):
    assert isinstance(output_size,(int,tuple))
    self.output_size = output_size
  
  def __call__(self,sample):
    image = sample['image']
    key_pts = sample['key_pts']

    h,w = image.shape[:2]
    if isinstance(self.output_size,int):
      if h > w :
        new_h, new_w = self.output_size * h/w, self.output_size
      else:
        new_h,new_w = self.output_size,self.output_size * (w/h)
    else:
      new_h,new_w = self.output_size
    new_w, new_h = int(new_w),int(new_h)    
    image = cv2.resize(image, (new_w,new_h))
    key_pts = key_pts * [new_w/w,new_h/h]

    return {'image':image,'key_pts':key_pts}

class RandomCrop(object):
  def __init__(self,output_size):
    assert isinstance(output_size,(int,tuple))
    if isinstance(output_size,int):
      self.output_size = (output_size,output_size)
    else:
      assert len(output_size) == 2
      self.output_size = output_size
  
  def __call__(self,sample):
    image = sample['image']
    key_pts = sample['key_pts']

    h,w = image.shape[:2]
    new_h,new_w = self.output_size

    top = np.random.randint(0, h - new_h)
    left = np.random.randint(0, w - new_w)

    image = image[top : top + new_h, left : left + new_w]
    key_pts = key_pts - [left,top]
    return {'image':image,'key_pts':key_pts}

class ToTensor(object):
  def __call__(self,sample):
    image = sample['image']
    key_pts = sample['key_pts']

    if len(image.shape)==2:
      image = image.reshape(image.shape[0],image.shape[1],1)
    
    image = image.transpose((2,0,1))
    return {'image':torch.from_numpy(image),'key_pts':key_pts}

class FacialKeypointsData(Dataset):
  def __init__(self,csv_file,root_dir,transform=None):
    self.root_dir = root_dir
    self.csv_file = pd.read_csv(csv_file)
    self.transform = transform
  
  def __len__(self):
    return len(self.csv_file)
  
  def __getitem__(self,idx):
    image_name = self.csv_file.iloc[idx,0]
    image = mpimg.imread(self.root_dir + "/" + image_name)
    
    #getting rid of alpha channel if an image has it 
    if image.shape[2] == 4:
      image = image[:,:,:3]
    key_pts = self.csv_file.iloc[idx,1:].values.astype("float").reshape(-1,2)
    sample = {'image':image,'key_pts':key_pts}
    if self.transform:
      sample = self.transform(sample)
    return sample