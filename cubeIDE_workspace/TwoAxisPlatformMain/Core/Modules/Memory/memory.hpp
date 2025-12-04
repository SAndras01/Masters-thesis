/*
 * memory.hpp
 *
 *  Created on: 2024. júl. 8.
 *      Author: Sásdi András
 */

//TODO: CREATE_I8_ELEMENT to work with array init

#ifndef MEMORY_MEMORY_HPP_
#define MEMORY_MEMORY_HPP_

#define MAX_KEY_LENGTH 12
#define STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)
#define CHECK_KEY_LENGTH(str) STATIC_ASSERT((strlen(str) <= MAX_KEY_LENGTH), "Key is longer than 12 characters")

#define CREATE_I8_ELEMENT(key) {key, 0, 128, i8}; CHECK_KEY_LENGTH(key)

#include <iostream>
#include <string.h>
#include <inttypes.h>
#include "Stream.hpp"
#include "main.h"

enum elementType
{
	i8,			/*!< uint8_t */
	i16,		/*!< uint16_t */
	i32,		/*!< uint32_t */
	charstring	/*!< const char* */
}; //Supported types to be stored


enum MemoryError_t
{
	KEY_ERROR,				/*!< Threw if no matching key was found
							@note Threw by functions:\n
							\link Memory::getValue \endlink,
							\link Memory::setValue \endlink (consequently \link memoryElement::operator = \endlink ),
							\link Memory::deleteElementData \endlink (consequently \link memoryElement::deleteData \endlink ) and
							\link Memory::operator [] \endlink
							*/
	INVALID_TYPE_ERROR,		/*!< Threw if the type does not match the enum \link elementType \endlink
	 	 	 	 	 	 	 @note Threw by functions:\n
	 	 	 	 	 	 	 \link Memory::listAll \endlink and
	 	 	 	 	 	 	 \link memoryElement::print \endlink.
	 	 	 	 	 	 	 */
	TYPE_MISSMATCH_ERROR,	/*!< Threw if the saved type doesn't match with the initializer list
							 @note Threw by functions:\n
	 	 	 	 	 	 	 \link EEPROMmemory::Init() \endlink (called by \link EEPROMmemory::EEPROMmemory \endlink).
	 	 	 	 	 	 	 */
	INVALID_ADDRESS			/*!< Threw if the start address of the saved header is not a valid one
	 	 	 	 	 	 	 @note Threw by functions:\n
	 	 	 	 	 	 	 \link EEPROMmemory::Init() \endlink (called by \link EEPROMmemory::EEPROMmemory \endlink).
	 	 	 	 	 	 	 */
}; //Error codes

/**
* @brief Write data that can go through page boundaries or write data longer than a page.
*
* @param I2Ccontroller The I2C controller used to communicate with the EEPROM
* @param EEPROMAddress The I2C address of the EEPROM
* @param start The address in the EEPROM where the data will be saved
* @param data_p Pointer to the data to be written (must be casted to (uint8_t*))
* @param len The length of the data.
* @param pageLen The length of one page in the EEPROM (defaults to 128)
*
*/
HAL_StatusTypeDef writeMultiPage(I2C_HandleTypeDef* I2Ccontroller, uint8_t EEPROMAddress, uint16_t start, uint8_t *data_p, uint16_t len, uint8_t pageLen = 128);

/**
* @brief Delete the stored data from the EEPROM on a given interval (can cross page boundaries)
*
* @param I2Ccontroller The I2C controller used to communicate with the EEPROM
* @param EEPROMAddress The I2C address of the EEPROM
* @param from The address in the EEPROM from where data will be erased
* @param len The length of the area to be deleted in bytes
* @param pageLen The length of one page in the EEPROM (defaults to 128)
*
* @note Fills the given region with 0xFF
*
*/
HAL_StatusTypeDef deleteRegion(I2C_HandleTypeDef* I2Ccontroller, uint8_t EEPROMAddress, uint16_t from, uint16_t len, uint8_t pageLen = 128);

class Memory; //To make the linker happy

