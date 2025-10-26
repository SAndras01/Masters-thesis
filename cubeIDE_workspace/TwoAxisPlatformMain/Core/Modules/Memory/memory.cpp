/*
 * memory.cpp
 *
 *  Created on: 2024. júl. 8.
 *      Author: SNA1BP
 */


#include "memory.hpp"

HAL_StatusTypeDef writeMultiPage(I2C_HandleTypeDef* I2Ccontroller, uint8_t EEPROMAddress, uint16_t start, uint8_t *data_p, uint16_t len, uint8_t pageLen)
{
	HAL_StatusTypeDef stat;

	uint16_t remainder; //this much is left until the end of the current page
	while(len != 0)
	{
		remainder = (pageLen-((start)%pageLen));

		if( remainder <= len )
		{
			while (HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100) != HAL_OK)
			{
				HAL_Delay(5);
			}

			stat = HAL_I2C_Mem_Write(I2Ccontroller, EEPROMAddress<<1, start, I2C_MEMADD_SIZE_16BIT, data_p, remainder, HAL_MAX_DELAY);

			while(stat != HAL_OK)
			{
				stat = HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100);
			}

			start += remainder; //shift the "writer"
			len -= remainder; //decrease the remaining length
			data_p += remainder*sizeof(uint8_t); //shift the "reader"
		}
		else//write the rest of the data
		{
			while (HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100) != HAL_OK)
			{
				HAL_Delay(5);
			}

			stat = HAL_I2C_Mem_Write(I2Ccontroller, EEPROMAddress<<1, start, I2C_MEMADD_SIZE_16BIT, data_p, len, HAL_MAX_DELAY);

			while(stat != HAL_OK)
			{
				stat = HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100);
			}

			len = 0;

		}
	}
	return stat;
}

//Basically the same as writeMultiPage, with the exception that here an array filled with 128 0xFF is used as the data
HAL_StatusTypeDef deleteRegion(I2C_HandleTypeDef* I2Ccontroller, uint8_t EEPROMAddress, uint16_t start, uint16_t len, uint8_t pageLen)
{
	uint8_t ereaserBuffer[pageLen];
	for(uint8_t i = 0; i < pageLen; i++){ ereaserBuffer[i]=0xFF; }

	HAL_StatusTypeDef stat;

	uint16_t remainder; //this much is left until the end of the current page
	while(len != 0)
	{
		remainder = (pageLen-((start)%pageLen));

		if( remainder <= len )
		{
			//255 from start until EOP then len = len-remainder, start = start + remainder
			while (HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100) != HAL_OK)
			{
				HAL_Delay(5);
			}
			stat = HAL_I2C_Mem_Write(I2Ccontroller, EEPROMAddress<<1, start, I2C_MEMADD_SIZE_16BIT, ereaserBuffer, remainder, 100);

			while(stat != HAL_OK)
			{
				stat = HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100);
			}

			//Here the "reader" is not increased
			start += remainder;
			len -= remainder;
		}
		else
		{
			//255 from start until len then len = 0
			while (HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100) != HAL_OK)
			{
				HAL_Delay(5);
			}
			stat = HAL_I2C_Mem_Write(I2Ccontroller, EEPROMAddress<<1, start, I2C_MEMADD_SIZE_16BIT, ereaserBuffer, len, 100);

			while(stat != HAL_OK)
			{
				stat = HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100);
			}

			len = 0;

		}
	}
	return stat;
}


Memory::Memory(memoryElement* dict_p, uint16_t dictLen_p, MemoryErrorCallback_t errorCallback_p, Stream* stream_p)
{
	if(errorCallback_p)	{ attachErrorCallback(errorCallback_p); }
	if(stream_p)		{ attachStream(stream_p); }

	dict = dict_p;
	dictLen = dictLen_p;
	for(uint16_t i = 0; i< dictLen; i++)
	{
		dict[i].master = this;
	}
}


void Memory::attachErrorCallback( MemoryErrorCallback_t errorCallback_p ) { errorCallback = errorCallback_p; }

void Memory::attachStream(Stream* stream_p) { stream = stream_p; }

bool Memory::getValue(const char* key_p, uint8_t* result_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			return _getValue(dict[i].start, result_p, i8);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}
bool Memory::getValue(const char* key_p, uint16_t* result_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			return _getValue(dict[i].start, result_p, i16);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}
bool Memory::getValue(const char* key_p, uint32_t* result_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			return _getValue(dict[i].start, result_p, i32);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}
bool Memory::getValue(const char* key_p, const char* result_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			return _getValue(dict[i].start,(char*) result_p, charstring);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}


