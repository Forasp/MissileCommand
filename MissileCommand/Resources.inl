
template <typename Resource, typename Identifier>
void Resources<Resource, Identifier>::LoadResource(Identifier _ID, const std::string& _Filename)
{
	// Create and load resource
	std::unique_ptr<Resource> NewResource(new Resource());
	if (!NewResource->loadFromFile(_Filename))
		throw std::runtime_error("Resources::load - Failed to load " + _Filename);

	// If loading successful, insert resource to map
	AddResource(_ID, std::move(NewResource));
}

template <typename Resource, typename Identifier>
template <typename Parameters>
void Resources<Resource, Identifier>::LoadResource(Identifier _ID, const std::string& _Filename, const Parameters& _SecondParam)
{
	// Create and load resource
	std::unique_ptr<Resource> NewResource(new Resource());
	if (!NewResource->loadFromFile(_Filename, _SecondParam))
		throw std::runtime_error("Resources::load - Failed to load " + _Filename);

	// If loading successful, insert resource to map
	AddResource(_ID, std::move(NewResource));
}

template <typename Resource, typename Identifier>
Resource& Resources<Resource, Identifier>::GetResource(Identifier _ID)
{
	auto Found = mResourceMap.find(_ID);
	assert(Found != mResourceMap.end());

	return *Found->second;
}

template <typename Resource, typename Identifier>
const Resource& Resources<Resource, Identifier>::GetResource(const Identifier _ID)
{
	auto Found = mResourceMap.find(_ID);
	assert(Found != mResourceMap.end());

	return *Found->second;
}

template <typename Resource, typename Identifier>
void Resources<Resource, Identifier>::AddResource(Identifier _ID, const std::string& _Filename)
{
	// Insert and check success
	auto Inserted = mResourceMap.insert(std::make_pair(_ID, std::move(_Resource)));
	assert(Inserted.second);
}