/**
 * @brief struct of the memory Element.
 * This is basically a header for a stored data. It stores where the data is located, it's type and length. The key is used to have a unique identifier for each data stored this way
 *
 * @note Upon initialization only the **key and type** have to be given:
\code
 	 memoryElement elementList[4] =
	{
			{"1st", i8},
			{"2nd", i16},
			{"3rd", i32},
			{"4th", charstring}
	};
 * \endcode
 */
struct memoryElement
{
	/**
	 * @brief The key is used as a unique identifier for each data
	 */
	const char* key;

	/**
	 * @brief The types is used to specify the type of data stored. This way it can be read back and reconstructed as the correct type.
	 */
	elementType type;

	/**
	 * @brief The address where the saved data starts.
	 */
	uint32_t start;

	/**
	 * @brief The length of the stored data. This together with start clearly defines the memory field where the data can be found
	 * @note Only really useful for \link charstring  \endlink as the type defines the length of the data stored. Will also be useful in a possible future expansion where arrays of numbers will be allowed.
	 */
	uint8_t len;

	/**
	 * @brief Used in init, to mark if the header is already written into the memory.
	 */
	bool foundAtInit = 0;

	/**
	 * @brief The \link Memory \endlink element that has this instance in its dict.
	 */
	Memory* master;

    /**
	* @brief Delete the data that is located at \link start \endlink
	*/
	bool deleteData();

    /**
	* @brief Prints the key and value of the element.
	*
	* @note uses the stream parameter of the \link master \endlink
	*/
	void print();

    void operator = (uint8_t value_p);
    void operator = (uint16_t value_p);
    void operator = (uint32_t value_p);
    void operator = (const char* value_p);
};

///Typef of the \link Memory::errorCallback error handler function \endlink of the \link Memory \endlink class
typedef void (*MemoryErrorCallback_t)( Memory* caller_p, MemoryError_t errorCode_p, const char* key_p);



/**
 * @brief Base class for dictionary-like data storing.
 *
 * example:
 * \code
 	 memoryElement elementList[4] =
	{
    		{"1st", i8},
    		{"2nd", i16},
    		{"3rd", i32},
    		{"4th", charstring}
    };

    EEPROMmemory myEEPROM(elementList, 4, EEPROMAddress, &hi2c1);

    myEEPROM.attachStream(&mySerial);
    myEEPROM.attachErrorCallback(exampleCallback);

    myEEPROM["1st"] = "Mondottam, ember: küzdj és bízva bízzál!";
    myEEPROM["2nd"] = (uint16_t)3630;
    myEEPROM["3rd"] = (uint32_t)3000000000;
    myEEPROM["4th"] = (uint8_t)42;

    myEEPROM.listAll();
 * \endcode
 */
class Memory
{
protected:
	/**
	 * @brief Function handler for an error handler function.
	 *
	 * If attached an error handler function will be called when encountering a problem
	 * @note must abide to the following argument list: ( Memory* caller_p, MemoryError_t errorCode_p, const char* key_p)
	 */
	MemoryErrorCallback_t errorCallback = NULL;

	/**
	 * @brief Array containing the headers
	 */
    memoryElement* dict = NULL;

    /**
	 * @brief The length of the array \link dict \endlink
	 */
    uint16_t dictLen = 0;

    /**
	* @brief Copyes the value of of the data starting at the given address
	*
	* @param start_p memory address where the data starts
	* @param result_p pointer where the found data will be copied
	* @param type_p the \link type elementType \endlink of the stored data
	*
	* Has to be Implemented to fit for the specific memory
	*
	* @note gets called by the public \link getValue \endlink function
	*/
    virtual bool _getValue(uint32_t start_p, void* result_p, elementType type_p) = 0;

    /**
	* @brief Copyes the value of the passed pointer to the the memory location marked by the start
	*
	* @param start_p memory address where the data starts
	* @param source_p pointer to the new data
	* @param type_p the \link type elementType \endlink of the new data
	*
	* Has to be Implemented to fit for the specific memory
	*
	* @note gets called by the public \link setValue \endlink function
	*/
    virtual bool _setValue(uint32_t start_p, void* source_p, elementType type_p) = 0;

public:
    /// Will be used for printing, can be used to access a stream from the error handler function
    Stream* stream = NULL;