bool Memory::setValue(const char* key_p, uint8_t value_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			dict[i].deleteData();
			return _setValue(dict[i].start, &value_p, i8);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}
bool Memory::setValue(const char* key_p, uint16_t value_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			dict[i].deleteData();
			return _setValue(dict[i].start, &value_p, i16);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}
bool Memory::setValue(const char* key_p, uint32_t value_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			dict[i].deleteData();
			return _setValue(dict[i].start, &value_p, i32);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}
bool Memory::setValue(const char* key_p, const char* value_p)
{
	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			dict[i].deleteData();
			return _setValue(dict[i].start, (char*)value_p, charstring);
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}
	return false;
}

void Memory::listAll(Stream* stream_p)
{
	if(stream_p)
	{
		stream = stream_p;
	}

	char msg[250];

	for(uint16_t i = 0; i < dictLen; i++)
	{
		switch(dict[i].type)
		{
			case i8:
				uint8_t value8;
				getValue(dict[i].key, &value8);
				sniprintf(msg, sizeof(msg), "%s - %" PRIu8 "\r\n", dict[i].key, value8);
				stream->print(msg);
				break;

			case i16:
				uint16_t value16;
				getValue(dict[i].key, &value16);
				sniprintf(msg, sizeof(msg), "%s - %" PRIu16 "\r\n", dict[i].key, value16);
				stream->print(msg);
				break;

			case i32:
				uint32_t value32;
				getValue(dict[i].key, &value32);
				sniprintf(msg, sizeof(msg), "%s - %" PRIu32 "\r\n", dict[i].key, value32);
				stream->print(msg);
				break;

			case charstring:
				char valuestr[128];
				getValue(dict[i].key, (const char*)valuestr);
				sniprintf(msg, sizeof(msg), "%s - %s\r\n", dict[i].key, valuestr);
				stream->print(msg);
				break;

			default:
				if(errorCallback)
				{
					errorCallback(this, INVALID_TYPE_ERROR, dict[i].key);
				}
				break;
		}
	}
}

bool memoryElement::deleteData(){ return master->deleteElementData(key); }

void memoryElement::print()
{
	char msg[250];

	switch(type)
	{
		case i8:
			uint8_t value8;
			master->getValue(key, &value8);
			sniprintf(msg, sizeof(msg), "%s - %" PRIu8 "\r\n", key, value8);
			master->stream->print(msg);
			break;

		case i16:
			uint16_t value16;
			master->getValue(key, &value16);
			sniprintf(msg, sizeof(msg), "%s - %" PRIu16 "\r\n", key, value16);
			master->stream->print(msg);
			break;

		case i32:
			uint32_t value32;
			master->getValue(key, &value32);
			sniprintf(msg, sizeof(msg), "%s - %" PRIu32 "\r\n", key, value32);
			master->stream->print(msg);
			break;

		case charstring:
			char valuestr[128];
			master->getValue(key, (const char*)valuestr);
			sniprintf(msg, sizeof(msg), "%s - %s\r\n", key, valuestr);
			master->stream->print(msg);
			break;

		default:
			if(master->errorCallback)
			{
				master->errorCallback(master, INVALID_TYPE_ERROR, key);
			}
			break;
	}
}

void memoryElement::operator = (uint8_t value_p){ master->setValue(key, value_p); }
void memoryElement::operator = (uint16_t value_p){ master->setValue(key, value_p); }
void memoryElement::operator = (uint32_t value_p){ master->setValue(key, value_p); }
void memoryElement::operator = (const char* value_p){ master->setValue(key, value_p); }

EEPROMmemory::EEPROMmemory(memoryElement* dict_p, uint16_t dictLen_p, uint8_t EEPROMAddress_p, I2C_HandleTypeDef* i2c_handle, MemoryErrorCallback_t errorCallback_p, Stream* stream_p):Memory(dict_p, dictLen_p, errorCallback_p, stream_p)
{
	EEPROMAddress = EEPROMAddress_p;
	I2Ccontroller = i2c_handle;

	Init();
}

