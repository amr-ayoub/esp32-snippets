/*
 * BLEAdvertisedDevice.h
 *
 *  Created on: Jul 3, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_BLEADVERTISEDDEVICE_H_
#define COMPONENTS_CPP_UTILS_BLEADVERTISEDDEVICE_H_
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)
#include <esp_gattc_api.h>

#include <map>

#include "BLEAddress.h"
#include "BLEScan.h"
#include "BLEUUID.h"


class BLEScan;
/**
 * @brief A representation of a %BLE advertised device found by a scan.
 *
 * When we perform a %BLE scan, the result will be a set of devices that are advertising.  This
 * class provides a model of a detected device.
 */
class BLEAdvertisedDevice {
public:
	BLEAdvertisedDevice();

	BLEAddress  getAddress();
	uint16_t    getApperance();
	std::string getManufacturerData();
	std::string getName();
	int         getRSSI();
	BLEScan*    getScan();
	BLEUUID     getServiceUUID();
	int8_t      getTXPower();

	bool        haveAppearance();
	bool        haveManufacturerData();
	bool        haveName();
	bool        haveRSSI();
	bool        haveServiceUUID();
	bool        haveTXPower();

	std::string toString();

private:
	friend class BLEScan;

	void parseAdvertisement(uint8_t* payload);
	void setAddress(BLEAddress address);
	void setAdFlag(uint8_t adFlag);
	void setAdvertizementResult(uint8_t* payload);
	void setAppearance(uint16_t appearance);
	void setManufacturerData(std::string manufacturerData);
	void setName(std::string name);
	void setRSSI(int rssi);
	void setScan(BLEScan* pScan);
	void setServiceUUID(BLEUUID serviceUUID);
	void setTXPower(int8_t txPower);

	bool m_haveAppearance;
	bool m_haveManufacturerData;
	bool m_haveName;
	bool m_haveRSSI;
	bool m_haveServiceUUID;
	bool m_haveTXPower;


	BLEAddress  m_address = BLEAddress((uint8_t*)"\0\0\0\0\0\0");
	uint8_t     m_adFlag;
	uint16_t    m_appearance;
	int         m_deviceType;
	std::string m_manufacturerData;
	std::string m_name;
	BLEScan*    m_pScan;
	int         m_rssi;
	BLEUUID     m_serviceUUID;
	int8_t      m_txPower;
};

/**
 * @brief A callback handler for callbacks associated device scanning.
 *
 * When we are performing a scan as a %BLE client, we may wish to know when a new device that is advertising
 * has been found.  This class can be sub-classed and registered such that when a scan is performed and
 * a new advertised device has been found, we will be called back to be notified.
 */
class BLEAdvertisedDeviceCallbacks {
public:
	virtual ~BLEAdvertisedDeviceCallbacks() {}
	/**
	 * @brief Called when a new scan result is detected.
	 *
	 * As we are scanning, we will find new devices.  When found, this call back is invoked with a reference to the
	 * device that was found.  During any individual scan, a device will only be detected one time.
	 */
	virtual void onResult(BLEAdvertisedDevice* pAdvertisedDevice) = 0;
};

#endif /* CONFIG_BT_ENABLED */
#endif /* COMPONENTS_CPP_UTILS_BLEADVERTISEDDEVICE_H_ */