    /**
	* @brief Constructor for the Memory class.
	* @param dict_p The array of dict elements (technically headers for the data stored at each \link memoryElement::start \endlink)
	* @param dictLen The length of the array \link dict \endlink.
	* @param errorCallback_p the \link MemoryErrorCallback_t error handler function \endlink to be attached upon instantiation
	*
	*/
    Memory(memoryElement* dict_p, uint16_t dictLen_p, MemoryErrorCallback_t errorCallback_p= NULL, Stream* stream_p = NULL);

    /**
	* @brief Attaches an Error handler function handler to the instance.
	* @param errorCallback_p The function to be used (must abide to the following argument list: ( Memory* caller_p, MemoryError_t errorCode_p, const char* key_p))
	* example:
	* \code
	 void exampleCallback( Memory* caller_p, MemoryError_t errorCode_p, const char* key_p)
	⋮
	{
		switch(errorCode_p)
		{
			case KEY_ERROR:
			{
				caller_p->stream->print(key_p);
				caller_p->stream->print(" - invalid key error\r\n");
				break;
			}
			case INVALID_TYPE_ERROR:
			{
				caller_p->stream->print(key_p);
				caller_p->stream->print(" - invalid type error\r\n");
				break;
			}
			case TYPE_MISSMATCH_ERROR:
			{
				caller_p->stream->print(key_p);
				caller_p->stream->print(" - saved type doesn't match with the initializer list\r\n");
				break;
			}
			case INVALID_ADDRESS:
			{
				caller_p->stream->print(key_p);
				caller_p->stream->print(" - invalid data field start address\r\n");
				break;
			}
			default:
			{
				caller_p->stream->print(key_p);
				caller_p->stream->print(" - unknown error\r\n");
				break;
			}
		}
	}
	⋮
	myEEPROM.attachErrorCallback(exampleCallback);
	⋮
	*\endcode
	*/
    void attachErrorCallback( MemoryErrorCallback_t errorCallback_p );

    /**
	* @brief Attach an instance of the Stream class to be used for printing.
	* @param stream_p The instance of the Stream class that will be attached
	*
	*/
    void attachStream(Stream* stream_p);

    /**
	* @brief Copyes the value of of the data belonging to the given key into the passed pointer
	* @param key_p The key of the wanted value
	* @param result_p pointer where the found data will be copied
	*
	* To be used with uint8_t values
	*
	* @note will call virutal function \link _getValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool getValue(const char* key_p, uint8_t* result_p);
    /**
	* @brief Copyes the value of of the data belonging to the given key into the passed pointer
	* @param key_p The key of the wanted value
	* @param result_p pointer where the found data will be copied
	*
	* To be used with uint16_t values
	*
	* @note will call virutal function \link _getValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool getValue(const char* key_p, uint16_t* result_p);
    /**
	* @brief Copyes the value of of the data belonging to the given key into the passed pointer
	* @param key_p The key of the wanted value
	* @param result_p pointer where the found data will be copied
	*
	* To be used with uint32_t values
	*
	* @note will call virutal function \link _getValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool getValue(const char* key_p, uint32_t* result_p);
    /**
	* @brief Copyes the value of of the data belonging to the given key into the passed pointer
	* @param key_p The key of the wanted value
	* @param result_p pointer where the found data will be copied
	*
	* To be used with const char* (string) values
	*
	* @note will call virutal function \link _getValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool getValue(const char* key_p, const char* result_p);

    /**
	* @brief Sets the value of of the data belonging to the given key to the passed value
	* @param key_p The key of the value that will be changed
	* @param value_p The value that will be written in the place of the old data
	*
	* To be used with uint8_t values
	*
	* @note will call virutal function \link _setValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool setValue(const char* key_p, uint8_t value_p);
    /**
	* @brief Sets the value of of the data belonging to the given key to the passed value
	* @param key_p The key of the value that will be changed
	* @param value_p The value that will be written in the place of the old data
	*
	* To be used with uint16_t values
	*
	* @note will call virutal function \link _setValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool setValue(const char* key_p, uint16_t value_p);
    /**
	* @brief Sets the value of of the data belonging to the given key to the passed value
	* @param key_p The key of the value that will be changed
	* @param value_p The value that will be written in the place of the old data
	*
	* To be used with uint32_t values
	*
	* @note will call virutal function \link _setValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool setValue(const char* key_p, uint32_t value_p);
    /**
	* @brief Sets the value of of the data belonging to the given key to the passed value
	* @param key_p The key of the value that will be changed
	* @param value_p The value that will be written in the place of the old data
	*
	* To be used with const char* (string) values
	*
	* @note will call virutal function \link _setValue \endlink , that has to be Implemented  for the specific memory types
	*/
    bool setValue(const char* key_p, const char* value_p);