HAL_StatusTypeDef EEPROMmemory::writeHeader(memoryElement element_p, uint16_t headerStart_p)
{
	memoryElement test = element_p;
    uint8_t headerBuffer[headerLen];
    for(uint8_t i = 0; i<headerLen; i++) { headerBuffer[i] = 0xFF; }

    memcpy((uint8_t*)(headerBuffer+keyStarts), element_p.key, strlen(element_p.key)+1);
	memcpy((uint8_t*)(headerBuffer+startStarts), &(element_p.start), sizeof(element_p.start));
	memcpy((uint8_t*)(headerBuffer+lenStarts), &(element_p.len), sizeof(element_p.len));
	memcpy((uint8_t*)(headerBuffer+typeStarts), &(element_p.type), sizeof(element_p.type));

	HAL_StatusTypeDef stat;


	HAL_Delay(5);
	stat = HAL_I2C_Mem_Write(I2Ccontroller, EEPROMAddress<<1, headerStart_p, I2C_MEMADD_SIZE_16BIT, headerBuffer, sizeof(headerBuffer), HAL_MAX_DELAY);

	while(stat != HAL_OK)
	{
		stat = HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100);
	}

	return stat;
}

memoryElement EEPROMmemory::readHeader(uint16_t headerStart_p)
{
	uint8_t headerBuffer[headerLen];

	uint8_t		keyToRead[12];
    uint16_t 	startToRead;
    uint8_t 	lenToRead;
    elementType	typeToRead;

    HAL_StatusTypeDef stat;

    HAL_Delay(5);
	stat = HAL_I2C_Mem_Read(I2Ccontroller, EEPROMAddress<<1, headerStart_p, I2C_MEMADD_SIZE_16BIT, headerBuffer ,sizeof(headerBuffer), HAL_MAX_DELAY);
	while(stat != HAL_OK)
	{
		stat = HAL_I2C_Mem_Read(I2Ccontroller, EEPROMAddress<<1, headerStart_p, I2C_MEMADD_SIZE_16BIT, headerBuffer ,sizeof(headerBuffer), HAL_MAX_DELAY);
	}

	memcpy(keyToRead, (uint8_t*)(headerBuffer+keyStarts), startStarts);
	memcpy(&startToRead, (uint8_t*)(headerBuffer+startStarts) ,sizeof(startToRead));
	memcpy(&lenToRead, (uint8_t*)(headerBuffer+lenStarts) ,sizeof(lenToRead));
	memcpy(&typeToRead, (uint8_t*)(headerBuffer+typeStarts) ,sizeof(typeToRead));

	memoryElement fetchedElement;

	fetchedElement.key = (const char*) keyToRead;
	fetchedElement.start = startToRead;
	fetchedElement.len = lenToRead;
	fetchedElement.type = typeToRead;

	return fetchedElement;
}

