/*****************************************************************
 **' Dependencies.h
 *****************************************************************
 **' Created on: 13.04.2015
 **' Author: HAUSWALD, Tom.
 *****************************************************************
 *****************************************************************/

#ifndef DEPENDENCIES_H_
#define DEPENDENCIES_H_

//Do nothing
#define NOOP ;;

/**
 * Return the number of entries in an enumeration
 * Enumeration E must create a namespace __E__
 * that contains a global constant COUNT.
 */
#define ENUM_COUNT(E) (__ ## E ## __::COUNT)
/**
 * Stringify the enumeration value.
 */
#define ENUM_STRING(E, VALUE) (__ ## E ## __::tostring(VALUE))

//SFML used as multimedia library for input, graphics & audio
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

//Common standard library headers
#include <iostream>
#include <cstdlib>
#include <cstdint>
#include <cstdarg>
#include <cassert>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>
#include <memory>

namespace PKMN
{
	using namespace sf;
	using namespace std;

	/**
	 * Level indicator [1..Max Level].
	 */
	typedef uint8_t Level;

	/**
	 * Individual value.
	 */
	typedef uint8_t IndividualValue;

	/**
	 * Effort value.
	 */
	typedef uint8_t EffortValue;

	/**
	 * Stat stage:
	 * <ul>
	 * <li>[-6..6] for all stats besides HP.</>
	 * <li>[0..Max HP] for HP, where stat stage 0 means full HP left.</>
	 * </ul>
	 */
	typedef int16_t StatStage;

	/**
	 * Stat value.
	 */
	typedef uint16_t StatValue;

	/**
	 * Base stat value [0..255].
	 */
	typedef uint8_t BaseStatValue;

	/**
	 * An amount of experience points.
	 */
	typedef uint32_t Experience;

	/**
	 * String used for name.
	 * One or two words only in most cases.
	 */
	typedef string Name;

	/**
	 * String used as descriptive text.
	 */
	typedef string DescriptionText;

	/**
	 * String used as file name i.e. path specifier.
	 */
	typedef string Filename;

	/**
	 * Describes a percentage value inside the range [0..100].
	 */
	typedef uint8_t Percentage;

	/**
	 * Customly managed pointer.
	 */
	template<typename T>
	class custom_ptr
	{
	private:

		/**
		 * Action performed on the wrapped pointer.
		 */
		typedef function<void(T*)> PointerAction;

		/**
		 * Wrapped pointer.
		 */
		T *m_pointer;

		/**
		 * Action to perform on release.
		 */
		PointerAction m_releaseAction;

		/**
		 * If set to true, the relase action will be automatically
		 * performed when going out of scope.
		 */
		bool m_releaseEnabled;

	public:
		/**
		 * Construct empty custom pointer wrapper object.
		 */
		custom_ptr(void)
			:m_pointer(nullptr), m_releaseEnabled(true)
		{
				NOOP;
		}

		/**
		 * @return Mutable access to underlying pointer.
		 */
		inline T *get(void)
		{
			return m_pointer;
		}

		/**
		 * @return Readonly access to underlying pointer.
		 */
		inline const T *get(void) const
		{
			return m_pointer;
		}

		/**
		 * Assign an address to the pointer.
		 * If another address is already assigned,
		 * release is called on the old pointer and the
		 * new value is assigned afterwards.
		 *
		 * @param pointer
		 * The pointer.
		 *
		 * @param releaseAction
		 * Lambda expresseion describing the action to perform on the underlying pointer
		 * once released is called.
		 */
		inline void assign(T *pointer, const PointerAction &releaseAction)
		{
			release();
			m_pointer = pointer;
			m_releaseAction = releaseAction;
		}

		/**
		 * Disable automatic release.
		 */
		inline void disableRelease(void){ m_releaseEnabled = false; }

		/**
		 * Enable automatic release.
		 */
		inline void enableRelease(void){ m_releaseEnabled = true; }

		/**
		 * Release the pointer.
		 */
		inline void release(void)
		{
			if((m_pointer != nullptr) && m_releaseEnabled)
			{
				m_releaseAction(m_pointer);
				m_pointer = nullptr;
			}
		}

		/**
		 * If the release action was not performed yet,
		 * do it upon deconstruction.
		 */
		~custom_ptr(void)
		{
			release();
		}

		/**
		 * @return Whether the pointer is not null.
		 */
		inline bool valid(void) const
		{
			return m_pointer != nullptr;
		}

		//Dereference operator (mutable).
		inline T *operator->(void)
		{
			return m_pointer;
		}

		//Dereference operator (readonly).
		inline const T *operator->(void) const
		{
			return m_pointer;
		}
	};
}

/**
 * @return Whether A and B are the same type.
 */
template<typename A, typename B>
static inline bool equal(void){ return std::is_same<A, B>::value; }

/**
 * Formats a string using a variadic argument list.
 * Resulting string may not exceed a length of 512 characters.
 *
 * @param fmt
 * The format specifier.
 *
 * @return
 * The formatted string.
 */
static inline std::string formatstr(const std::string &fmt, ...)
{
	char buffer[512];
	const char *fmtcstr = fmt.c_str();

	va_list args;
	va_start(args, fmtcstr);
	vsprintf(buffer, fmtcstr, args);
	va_end(args);

	return std::string(buffer);
}

/**
 * Checks whether a certain value is contained within a vector.
 *
 * @param container
 * The vector to search through.
 * @param value
 * The value to search for.
 *
 * @return
 * Whether the value was found.
 */
template<typename T>
static inline bool invector(const std::vector<T> &container, const T &value)
{
	return find(container.begin(), container.end(), value) != container.end();
}

/**
 * Split a string into substrings at all occurences of the delimiter.
 * Put the results in the vector specified.
 *
 * @param str
 * The string to split.
 *
 * @param delim
 * The delimiting character.
 *
 * @param elems
 * Vector to add the result to.
 *
 * @return
 * Vector containing all substrings in order of occurrence.
 */
static inline std::vector<std::string> &splitstr(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (getline(ss, item, delim))
    {
        elems.push_back(item);
    }
    return elems;
}

/**
 * Split a string into substrings at all occurences of the delimiter.
 *
 * @param s
 * The string to split.
 *
 * @param delim
 * The delimiting character.
 *
 * @return
 * Vector containing all substrings in order of occurrence.
 */
static inline std::vector<std::string> splitstr(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    splitstr(s, delim, elems);
    return elems;
}

#include <sys/stat.h>

/**
 * Checks whether a file exists.
 *
 * @param file
 * Name of the file.
 *
 * @return
 * Whether the file exists.
 */
static inline bool fileExists(const std::string &file)
{
	struct stat buffer;
	return (stat(file.c_str(), &buffer) == 0);
}

#endif /* DEPENDENCIES_H_ */
