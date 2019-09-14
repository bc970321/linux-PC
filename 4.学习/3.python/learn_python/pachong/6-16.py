#!/usr/bin/env python
# coding=utf-8
import time
from selenium import webdriver
import importlib
import sys
importlib.reload(sys)

url = "https://inn.ctrip.com/onlineinn/list?checkin=2019-06-15&checkout=2019-06-16&cityid=5&cityname=%E5%93%88%E5%B0%94%E6%BB%A8&channelid=211"

driver = webdriver.Chrome()
global count
count = 0
driver.get(url)
time.sleep(3)
def GetAll(cnt):
    time.sleep(2)
    click_items = driver.find_elements_by_class_name("list-photo")
    global count
    for each in click_items:
        if (count >= 100):
            sys.exit(0)
        count = count + 1
        each.click()
        handle = driver.window_handles
        driver.switch_to_window(handle[1])
        time.sleep(1)
        name = driver.find_elements_by_class_name("tit")
        if (len(name) == 0):
            driver.close()
            driver.switch_to_window(handle[0])
            continue
        print (str(count) + "." + name[0].text)
        driver.close()
        driver.switch_to_window(handle[0])


while (count <= 100):
    GetAll(count)
    next = driver.find_element_by_class_name("item-next")
    next.click()

driver.close()
