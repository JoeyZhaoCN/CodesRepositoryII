import os
import time

source = ['F:\\WorkSpace\\2017\\12.04']
target_dir = 'E:\\backup'

if not os.path.exists(target_dir) :
    os.mkdir(target_dir)

today = target_dir + os.sep + time.strftime('%Y%m%d')
now = time.strftime('%H%M%S')

comment = input('Enter a Command -->')

if len(comment) == 0 :
    target = today + os.sep + now + '.zip'
else :
    target = today + os.sep + now + '_' +\
        comment.replace(' ', '_') + '.zip'

if not os.path.exists(today) :
    os.mkdir(today)
    print('Successfuly created directory', today)

zip_command = 'zip -r {} {}'.format(target, ' '.join(source))

# 运行备份
print('Zip command is:')
print(zip_command)
print('Running:')
if os.system(zip_command) == 0 :
    print('Successfuly backup to', target)
else :
    print('Backup failed')
