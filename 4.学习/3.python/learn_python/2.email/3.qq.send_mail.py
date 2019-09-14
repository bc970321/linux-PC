#!/usr/bin/env python
# coding=utf-8

import smtplib
import json
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import Header

def get_userinfo():
    with open("qq.json", "r") as info:
        return json.loads(info.read())
   
server = smtplib.SMTP("smtp.qq.com")
userinfo = get_userinfo()

server.login(userinfo["username"], userinfo["password"])


message = '<html><h1  style="color:#00F">好好学习 天天向上</h1></html>'

#content = MIMEText(_text = message, _subtype = "html")
#content["subject"] = "Html"
#content["from"] = userinfo["username"]
#content["to"] = userinfo["username"]

send_file = open(r"/home/bicheng/Pictures/002.jpg", "rb").read()
att = MIMEText(send_file, "base64", 'utf-8')
att['Content-Type'] = 'application/octet-stream'
att['Content-Disposition'] = 'attachment;filename="logo.png"'

msgRoot = MIMEMultipart()
msgRoot.attach(MIMEText(message, 'html', 'utf-8'))
msgRoot['Subject'] = "fujian"
msgRoot['From'] = userinfo["username"]
msgRoot['To'] = userinfo["username"]
msgRoot.attach(att)

server.sendmail(userinfo["username"], userinfo["username"], msgRoot.as_string())

#server.sendmail(userinfo["username"], userinfo["username"], content.as_string())

print ("OK!")
server.close()
