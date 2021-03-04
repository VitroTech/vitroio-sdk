#error The file is namespaces documentation only.


/**
 * @namespace vitroio
 * 
 * @brief The namespace contains all of components of vitro-shard-sdk and
 * components based on the sdk. It is suggested to place types inherited from
 * the sdk components in this namespace e.g. implementations of sensors
 * drivers/interfaces.
 */
namespace vitroio
{

/**
 * @namespace vitroio::sdk
 * @brief The namespace contains all of components defined by
 * vitro-shard-sdk.
 */
namespace sdk
{

/**
 * @namespace vitroio::sdk::impl
 * 
 * @brief The namespace contains internal components of vitro-shard-sdk.
 * These components should not be used by user.
 */ 
namespace impl
{

} // namespace impl

} // namespace sdk

} // namespace vitroio
