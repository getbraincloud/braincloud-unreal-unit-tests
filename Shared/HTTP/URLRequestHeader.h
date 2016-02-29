//
//  URLRequestHeader.h
//  GameClientLib
//


#ifndef _URLREQUESTHEADER_H_
#define _URLREQUESTHEADER_H_


#include <string>


class URLRequestHeader {

public:
    URLRequestHeader( std::string const &,
                     std::string const & = std::string() );
    URLRequestHeader( URLRequestHeader const & h )  { copy(h); }
    virtual ~URLRequestHeader( );

    URLRequestHeader    & operator=( URLRequestHeader const & h )
    {
        copy(h);
        return(*this);
    }

    const std::string & getName( ) const    { return _name; }
    const std::string & getValue( ) const   { return _value; }

    void        setValue( std::string const & = std::string() );

protected:

private:
    void        copy( URLRequestHeader const & );

    std::string _name;
    std::string _value;

};  // end URLRequestHeader


#endif  // _URLREQUESTHEADER_H_
