#!/usr/bin/env python
# coding=utf-8

import requests
import re 

url = "https://www.chinanews.com/rss/index.html"

response =  requests.get(url)


#print (requests.utils.get_encodings_from_content(response.text)
response.encoding = 'gb2312'

html = response.text

d1 = re.findall(r'<ul id="xm" style="list-style-type:none;">.*?</ul>', html, re.S)[0]


chapter_info_list = re.findall(r'<li>(.*?)</li>', d1)

#print (d1)

print (chapter_info_list[0])
