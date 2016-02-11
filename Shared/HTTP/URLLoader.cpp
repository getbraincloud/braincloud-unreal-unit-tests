//
//  URLLoader.cpp
//  GameClientLib
//


#include "URLLoader.h"


/**
 * Constructor
 *   - NOTE:  If a URLRequest is given, the object will try to contact the
 *            server immediately by calling the load() method.
 */
URLLoader::URLLoader( URLLoaderClient * client )
    : _client(client) {

}  // end URLLoader::URLLoader

URLLoader::URLLoader( URLLoader const & urlLoader )
    : _client(NULL), _urlRequest(urlLoader._urlRequest) {

}  // end URLLoader::URLLoader


/**
 * Destructor
 */
URLLoader::~URLLoader( ) {

}  // end URLLoader::~URLLoader


/*
 * Public Methods
 */


/*
 * Protected Methods
 */


/*
 * Private Methods
 */