void EEPROMmemory::Init()
{
	/**
	 * Read the saved headers from the EEPROM -> compare with the dict:
	 * There is a match -> set the attributes of the dict's element to the one found saved on the EEPROM
	 * There is not a match -> the element is no longer needed -> delete the header and the stored data associated with it from the EEPROM. These formatted parts will be reused
	 *
	 * If there are elements in the dict that were not saved into the EEPROM yet -> write the header and set the start value
	 *
	 */


	uint16_t firstEmptyHeaderAddress = 0;

	uint16_t deletedHeaderRegions[440];
	for(uint16_t i = 0; i<440; i++){ deletedHeaderRegions[i] = 0xFFFF; } //Initialize with an impossible address

	uint16_t deletedDataRegions[440];
	for(uint16_t i = 0; i<440; i++){ deletedDataRegions[i] = 0xFFFF; } //Initialize with an impossible address


	memoryElement fetchedElement;


    uint16_t n = 0;
    uint16_t headerAddress = 0;

    uint16_t j = 0;

    bool addressDuplicates = false;
    while(n < 440)
    {
    bool inDict = 0;
    	headerAddress = n*headerLen;

		fetchedElement = readHeader(headerAddress);

		//Test if fetched key is empty
		bool mptyKey = 1;
		for(uint8_t i = 0; i<12; i++)
		{
			if((uint8_t)fetchedElement.key[i] != 0xFF)
			{
				mptyKey = 0;
				break;
			}
		}

		if(mptyKey)
		{
			firstEmptyHeaderAddress = headerAddress;
			break;
		}

		for(uint16_t i = 0; i<dictLen; i++)
		{
			if(strcmp(dict[i].key, fetchedElement.key) == 0)
			{
			    //Check for address duplicates
				addressDuplicates = false;
			    for(uint16_t k = 1; k < i; k++)
			    {
					if (fetchedElement.start == dict[k].start)
					{
						addressDuplicates = true;
					}
			    }

				//Test if the address of the found element is a duplicate or invalid -> not divisible by 128 OR not greater than 55*128 OR larger than 64000
				if( (fetchedElement.start%128 != 0) || (fetchedElement.start < 55*128) || (fetchedElement.start >= 64000) )
				{
					break;
				}
				else
				{
					dict[i].foundAtInit = 1;
					inDict = 1;

					dict[i].start = fetchedElement.start;

					if(dict[i].type != fetchedElement.type)
					{
						dict[i].type = fetchedElement.type;
						if(errorCallback)
						{
							errorCallback(this, TYPE_MISSMATCH_ERROR, dict[i].key);
						}
					}
				}
				break;
			}
		}

		if(!inDict)//Delete the header as well as the data if it was not listed in the dict or the address was invalid
		{
			deleteRegion(I2Ccontroller, EEPROMAddress, headerAddress, headerLen);
			deletedHeaderRegions[j] = headerAddress;

			//Check if the address is valid
			if( (fetchedElement.start%128 == 0) && (fetchedElement.start >= 55*128) && (fetchedElement.start <= 64000) )
			{
				deleteRegion(I2Ccontroller, EEPROMAddress, fetchedElement.start, pageLen);
				deletedDataRegions[j]   = fetchedElement.start;
			}
			else
			{
				if(errorCallback)
				{
					errorCallback(this, INVALID_ADDRESS, fetchedElement.key);
				}
			}
			j++;
		}
		n++;
    }//while(n < 440)

    //Check for address duplicates
    for(uint16_t k = 1; k < j; k++)
    {
		addressDuplicates = false;
    	for(uint16_t L = 0; L < k; L++)
    	{
    		if(deletedDataRegions[k] == deletedDataRegions[L])
    		{
    			addressDuplicates = true;
    			break;
    		}
    	}
    	if(addressDuplicates) //delete it by making it an impossible address
    	{
    		deletedDataRegions[k] = 0xFFFF;
    	}
    }

    uint16_t proposedDataStartAddress = 0;
    bool AddrCcollision = true;
    j = 0;
    for(uint16_t i = 0; i<dictLen; i++)
    {
    	//Not found at init, needs to be saved into EEPROM
    	if(dict[i].foundAtInit == 0)
    	{
    		if(deletedHeaderRegions[j] != 0xFFFF)//Fill in the deleted regions
    		{
    			/*	becaouse of the line "if( (fetchedElement.start%128 == 0) && (fetchedElement.start >= 55*128) )" this list might have "gaps"
    			*	duplicates were also marked by setting them to 0xFFFF
    			*/
    			if(deletedDataRegions[j] != 0xFFFF) //Valid data start address
    			{
    				dict[i].start = deletedDataRegions[j];
    			}
    			else
    			{
    				//give it an address, but first check if it collides with any previously given addresses
    				proposedDataStartAddress = pageLen * (i+55); //one data per page
    				uint16_t increment = 1;
    				while(AddrCcollision && increment <= 501)
    				{
    					for(uint16_t k = 0; k<=i; k++)
    					{
    						if(dict[k].start == proposedDataStartAddress)
    						{
    							AddrCcollision = true;
    							proposedDataStartAddress += increment * pageLen; //collision detected, shift it with one page then check again
    							break;
    						}
    						AddrCcollision = false;
    					}
    					increment++;
    				}
    				if(increment > 500)
    				{
    					//TODO manage memory full
    				}
    				dict[i].start = proposedDataStartAddress;
    				deleteRegion(I2Ccontroller, EEPROMAddress, dict[i].start, pageLen);
    			}
    			writeHeader(dict[i], deletedHeaderRegions[j]);
    			j++;
    		}

    		else //deletedHeaderRegions[j] is a valid address for the header
    		{
				//give it an address, but first check if it collides with any previously given addresses
				proposedDataStartAddress = pageLen * (i+55); //one data per page
				uint16_t increment = 1;
				while(AddrCcollision && increment <= 501)
				{
					for(uint16_t k = 0; k<=i; k++)
					{
						if(dict[k].start == proposedDataStartAddress)
						{
							AddrCcollision = true;
							proposedDataStartAddress += increment * pageLen; //collision detected, shift it with one page then check again
							break;
						}
						AddrCcollision = false;
					}
					increment++;
				}
				if(increment > 500)
				{
					//TODO manage memory full
				}
				dict[i].start = proposedDataStartAddress;
				deleteRegion(I2Ccontroller, EEPROMAddress, dict[i].start, pageLen); // erase the occupied page

				writeHeader(dict[i], firstEmptyHeaderAddress);

				firstEmptyHeaderAddress += headerLen;//The address of the next header
    		}
    	}

    }


}

