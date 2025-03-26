/**
* @file    stack_fifo.h
*
* @brief   Beschreibung
*
* @author  mgrathwohl
*
* @date    2023/08/18
*
*/

#ifndef STACK_FIFO_H_
#define STACK_FIFO_H_

#include <cstdint>
#include <array>

template <typename T>
class Stack_Fifo_Interface
{
public:
	virtual bool write(T &value) = 0;
	virtual bool read(T &value) = 0;
	virtual bool isDataAvlb() = 0;
};

/** Fifo template Klasse
*
* speichert Informationen nach dem fifo prinzip\n
* Fifo anlegen z.B.:\n
* Stack_Fifo<int,10> tmp_fifo;\n
* oder\n
* Stack_Fifo<int,10> *tmp_fifo1 = new Stack_Fifo<int,10>();
*
* > Keine Strings verwenden fuer das Template!
*
* @author mgrathwohl
* @date 2023/08/18
*/
template <typename T, const uint32_t _len>
class Stack_Fifo : public Stack_Fifo_Interface<T>
{
public:
	/** konstruktor class instance.
	 *
	 * initialisiert die indexe
	 *
	 */
	Stack_Fifo() = default;

	/** destruktor class instance.
	 *
	 */
	virtual ~Stack_Fifo() = default;

	Stack_Fifo(Stack_Fifo &other) = delete;
	void operator=(const Stack_Fifo &) = delete;

	/** schreib operation.
	 *
	 * schreibt den definierten Datentyp in die fifo.
	 *
	 * @param value zu speichernder Wert.
	 *
	 * @return true wenn schreiben erfolgreich, sonst false
	 */
	inline bool write(T &value)
	{
		bool ret_code = false;
		uint32_t newWrIdx = _writeIdx;
		++newWrIdx;
		if(newWrIdx >= _len)
		{
			newWrIdx = 0;
		}
		if (newWrIdx != _readIdx)
		{
			fifo_array.at(_writeIdx) = value;
			_writeIdx = newWrIdx;
			ret_code = true;
		}
		return ret_code;
	};

	/** lese operation.
	 *
	 * liest den definierten Datentyp aus der Fifo, incl. Austrag aus der Fifo.
	 *
	 * @param value aeltester Datentyp wird hier zurueckgegeben.
	 *
	 * @return true wenn lesen erfolgreich, sonst false
	 */
	inline bool read(T &value)
	{
		bool retval = false;
		if(isDataAvlb())
		{
			value =  fifo_array.at(_readIdx);
			++_readIdx;
			if(_readIdx >= _len)
			{
				_readIdx = 0;
			}
			retval = true;
		}
		return retval;
	};

	/** lese operation.
	 *
	 * liest den definierten Datentyp aus der fifo.
	 * fifo wird nicht veraendert, Datentyp bleibt in fifo vorhanden
	 *
	 * @param value aeltester Datentyp wird hier zurueckgegeben.
	 *
	 * @return true wenn lesen erfolgreich, sonst false
	 */
	inline bool read_data(T &value)
	{
		bool retval = false;
		if(isDataAvlb())
		{
			value =  fifo_array.at(_readIdx);
			retval = true;
		}
		return retval;
	};

	/** daten vorhanden operation.
	*
	* prueft ob sich daten in der fifo befinden
	*
	* @return true wenn Daten vorhanden, false wenn nicht.
	*/
	inline bool isDataAvlb()
	{
		bool retval = false;
		if(_readIdx != _writeIdx)
		{
			retval = true;
		}
		return retval;
	};

	/** daten loeschen operation.
	*
	* loescht alle Daten aus der fifo und setzt die Indexe zurueck
	*
	*/
	inline void clear()
	{
		_readIdx = 0;
		_writeIdx = 0;
		fifo_array.fill(T());
	};

	/** datengroese fuer einen eintrag operation.
	*
	* @return gibt die groese fuer einen eintrag in der fifo zurueck in byte
	*
	*/
	inline uint32_t getDataSize()
	{
		return sizeof(T);
	};

	/** datengroese fuer fifo operation.
	*
	* @return gibt die groese fuer die gesamte fifo zurueck in byte
	*
	*/
	inline uint32_t getFifoSize()
	{
		return (getDataSize()*_len);
	};

	/** Anzahl belegte Meldungen in fifo operation.
	 *
	* @return gibt die Anzahl belegter Meldungen in der Fifo zurueck
	 *
	*/
	inline uint32_t anz_exist_meld()
	{
		uint32_t retval = 0;
		if(_writeIdx >= _readIdx)
		{
			retval = _writeIdx - _readIdx;
		}
		else
		{
			retval = (_len - _readIdx) + _writeIdx;
		}
		return retval;
	}

	/** Anzahl freie Meldungen in fifo operation.
	*
	 * @return gibt die Anzahl freier Meldungen in der Fifo zurueck
	*
	*/
	inline uint32_t anz_free_meld()
	{
		return((_len - 1) - anz_exist_meld());
	}

protected:
	std::array<T, _len> fifo_array{};
	volatile uint32_t _readIdx = 0;
	volatile uint32_t _writeIdx = 0;
};


/** Round Robin Fifo template Klasse
*
* speichert Informationen nach dem fifo prinzip\n
* Wenn Fifo voll ist werden Daten von vorne ueberschrieben\n
* Fifo anlegen fuer z.B. 9 Eintraege:\n
* Stack_RR_Fifo<int,10> tmp_fifo;\n
* oder\n
* Stack_RR_Fifo<int,10> *tmp_fifo1 = new Stack_RR_Fifo<int,10>();
*
* > Keine Strings verwenden fuer das Template!
*
* @author mgrathwohl
* @date 2023/08/18
*
* @see Stack_Fifo
*/
template <typename T, const uint32_t _len>
class Stack_RR_Fifo : public Stack_Fifo<T, _len>
{
public:
	Stack_RR_Fifo() : Stack_Fifo<T, _len>()
	{};
	virtual ~Stack_RR_Fifo() = default;

	inline bool write(T &value) override
	{
		bool retval = true;
		uint32_t newWrIdx = Stack_Fifo<T, _len>::_writeIdx;
		++newWrIdx;
		if(newWrIdx >= _len)
		{
			newWrIdx = 0;
		}
		if(newWrIdx == Stack_Fifo<T, _len>::_readIdx)
		{
			incReadIdx();
		}

		Stack_Fifo<T, _len>::fifo_array.at(Stack_Fifo<T, _len>::_writeIdx) = value;
		Stack_Fifo<T, _len>::_writeIdx = newWrIdx;

		return retval;
	};

	inline bool read(T &value) override
	{
		bool retval = false;
		if(Stack_Fifo<T, _len>::read_data(value))
		{
			incReadIdx();
			retval = true;
		}
		return retval;
	};

private:
	inline void incReadIdx()
	{
		++Stack_Fifo<T, _len>::_readIdx;
		if(Stack_Fifo<T, _len>::_readIdx >= _len)
		{
			Stack_Fifo<T, _len>::_readIdx = 0;
		}
	}

};

#endif /* STACK_FIFO_H_ */
