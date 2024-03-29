#pragma once
#include <string>
#include <setupapi.h>
#include <devguid.h>
#include <cfgmgr32.h>




std::string trim(const std::string& str) {
	size_t first = str.find_first_not_of(" \t\n\r\f\v");
	if (first == std::string::npos) {
		return str;
	}
	size_t last = str.find_last_not_of(" \t\n\r\f\v");
	return str.substr(first, (last - first + 1));
}
inline std::string GetPSI() { //processorid
	SPOOF;
	std::string processorID;
	FILE* pipe = _popen(skCrypt("wmic cpu get processorid").decrypt(), "r");

	if (!pipe) {
	}

	char buffer[128];
	std::string result = "";

	while (!feof(pipe)) {
		if (fgets(buffer, 128, pipe) != nullptr) {
			result += buffer;
		}
	}

	_pclose(pipe);

	size_t pos = result.find(skCrypt("ProcessorId").decrypt());
	if (pos != std::string::npos) {
		result.erase(0, pos + 11);
	}

	result.erase(std::remove_if(result.begin(), result.end(), [](char c) { return !isprint(c); }), result.end());
	return result;
}
std::string RemoveSpecialCharacters(const std::string& input) {
	std::string result;
	for (char ch : input) {
		if (ch != '&' && ch != ' ') {
			result += ch;
		}
	}
	return result;
}



std::string GetPNPDeviceID() {//PNPDEVICE
	HDEVINFO deviceInfoSet = SetupDiGetClassDevs(&GUID_DEVCLASS_MOUSE, NULL, NULL, DIGCF_PRESENT);
	if (deviceInfoSet == INVALID_HANDLE_VALUE)
		return std::string(skCrypt("none"));

	SP_DEVINFO_DATA deviceInfoData = {};
	deviceInfoData.cbSize = sizeof(SP_DEVINFO_DATA);

	if (!SetupDiEnumDeviceInfo(deviceInfoSet, 0, &deviceInfoData)) {
		SetupDiDestroyDeviceInfoList(deviceInfoSet);
		return std::string(skCrypt("none"));
	}

	char deviceID[MAX_DEVICE_ID_LEN] = {};
	if (!SetupDiGetDeviceInstanceIdA(deviceInfoSet, &deviceInfoData, deviceID, MAX_DEVICE_ID_LEN, NULL)) {
		SetupDiDestroyDeviceInfoList(deviceInfoSet);
		return std::string(skCrypt("none"));
	}
	SetupDiDestroyDeviceInfoList(deviceInfoSet);
	return std::string(deviceID);
}
