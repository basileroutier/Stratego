import sys
import os
import subprocess


def lazygit():
    commitDetail = input("Enter commit details : ")
    commit = 'git commit -m "' + commitDetail + '"'
    os.system('git add .')
    os.system(commit)
    os.system('git pull')
    os.system('git push')


lazygit()

# arrayError = [];
#
# push = 'git push'
#
# os.system('git add .')
# os.system(commit)
# arrayError.append(subprocess.getoutput(push))
#
# if(arrayError[0].find('pull')==0):
#     os.system('git fetch')
#     os.system('git pull')
#     os.system('git pull')
#     os.system('git push')





val=input("Press any key to end")
