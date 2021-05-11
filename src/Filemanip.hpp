#pragma once
#include <json/json.h>
#include <fstream>
#include <unistd.h>

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
	if (data["currentMapOrder"].asInt() != 5) {
		data["currentMapOrder"] = data["currentMapOrder"].asInt() + 1;
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
    data["MainDirectory"] = path;

    std::ofstream fileDataJson("Data/data.json");
	    Json::StyledWriter styledwriter;
	    fileDataJson << styledwriter.write(data);
	fileDataJson.close();
}


void updateVersion(){
	std::ifstream fileVersionJSON("version.json");
		Json::Value data;
		Json::Reader reader;
		reader.parse(fileVersionJSON, data);
	fileVersionJSON.close();

    std::ofstream updateVersionJSON("version.json");
        std::ifstream readTransferVersion("updates/transferversion");
            std::string newVersion;
            readTransferVersion >> newVersion;
        readTransferVersion.close();

        data["localversion"] = newVersion;
        Json::StyledWriter styledwriter;
        updateVersionJSON << styledwriter.write(data);
    updateVersionJSON.close();

}