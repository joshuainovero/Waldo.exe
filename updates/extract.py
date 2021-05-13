import os
import os.path
import json
import shutil
from tkinter import *
from tkinter import messagebox
from zipfile import ZipFile
from pathlib import Path
root = Tk()

readJSONMainPath = json.load(open("../Data/data.json"))
moveReady = False
def moveFile(root_src_dir, root_dst_dir): # Move files
    for src_dir, dirs, files in os.walk(root_src_dir):
        dst_dir = src_dir.replace(root_src_dir, root_dst_dir, 1)
        if not os.path.exists(dst_dir):
            os.makedirs(dst_dir)
        for file_ in files:
            src_file = os.path.join(src_dir, file_)
            dst_file = os.path.join(dst_dir, file_)
            if os.path.exists(dst_file):
                if os.path.samefile(src_file, dst_file):
                    continue
                os.remove(dst_file)
            shutil.move(src_file, dst_dir)

try:
    with ZipFile('updatefiles.zip', 'r') as zipObj: # unzip downloaded updates
        zipObj.extractall()
    moveReady = True
except:
    root.withdraw()
    messagebox.showerror("Waldo", "Cannot extract updates! - INSTALLATION ERROR\nUpdate your program again")


if (moveReady):
    try:
        #Files to move
        waldoEXEPath = str(Path('updatefiles/exe').absolute())
        assetsPath = str(Path('updatefiles/Assets').absolute())

        # Waldo.exe
        print(waldoEXEPath)
        exeDestinationPath = str(readJSONMainPath["MainDirectory"])
        print(exeDestinationPath)
        moveFile(waldoEXEPath, exeDestinationPath)

        # Assets
        print(assetsPath)
        assetsDestinationPath = str(readJSONMainPath["MainDirectory"]) + "\\Assets"
        print(assetsDestinationPath)
        moveFile(assetsPath, assetsDestinationPath)
    except:
        root.withdraw()
        messagebox.showerror("Waldo", "Error in moving files!")

# def process_exists(process_name):
#     call = 'TASKLIST', '/FI', 'imagename eq %s' % process_name
#     output = subprocess.check_output(call).decode()
#     last_line = output.strip().split('\r\n')[-1]
#     return last_line.lower().startswith(process_name.lower())
    
# os.system("TASKKILL /F /IM Waldo.exe 2>NULL")



