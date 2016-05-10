//
//  URLRequestHeader.cpp
//  GameClientLib
//


#include "braincloud/internal/URLRequestHeader.h"


/**
 * Constructor
 */
URLRequestHeader::URLRequestHeader( std::string const & name,
                                   std::string const & value )
    : _name(name), _value(value) {
}  // end URLRequestHeader::URLRequestHeader


/**
 * Destructor
 */
URLRequestHeader::~URLRequestHeader( ) {
}  // end URLRequestHeader::~URLRequestHeader


/*
 * Public Methods
 */


/**
 * Set the value for the header.
 */
void URLRequestHeader::setValue( std::string const & value ) {
    _value = value;
}  // end URLRequestHeader::setValue


/*
 * Protected Methods
 */


/*
 * Private Methods
 */


/**
 * Copy the contents of another request header into this header.
 *
 * @param other - other header
 */
void URLRequestHeader::copy( URLRequestHeader const & other ) {
    _name   = other._name;
    _value  = other._value;
}  // end URLRequestHeader::copy
