#!/usr/bin/env python
# coding=utf-8
import oss2
import uuid
import sys
import os
import time
import pyperclip
import Image

def is_img(ext):
    ext = ext.lower()
    if ext in ['.hpg', '.png', '.jpeg', '.bmp', '.gif']:
        return True
    else:
        return False


if len(sys.argv) == 1:
    #判断剪切板是否有图片
    im = ImageGrab.grabclipboard()
    if isinstance(im, Image.Image):
        im.save('/tmp/tmphaizei.jpg', 'jpeg')
        src_file = 'tmphaizei.jpg'
    else:
        print ("exit")
        sys.exit()
elif len(sys.argv) == 2:
    if not os.path.exists(sys.argv[1]):
        sys.exit()
    else:
        if not is_img(os.path.splitext(sys.argv[1])[1]):
            sys.exit()
        else:
            src_file = sys.argv[1]
else:
    print ("Error in args")
    sys.exit()

print ("src_file = %s" % src_file)

def gen_remote_name(localname):
    name = uuid.uuid4().__str__().replace("-","").upper()
    date = time.strftime('%Y-%m-%d', time.localtime(time.time()))
    localname = str(localname).rsplit(".")
    return "%s.%s.%s" % (date, name, localname)

print (gen_remote_name)

BUCKET_NAME = "bicheng123"
ENDPOINT = "http://oss-cn-beijing.aliyuncs.com"
ACCESS_KEY_ID = "LTAIKKKC3SJOVjag"
ACCESS_KEY_SECRET = "wPbyWXf7B8xH2cJlB378LUjnRmyi8Z"

auth = oss2.Auth(ACCESS_KEY_ID, ACCESS_KEY_SECRET)
bucket = oss2.Bucket(auth, ENDPOINT, BUCKET_NAME)
remote_file_name = gen_remote_name(src_file)
bucket.put_object_from_file(remote_file_name, src_file)

result_str = "![](http://%s.%s/%s)" % (BUCKET_NAME, ENDPOINT, remote_file_name)
pyperclip.copy(result_str)

print (result_str)

