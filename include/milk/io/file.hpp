#pragma once

#include <string>

namespace milk {

class file {
public:
	file() = default;
	file(const std::string& path);

	file& operator=(const std::string& path);

	/**
	 * Path of this file
	 */
	const std::string& path() const noexcept;

	/**
	 * Content of this file
	 *
	 * @throws When file operations fail
	 */
	std::string get_contents() const;

private:
	std::string m_path;
};

} // namespace milk
