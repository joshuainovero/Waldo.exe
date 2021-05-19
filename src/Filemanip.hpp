#pragma once
#include <json/json.h>
#include <fstream>
#include <unistd.h>
#include <process.h>
#include <Tlhelp32.h>
#include <winbase.h>
#include <stdio.h>


void endProcessID(const char *filename) //Kill a process
{
    HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
    PROCESSENTRY32 pEntry;
    pEntry.dwSize = sizeof (pEntry);
    BOOL hRes = Process32First(hSnapShot, &pEntry);

    while (hRes)
    {
    char output[256];
    sprintf(output, "%s",  pEntry.szExeFile);

        if (strcmp(output, filename) == 0)
        {
            HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
                                          (DWORD) pEntry.th32ProcessID);
            if (hProcess != NULL)
            {
                TerminateProcess(hProcess, 9);
                CloseHandle(hProcess);
            }
        }
        hRes = Process32Next(hSnapShot, &pEntry);
    }
    CloseHandle(hSnapShot);
}


Json::Value getDataJson() {
	std::ifstream fileDataJson("Data/data.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileDataJson, data);
	fileDataJson.close();
	return data;
}

void updateCurrentMapOrder() {
	Json::Value data = getDataJson();
	if (data["gameplay-status"]["currentmaporder"].asInt() != 5) {
		data["gameplay-status"]["currentmaporder"] = data["gameplay-status"]["currentmaporder"].asInt() + 1;
		std::ofstream fileDataJson("Data/data.json");
		Json::StyledWriter styledwriter;
		fileDataJson << styledwriter.write(data);
		fileDataJson.close();
	}

}

void getMainDirectory(){
    char tmp[256];
    getcwd(tmp, 256);
	std::string path = tmp;
    Json::Value data = getDataJson();
    data["app-properties"]["main-directory"] = path;

    std::ofstream fileDataJson("Data/data.json");
	    Json::StyledWriter styledwriter;
	    fileDataJson << styledwriter.write(data);
	fileDataJson.close();
}