    /**
	* @brief Delete the data corresponding to the given key
	* @param key_p The key of the value that will deleted
	*/
    virtual bool deleteElementData(const char* key_p) = 0;


    /**
	* @brief virtual overload of the bracket operator. Has to be Implemented  to fit for the specific memory
	*
	* @param key_p The key of the value that will returned
	*
	* @return the element with the given key
	*/
    virtual memoryElement operator []  (const char* key_p) = 0;

    /**
	* @brief Lists the names of elements and their data
	* @param stream_p Pointer to a Stream object, where the output will be generated. Defaults to null in which case the \link stream \endlink will be used
	*
	* Example:
	* \code
	⋮
    memoryElement elementList[4] =
    {
		{"1st", charstring},
		{"2nd", i16},
		{"3rd", i32},
		{"4th", i8}
    };

    EEPROMmemory myEEPROM(elementList, 4, EEPROMAddress, &hi2c1);

    myEEPROM.attachStream(&mySerial);

    myEEPROM["1st"] = "Mondottam, ember: küzdj és bízva bízzál!";
    myEEPROM["2nd"] = (uint16_t)3630;
    myEEPROM["3rd"] = (uint32_t)3000000000;
    myEEPROM["4th"] = (uint8_t)42;

    myEEPROM.listAll();
    ⋮
	* \endcode
	*
	OUTPUT:
	\code
	1st - Mondottam, ember: küzdj és bízva bízzál!
	2nd - 3630
	3rd - 3000000000
	4th - 42
	\endcode
	*
	* @note If a stream_p param is passed it will overwrite the current \link stream \endlink and will be attached as the new stream
 	*/
    void listAll(Stream* stream_p = NULL);

    friend struct memoryElement;
};


/**
 * @brief Derived class from the class \link Memory \endlink to be used with 24LC512 EEPROM.
 *
 *  In the firs 55 page 440 header can be stored (8 16byte header per 128 byte page), from the 55th page the data of of each element is stored, one data per page.
 *  There is a total of 500 page, so this way only 5 page is wasted.
 *
 *  @note structure of the header: 12 byte for the key(including the terminating '\0'), 2 byte for the data starts address, 1 byte for the length of the data(it is not used in the current implementation), 1 byte for the type of the data stored.
 */
class EEPROMmemory: public Memory
{
private:

	/**
	 * @brief The I2C address of the EEPROM
	 */
    uint8_t EEPROMAddress;

	/**
	 * @brief The HAL I2C handle that will be used to communicate with the device
	 */
    I2C_HandleTypeDef* I2Ccontroller = NULL;

	/**
	 * @brief A page of the 24LC512 EEPROM is 128 byte long.
	 */
    uint8_t pageLen = 128;

	/**
	 * @brief The key of the data is the first element of the header
	 */
    uint8_t keyStarts = 0;

	/**
	 * @brief The start address of the stored data is the second element in the header, taking up 2 bytes
	 */
    uint8_t startStarts = 12;

