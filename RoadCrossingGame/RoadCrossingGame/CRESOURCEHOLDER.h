#ifndef CRESOURCEHOLDER_H
#define CRESOURCEHOLDER_H

#include <string>
#include <memory>
#include <map>
#include <stdexcept>
#include <cassert>

template <typename Resource, typename Identifier>
class CRESOURCEHOLDER {
public:
	void load(Identifier id, const std::string& filename);

	template <typename Parameter>
	void load(Identifier id, const std::string& filename, const Parameter& secondParam);

	Resource& get(Identifier id);
	const Resource& get(Identifier id) const;
private:
	void insertResource(Identifier id, std::unique_ptr<Resource> resource);
private:
	std::map<Identifier, std::unique_ptr<Resource>>	mResourceMap;
};
#include "CRESOURCEHOLDER.inl"
#endif // !CRESOURCEHOLDER_H

