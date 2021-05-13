import subprocess
from zipfile import ZipFile
import requests
import json
import os
import ctypes

ctypes.windll.user32.ShowWindow(ctypes.windll.kernel32.GetConsoleWindow(), 0)

localVersion = None
githubVersion = None
jsonData = json.load(open('../Data/data.json'))

# Local Version
localVersion = str(jsonData["app-properties"]["localversion"])

# Version from github
requestVersion = requests.get(str(jsonData["app-properties"]["update-link"]))
jsonVersionGithubData = json.loads(requestVersion.text)
githubVersion = str(jsonVersionGithubData["waldoversion"])
writeTransferVersion = open("transferversion","w")
writeTransferVersion.write(githubVersion)
writeTransferVersion.close()

if (localVersion != githubVersion):
    writeUpdateRequired = open("UpdateRequired","w")
    writeUpdateRequired.write("True")
    writeUpdateRequired.close()
    subprocess.call([r'dlupdate.bat'])
    
else: 
    writeUpdateRequired = open("UpdateRequired","w")
    writeUpdateRequired.write("False")
    writeUpdateRequired.close()
    print('Game is already updated')

# openState = open("state","r")
# fLine = openState.readline()[:-1]
# if (fLine == "Updated"):
#     with open('../version.json','w') as versionfile:
#         jsonLocalVersion["localversion"] = githubVersion
#         json.dump(jsonLocalVersion, versionfile)
#         print("")

os.system('pause')



