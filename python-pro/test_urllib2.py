# coding=UTF-8

import urllib.request
import http.cookiejar
# responce = urllib.request.urlopen('http://www.baidu.com')
# print(responce.getcode())
# cont = responce.read()
# reqs = urllib.request.Request('http://www.baidu.com')
# reqs.add_header('User-Agent', 'Mozilla/5.0')
# responce = urllib.request.urlopen(reqs)
# print(responce.getcode())
cj = http.cookiejar.CookieJar()

opener = urllib.request.build_opener(urllib.request.HTTPCookieProcessor(cj))

urllib.request.install_opener(opener)

responce = urllib.request.urlopen('http://www.baidu.com')

print(responce.getcode())

cont = responce.read()

print(cont)
