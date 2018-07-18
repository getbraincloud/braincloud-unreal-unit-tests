#ifndef _XMLHTTPEVENTSINK_H_
#define _XMLHTTPEVENTSINK_H_

#include <functional>

#include <atlbase.h>
#include <comutil.h>
#include <msxml6.h>

class XMLHTTPEventSink : public IDispatch
{
public:
    XMLHTTPEventSink(IXMLHTTPRequest *request, const std::function<void()>& onCompleted)
        : m_request(request)
        , m_onCompleted(onCompleted)
    {
    }
    virtual ~XMLHTTPEventSink() { }

    // IUnknown 
    STDMETHODIMP QueryInterface(REFIID riid, void **ppvObject);
    STDMETHODIMP_(ULONG) AddRef();
    STDMETHODIMP_(ULONG) Release();

    // IDispatch
    STDMETHODIMP GetTypeInfoCount(UINT *pctinfo);        
    STDMETHODIMP GetTypeInfo(UINT iTInfo, LCID lcid, ITypeInfo **ppTInfo);    
    STDMETHODIMP GetIDsOfNames(REFIID riid, LPOLESTR *rgszNames, UINT cNames, LCID lcid, DISPID *rgDispId);
    STDMETHODIMP Invoke(DISPID dispIdMember, REFIID riid, LCID lcid, WORD wFlags, DISPPARAMS *pDispParams, VARIANT *pVarResult, EXCEPINFO *pExcepInfo, UINT *puArgErr);
private:
    LONG m_refCount;
    IXMLHTTPRequest *m_request;

    std::function<void()> m_onCompleted;
};

#endif /* _XMLHTTPEVENTSINK_H_ */