	/**
	 * @brief The length of the stored data is the third element in the header, taking up 1 bytes
	 * @note Not used in the current application as the type also defines the elements length. In the case of const char* data the max length is the length of a page (128 bytes), and the end can be determined by the terminating 0.
	 */
    uint8_t lenStarts = 14;

	/**
	 * @brief The type of the stored data is the fourth element in the header, taking up 1 bytes
	 */
    uint8_t typeStarts = 15;

	/**
	 * @brief The length of a header is 16 bytes in total
	 */
    uint8_t headerLen = 16;

    /**
	* @brief Implements Memory::_getValue
	*
	* @param start_p memory address where the data starts
	* @param result_p pointer where the found data will be copied
	* @param type_p the \link type elementType \endlink of the stored data
	*
	* @note gets called by the public \link getValue \endlink function
	*/
    bool _getValue(uint32_t start_p, void* result_p, elementType type_p) override;

    /**
	* @brief Implements Memory::_setValue
	*
	* @param start_p memory address where the data starts
	* @param source_p pointer to the new data
	* @param type_p the \link type elementType \endlink of the new data
	*
	* @note gets called by the public \link setValue \endlink function
	*/
    bool _setValue(uint32_t start_p, void* source_p, elementType type_p) override;

    /**
     * @brief used to update the value of the saved header in the case of data type change
     *
     * @param start_p The memory address where the data of the memory element is saved, <b>not the start of the header</b>. It will be used as key to find the element
     * @param type_p The <b>new</b> data type
     *
     */
    void updateHeader(uint32_t start_p, elementType type_p);


    /**
	* @brief Writes header data to the given memory location
	*
	* @param element_p The header data to be written
	* @param headerStart_p the memory address where the header will be written
	*
	*/
    HAL_StatusTypeDef writeHeader(memoryElement element_p, uint16_t headerStart_p);

    /**
    	* @brief The initialization of the EEPROM, based on the dict_p passed to the constructor is realised here
	*/
    void Init();
public:
    /**
	* @brief Constructor for the EEPROMmemory class.
	*
	* @param dict_p The array of dict elements (technically headers for the data stored at each \link memoryElement::start \endlink) (will be passed to the constructor of the \link Memory base class \endlink)
	* @param dictLen The length of the array \link dict \endlink. (will be passed to the constructor of the \link Memory base class \endlink)
	* @param EEPROMAddress_p the I2C address of the EEPROM
	* @param i2c_handle The I2C handle to use for communication.
	* @param errorCallback_p the \link MemoryErrorCallback_t error handler function \endlink to be attached upon instantiation (will be passed to the constructor of the \link Memory base class \endlink)
	*
	* @warning If the type of an element in the dict_p is found in the EEPROM but the types are not matching, the one in the EEPROM will be used in order to match with the data saved there. In case of a new value is given this will be overwritten anyway.
	* If such mismatch occurs -if possible- the errorCallback function will be called
	*/
    EEPROMmemory(memoryElement* dict_p, uint16_t dictLen,uint8_t EEPROMAddress_p, I2C_HandleTypeDef* i2c_handle, MemoryErrorCallback_t errorCallback_p = NULL, Stream* stream_p = NULL);


    /**
	* @brief reads the header stored at the given address on the EEPROM
	* @param headerStart_p the memory address where the header is located
	*
	* @returns The memoryElement found at the address.
	*
	* @warning It does not check whether the found data makes any sense as a header or not.
	*/
    memoryElement readHeader(uint16_t headerStart_p);

    /**
	* @brief Implements \link Memory::deleteElementData \endlink
	* @param key_p key_p The key of the value that will deleted
	*
	* uses the function \link deleteRegion \endlink, to erease the whole page where the data of the element was stored
	*/
    bool deleteElementData(const char* key_p) override;

    /**
	* @brief Implements \link Memory::operator [] \endlink
	* @param key_p The key of the sought element
	*
	* @returns the memoryElement with the given key. If no element is found with the given key, \link KEY_ERROR \endlink will be passed to the \link errorCallback \endlink function and an empty element will be returned.
	*/
    memoryElement operator []  (const char* key_p) override;

};

#endif /* MEMORY_MEMORY_HPP_ */
