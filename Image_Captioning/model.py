import torch
import torch.nn as nn
import torchvision.models as models
import torch.nn.functional as F


class EncoderCNN(nn.Module):
    def __init__(self, embed_size):
        super(EncoderCNN, self).__init__()
        resnet = models.resnet50(pretrained=True)
        for param in resnet.parameters():
            param.requires_grad_(False)
        
        modules = list(resnet.children())[:-1]
        self.resnet = nn.Sequential(*modules)
        self.embed = nn.Linear(resnet.fc.in_features, embed_size)
        self.bn1 = nn.BatchNorm1d(embed_size)

    def forward(self, images):
        features = self.resnet(images)
        features = features.view(features.size(0), -1)
        features = self.embed(features)
        features = self.bn1(features)
        return features
    

class DecoderRNN(nn.Module):
    def __init__(self, embed_size, hidden_size, vocab_size, num_layers):
        super(DecoderRNN,self).__init__()
        self.embed_size = embed_size
        self.hidden_size = hidden_size
        self.vocab_size = vocab_size
        self.num_layers = num_layers
        self.embed = nn.Embedding(self.vocab_size, self.embed_size)
        self.lstm = nn.LSTM(self.embed_size,self.hidden_size,self.num_layers,batch_first=True)
        self.fc = nn.Linear(self.hidden_size,self.vocab_size)
        self.init_weights()
        
    def init_weights(self):
        self.embed.weight.data.uniform_(-0.1,0.1)
        self.fc.weight.data.uniform_(-0.1,0.1)
        self.fc.bias.data.fill_(0.01)
        # below code taken from https://discuss.pytorch.org/t/set-forget-gate-bias-of-lstm/1745/4
        for names in self.lstm._all_weights:
            for name in filter(lambda n: "bias" in n,  names):
                bias = getattr(self.lstm, name)
                n = bias.size(0)
                start, end = n//4, n//2
                bias.data[start:end].fill_(1.)
                
    def forward(self, features, captions):
        features_un = features.unsqueeze(1)  # batch_size X 1 X embed_size 
        captions = captions[:,:-1]  # batch_size X (seq_length -1)
        captions_embed = self.embed(captions.long())  # batch_size X (seq_length-1) X embed_size 
        inputs = torch.cat((features_un,captions_embed),1) # batch_size X (seq_length) X embed_size
        hidden, _ = self.lstm(inputs) # batch_size X (seq_length) X embed_size
        out = self.fc(hidden) # batch_size X (seq_length + 1) X vocab_size
        return out
    
    def sample(self,inputs,max_len=20,hidden=None):
        output_ids = []
        for i in range(max_len):
            out,hidden = self.lstm(inputs,hidden) # 1 X 1 X hidden_size, (1 X 1 X hidden_size, 1 X 1 X hidden_size)
            out = out.squeeze(1) # 1 X hidden_size
            out = self.fc(out) # 1 X vocab_size
            _,pred = out.max(1) # 1
            output_ids.append(int(pred.to("cpu").item()))
            inputs = self.embed(pred.long()) # 1 X embed_size
            inputs = inputs.unsqueeze(1)  # 1 X 1 X embed_size
        return output_ids