/*
 * BLEService.h
 *
 *  Created on: Mar 25, 2017
 *      Author: kolban
 */

#ifndef COMPONENTS_CPP_UTILS_BLESERVICE_H_
#define COMPONENTS_CPP_UTILS_BLESERVICE_H_
#include "sdkconfig.h"
#if defined(CONFIG_BT_ENABLED)

#include <esp_gatts_api.h>

#include "BLECharacteristic.h"
#include "BLEServer.h"
#include "BLEUUID.h"
#include "FreeRTOS.h"

class BLEServer;

/**
 * @brief A data mapping used to manage the set of %BLE characteristics known to the server.
 */
class BLECharacteristicMap {
public:
	void setByUUID(BLEUUID uuid, BLECharacteristic* pCharacteristic);
	void setByHandle(uint16_t handle, BLECharacteristic* pCharacteristic);
	BLECharacteristic* getByUUID(BLEUUID uuid);
	BLECharacteristic* getByHandle(uint16_t handle);
	BLECharacteristic* getFirst();
	BLECharacteristic* getNext();
	std::string toString();
	void handleGATTServerEvent(
			esp_gatts_cb_event_t      event,
			esp_gatt_if_t             gatts_if,
			esp_ble_gatts_cb_param_t* param);


private:
	std::map<std::string, BLECharacteristic*> m_uuidMap;
	std::map<uint16_t, BLECharacteristic*> m_handleMap;
	std::map<std::string, BLECharacteristic*>::iterator m_iterator;
};


/**
 * @brief The model of a %BLE service.
 *
 */
class BLEService {
public:
	BLEService(BLEUUID uuid);

	void               addCharacteristic(BLECharacteristic* pCharacteristic);
	BLECharacteristic* createCharacteristic(BLEUUID uuid, uint32_t properties);
	void               dump();
	void               executeCreate(BLEServer* pServer);
	BLECharacteristic* getCharacteristic(BLEUUID uuid);
	BLEUUID            getUUID();
	BLEServer*         getServer();
	void               start();
	std::string        toString();

private:
	friend class BLEServer;
	friend class BLEServiceMap;
	friend class BLEDescriptor;
	friend class BLECharacteristic;
	friend class BLEDevice;

	BLECharacteristicMap m_characteristicMap;
	uint16_t             m_handle;
	BLECharacteristic*   m_lastCreatedCharacteristic;
	BLEServer*           m_pServer;
	//FreeRTOS::Semaphore  m_serializeMutex;
	FreeRTOS::Semaphore m_semaphoreAddCharEvt = FreeRTOS::Semaphore("AddCharEvt");
	FreeRTOS::Semaphore m_semaphoreCreateEvt = FreeRTOS::Semaphore("CreateEvt");
	FreeRTOS::Semaphore m_semaphoreStartEvt = FreeRTOS::Semaphore("StartEvt");
	BLEUUID              m_uuid;

	uint16_t           getHandle();
	BLECharacteristic* getLastCreatedCharacteristic();
	void               handleGATTServerEvent(
		esp_gatts_cb_event_t      event,
		esp_gatt_if_t             gatts_if,
		esp_ble_gatts_cb_param_t* param);
	void               setHandle(uint16_t handle);
	//void               setService(esp_gatt_srvc_id_t srvc_id);
}; // BLEService


#endif // CONFIG_BT_ENABLED
#endif /* COMPONENTS_CPP_UTILS_BLESERVICE_H_ */
