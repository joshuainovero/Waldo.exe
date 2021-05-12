import subprocess
import requests
import json
import os
localVersion = None
githubVersion = None

# Local Version
jsonLocalVersion = json.load(open('../version.json'))
localVersion = str(jsonLocalVersion["localversion"])

# Version from github
requestVersion = requests.get('https://joshuainovero.github.io/versions/versions.json')
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

openState = open("state","r")
fLine = openState.readline()[:-1]
if (fLine == "Updated"):
    with open('../version.json','w') as versionfile:
        jsonLocalVersion["localversion"] = githubVersion
        json.dump(jsonLocalVersion, versionfile)

os.system('pause')



