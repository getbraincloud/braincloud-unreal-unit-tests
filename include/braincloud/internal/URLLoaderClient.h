//
//  URLLoaderClient.h
//  GameClientLib
//


#include <string>
#include "braincloud/internal/URLResponse.h"


/**
 * Pure virtual class for sending responses back to the object which called
 * URLLoader.
 */
class URLLoaderClient {

public:
    // Include a virtual destructor to avoid problems destroying sub-classed
    // objects.
    virtual ~URLLoaderClient( ) { }

    /**
     * Inform the client an error occurred while attempting to process the
     * HTTP request.
     */
    virtual void    handleError( URLResponse const & ) = 0;

    /**
     * Allow the client to process the content of the response.
     *
     * @param response - content of the HTTP response from the server
     */
    virtual void    handleResult( URLResponse const & ) = 0;

protected:

private:

};  // end class
