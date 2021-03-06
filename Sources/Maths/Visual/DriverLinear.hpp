#pragma once

#include "Driver.hpp"

namespace acid
{
/**
 * @brief A driver that linearly increases its value.
 * @tparam T The type to be driven.
 **/
template<typename T>
class DriverLinear :
	public Driver<T>
{
public:
	/**
	 * Creates a new linear driver.
	 * @param start The start value. 
	 * @param end The end value. 
	 * @param length The time to go between values. 
	 **/
	DriverLinear(const T &start, const T &end, const Time &length) :
		Driver<T>(length),
		m_start(start),
		m_end(end)
	{
	}

	/**
	 * Gets the start time.
	 * @return The start time. 
	 **/
	const T &GetStart() const { return m_start; }

	/**
	 * Sets the start time.
	 * @param start The new start time. 
	 **/
	void SetStart(const T &start) { m_start = start; }

	/**
	 * Gets the end time.
	 * @return The ebd time. 
	 **/
	const T &GetEnd() const { return m_end; }

	/**
	 * Sets the end time.
	 * @param end The new end time. 
	 **/
	void SetEnd(const T &end) { m_end = end; }

protected:
	T Calculate(const float &factor) override
	{
		return m_start + factor * (m_end - m_start);
	}

private:
	T m_start;
	T m_end;
};
}
