#!/usr/bin/env python
# coding=utf-8
import time
from selenium import webdriver
import json
#from selenium.webdriver.common.by import By
#from selenium.webdriver.support import expected_conditions as EC
#from selenium.webdriver.support.ui import WebDriverWait
import sys

reload(sys)
sys.setdefaultencoding("utf-8")

url = "https://inn.ctrip.com/onlineinn/list?checkin=2019-06-15&checkout=2019-06-16&cityid=5&cityname=%E5%93%88%E5%B0%94%E6%BB%A8&channelid=211"

driver = webdriver.Chrome()
global count
count = 0
driver.get(url)

items = []

def get_item():
    time.sleep(1)
    show_all = driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[2]/div[3]/div[2]/div[4]')
    show_all.click()
    feed_item = {
        'info':driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[1]/div/div[1]/div[1]').text,
        'type_of_house':driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[2]/div[3]/div[1]/div[1]/span[1]').text,
        'num_of_people':driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[2]/div[3]/div[1]/div[2]/span[1]').text,
        'num_of_bed':driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[2]/div[3]/div[1]/div[3]/span[1]').text,
        'if_cook':driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[2]/div[3]/div[1]/div[1]/span[3]').text,
        'if_swim':'No',
        'if_supermarket':'No',
        'locate':driver.find_element_by_xpath('//*[@id="__next"]/div/div/div[1]/div/div[1]/div[3]/span').text,
        'url':driver.current_url,
        'price':driver.find_element_by_class_name('txt-price').text
    }
    if driver.find_elements_by_class_name('item-device-0507') != []:
        feed_item['id_swim'] = 'Have swim pool'
    if driver.find_elements_by_class_name("item-device-0501") != []:
        feed_item['if_supermarket'] = "Have super market"
    items.append(feed_item)

def GetAll(cnt):
    time.sleep(2)
    click_items = driver.find_elements_by_class_name("list-photo")
    global count
    for each in click_items:
        if (count >= 3):
            driver.close()
            return 1
        each.click()
        handle = driver.window_handles
        driver.switch_to_window(handle[1])
        time.sleep(1)
        name = driver.find_elements_by_class_name("tit")
        if (len(name) == 0):
            driver.close()
            driver.switch_to_window(handle[0])
            continue
        print str(count) + "." + name[0].text
        get_item()
        count = count + 1
        driver.close()
        driver.switch_to_window(handle[0])


while True:
    res = GetAll(count)
    if (res == 1):
        break
    next = driver.find_element_by_class_name("item-next")
    next.click()

print type(items[1]['info'])


with open('result.json', 'wt') as file:
    file.write(json.dumps(items))