bool EEPROMmemory::_getValue(uint32_t start_p, void* result_p, elementType type_p)
{
	HAL_StatusTypeDef stat;

	size_t len;

	switch(type_p)
	{
		case i8:
			len = sizeof(uint8_t);
			break;
		case i16:
			len = sizeof(uint16_t);
			break;
		case i32:
			len = sizeof(uint32_t);
			break;
		case charstring:
			len = pageLen;
			break;
		default:
			break;
	}

	HAL_Delay(5);
	stat = HAL_I2C_Mem_Read(I2Ccontroller, EEPROMAddress<<1, start_p, I2C_MEMADD_SIZE_16BIT, (uint8_t*)result_p ,len, 1000);

	while(stat != HAL_OK)
	{
		stat = HAL_I2C_Mem_Read(I2Ccontroller, EEPROMAddress<<1, start_p, I2C_MEMADD_SIZE_16BIT, (uint8_t*)result_p , len, 1000);
		HAL_Delay(5);
	}

	if(stat == HAL_OK){ return true; }
	return false;
}


void EEPROMmemory::updateHeader(uint32_t start_p, elementType type_p)
{
	bool typeChange = false;

	//find the header based on the start. (There can be no two header with the same data address)
	for(uint16_t i = 0; i < dictLen; i++)
	{
		if(dict[i].start == start_p && dict[i].type != type_p) //The start is the same but the type is not -> the type has changed
		{
			typeChange = true;
			dict[i].type = type_p;
			break;
		}
	}


	//If the type is changed it has to be updated in the EEPROM so in the case of a shut down the data of the element can be correctly read
	if(typeChange)
	{
		uint16_t headerAddress = 0;
		memoryElement currentHeader;
		for(uint16_t i = 0; i<dictLen; i++)
		{
			headerAddress = i*headerLen;
			currentHeader = readHeader(headerAddress);
			if( currentHeader.start == start_p )
			{
				currentHeader.type = type_p;
				writeHeader(currentHeader, headerAddress);
				break;
			}
		}
	}

}

bool EEPROMmemory::_setValue(uint32_t start_p, void* value_p, elementType type_p)
{
	// First we have to update the header if needed
	updateHeader(start_p, type_p);

	// After the header in the EEPROM have been updated(if needed) we can proceed to change the data
	HAL_StatusTypeDef stat;

	size_t len;

	switch(type_p)
	{
		case i8:
			len = sizeof(uint8_t);
			break;
		case i16:
			len = sizeof(uint16_t);
			break;
		case i32:
			len = sizeof(uint32_t);
			break;
		case charstring:
			len = strlen((const char*)value_p) + 1;
			break;
		default:
			break;
	}


	HAL_Delay(5);
	stat = HAL_I2C_Mem_Write(I2Ccontroller, EEPROMAddress<<1, (uint16_t)start_p, I2C_MEMADD_SIZE_16BIT, (uint8_t*)value_p, len, HAL_MAX_DELAY);

	while(stat != HAL_OK)
	{
		stat = HAL_I2C_IsDeviceReady(I2Ccontroller, EEPROMAddress<<1, 2, 100);
	}


	if(stat == HAL_OK){ return true; }
	return false;
}

bool EEPROMmemory::deleteElementData(const char* key_p)
{
	HAL_StatusTypeDef stat = HAL_ERROR;

	for(int i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			stat = deleteRegion(I2Ccontroller, EEPROMAddress, dict[i].start, pageLen);
			if(stat == HAL_OK){ return true; }
			return false;
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}

	if(stat == HAL_OK){ return true; }
	return false;
}

memoryElement EEPROMmemory::operator []  (const char* key_p)
{
	for(uint8_t i = 0; i<dictLen; i++)
	{
		if(strcmp(dict[i].key, key_p) == 0)
		{
			return dict[i];
		}
	}

	if(errorCallback)
	{
		errorCallback(this, KEY_ERROR, key_p);
	}

	return {""};
}


























