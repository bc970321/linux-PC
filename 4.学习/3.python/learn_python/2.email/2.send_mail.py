#!/usr/bin/env python
# coding=utf-8

import smtplib
import json
from email.mime.text import MIMEText
from email.mime.multipart import MIMEMultipart
from email.header import Header

def get_userinfo():
    with open("user.json", "r") as info:
        return json.loads(info.read())
   
recvier = "suyelu@126.com"
server = smtplib.SMTP("smtp.126.com")
userinfo = get_userinfo()

server.login(userinfo["username"], userinfo["password"])


message = '<html><h1  style="color:#00F">This is test!</h1></html>'

content = MIMEText(_text = message, _subtype = "html")
content["subject"] = "Html"
content["from"] = userinfo["username"]
content["to"] = userinfo["username"]

send_file = open(r"/home/bicheng/Pictures/123.jpg", "rb").read()
att = MIMEText(send_file, "base64", 'utf-8')
att['Content-Type'] = 'application/octet-stream'
att['Content-Disposition'] = 'attachment;filename="logo.png"'

msgRoot = MIMEMultipart()
msgRoot.attach(MIMEText(message, 'html', 'utf-8'))
msgRoot['Subject'] = "fuian"
msgRoot['From'] = userinfo["username"]
msgRoot['To'] = userinfo["username"]
msgRoot.attach(att)

#server.sendmail(userinfo["username"], userinfo["username"], msgRoot.as_string())

server.sendmail(userinfo["username"], userinfo["username"], content.as_string())
server.close()
